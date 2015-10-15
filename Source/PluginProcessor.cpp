/*
  ==============================================================================

    This file was auto-generated by the Introjucer!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#define _USE_MATH_DEFINES

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include <complex>
#include <iostream>
#include <fstream>

// http://graphics.stanford.edu/~seander/bithacks.html#RoundUpPowerOf2
int nextPowerOf2(int v)
{
    v--;
    v |= v >> 1;
    v |= v >> 2;
    v |= v >> 4;
    v |= v >> 8;
    v |= v >> 16;
    return ++v;
}

//==============================================================================
TestPluginAudioProcessor::TestPluginAudioProcessor()
{

}

TestPluginAudioProcessor::~TestPluginAudioProcessor()
{
}

//==============================================================================
const String TestPluginAudioProcessor::getName() const
{
    return JucePlugin_Name;
}


const String TestPluginAudioProcessor::getInputChannelName (int channelIndex) const
{
    return String (channelIndex + 1);
}

const String TestPluginAudioProcessor::getOutputChannelName (int channelIndex) const
{
    return String (channelIndex + 1);
}

bool TestPluginAudioProcessor::isInputChannelStereoPair (int index) const
{
    return true;
}

bool TestPluginAudioProcessor::isOutputChannelStereoPair (int index) const
{
    return true;
}

bool TestPluginAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool TestPluginAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool TestPluginAudioProcessor::silenceInProducesSilenceOut() const
{
    return true;
}

double TestPluginAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int TestPluginAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int TestPluginAudioProcessor::getCurrentProgram()
{
    return 0;
}

void TestPluginAudioProcessor::setCurrentProgram (int index)
{
}

const String TestPluginAudioProcessor::getProgramName (int index)
{
    return String();
}

void TestPluginAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void TestPluginAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    
    /* 
     For bass space we want fundamental frequency to be equivalent to 44.1K / 1024.
     i.e. around 43Hz. Then the 4 bass frequencies will be multiples of that.
    */

    fftSize = nextPowerOf2(int(sampleRate) / 50);
    
    int fftOrder = log2f(fftSize);
    forwardFFT.reset(new FFT(fftOrder, false));
    forwardLeftFFTData.reset(new float[2 * fftSize]);
    forwardRightFFTData.reset(new float[2 * fftSize]);

    // Report to UI what the block size is.
    blockSize = samplesPerBlock;
    
    // Get bass space frequencies.
    float fundamental = (float)sampleRate / (float)fftSize;
    
    for (int i = 0; i < 4; i++) {
        
        // Get the frequency at this bin.
        binFrequencies[i] = (i+1) * fundamental;
        
    }
    
    // Filter cutoff.
    float f_c = 0;
    
    // Filter cutoff radians.
    float theta_c = 0;
    
    /*
     
     Calculations for LUFS based on http://www.itu.int/dms_pubrec/itu-r/rec/bs/R-REC-BS.1770-3-201208-I!!PDF-E.pdf
     
     */
    
    // 400ms
    lufsMomentaryLoudnessSampleCount = sampleRate * 0.4;
    
    // 3s
    lufsShortTermLoudnessSampleCount = sampleRate * 3;
    
    // K-weighting filter for LUFS. Stage 1. High shelf. 4dB at 1682Hz
    f_c = 1682;
    float const gaindB = 4.;
    float V = powf(10, gaindB/ 20);
    float K = tanf(M_PI * f_c / sampleRate);
    
    // TODO: Subclass BiQuad for filters.
    float norm = 1 / (1 + M_SQRT2 * K + K * K);
    highShelfLeft.a0 = (V + sqrtf(2 * V) * K + K * K) * norm;
    highShelfLeft.a1 = 2 * (K * K - V) * norm;
    highShelfLeft.a2 = (V - sqrtf(2 * V) * K + K * K) * norm;
    highShelfLeft.b1 = 2 * (K * K - 1) * norm;
    highShelfLeft.b2 = (1 - M_SQRT2 * K + K * K) * norm;
    
    highShelfRight.a0 = highShelfLeft.a0;
    highShelfRight.a1 = highShelfLeft.a1;
    highShelfRight.a2 = highShelfLeft.a2;
    highShelfRight.b1 = highShelfLeft.b1;
    highShelfRight.b2 = highShelfLeft.b2;
    
    
    // K-weighting filter for LUFS. Stage 2. High pass. 100Hz
    f_c = 50;
    K = tanf(M_PI * f_c / sampleRate);
    float Q = M_SQRT1_2;
    norm = 1 / (1 + K / Q + K * K);
    highPassLeft.a0 = 1 * norm;
    highPassLeft.a1 = -2 * highPassLeft.a0;
    highPassLeft.a2 = highPassLeft.a0;
    highPassLeft.b1 = 2 * (K * K - 1) * norm;
    highPassLeft.b2 = (1 - K / Q + K * K) * norm;
    
    highPassRight.a0 = highPassLeft.a0;
    highPassRight.a1 = highPassLeft.a1;
    highPassRight.a2 = highPassLeft.a2;
    highPassRight.b1 = highPassLeft.b1;
    highPassRight.b2 = highPassLeft.b2;
    
    /*
    
     We are going to use a Linkwitz-Riley HPF to calculate a rough idea of of a track's level without bass.
     We need this to 'normalise' the bass space dB levels.
     
     From Designing Audio FX PLug-ins, Pirkle p. 186
    
    */
    
    f_c = 1000; // Filter cut-off 1000 Hz
    theta_c = M_PI * f_c / sampleRate;
    float omega_c = M_PI * f_c;
    float kappa = omega_c / tanf(theta_c);
    float delta = kappa * kappa + omega_c * omega_c + 2 * kappa * omega_c;
    linkwitzRiley.a0 = (kappa * kappa) / delta;
    linkwitzRiley.a1 = (-2 * kappa * kappa) / delta;
    linkwitzRiley.a2 = linkwitzRiley.a0;
    linkwitzRiley.b1 = (-2 * kappa * kappa + 2 * omega_c * omega_c) / delta;
    linkwitzRiley.b2 = (-2 * kappa * omega_c + kappa * kappa + omega_c * omega_c) / delta;

    
}

void TestPluginAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
    
    forwardFFT.reset();
    forwardLeftFFTData.reset();
    forwardRightFFTData.reset();


}

void TestPluginAudioProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{

    const int numSamples = buffer.getNumSamples();
    
    jassert(numSamples!=0);
    
    int scopeStride = 0;
    int scopeCounter = 0;
    
    // Effectively Rxx(0) is the energy in left channel. See Cross correlation comments below.
    float leftEnergy = 0;
    
    // Effectively Ryy(0) is the energy in right channel.
    float rightEnergy = 0;
    
    // Get the energy in the left/right channel after filtering.
    float leftEnergyFiltered = 0;
    
    float Rxy0 = 0;
    
    leftBlockMax = 0;
    rightBlockMax = 0;
    
    if (mode == UIConstants::Mode::DYNAMIC_RANGE || mode == UIConstants::Mode::STEREO)
    {
        // Just need NUMBER_SCOPE_POINTS points for the 'scopes
        scopeStride = floorf(numSamples / UIConstants::NUMBER_SCOPE_POINTS);
        scopeStride = scopeStride == 0 ? 1 : scopeStride; // numsamples can be small.
    }

    if (mode == UIConstants::Mode::HOME || mode == UIConstants::Mode::BASS_SPACE)
    {
        /*
         Fill up the fft data buffers. Remember we may have a larger buffer than the block size to get
         the required fft resolution.
        */
        
        // Apparently the block size could vary, if it does then our FFT will have issues. I have seen a value of 39!
        if (blockSize == numSamples)
        {
            // Get left channel FFT (used for logo).
            const float* channelData = buffer.getReadPointer (0);
            memcpy (&forwardLeftFFTData[fftBufferCount], channelData, numSamples * sizeof(float));
            
            // Now get right channel.
            channelData = buffer.getReadPointer (1);
            memcpy (&forwardRightFFTData[fftBufferCount], channelData, numSamples * sizeof(float));

            if (fftBufferCount + numSamples == fftSize)
            {
                // We have a full fft bufffer so do the DFT!
                forwardFFT->performRealOnlyForwardTransform(forwardLeftFFTData.get());
                forwardFFT->performRealOnlyForwardTransform(forwardRightFFTData.get());
                
                // TODO: Use better bins or average across bins.
                // Maybe don't need this every call.
                // We've only got 8 bars in the logo. Get bins at 100Hz,200Hz,400Hz, ...
                for (int i = 0, frequency = 100; i < 8; i++, frequency*=2)
                {
                    int bin = frequency / (getSampleRate() / fftSize);
                    std::complex<float> val(((FFT::Complex*)forwardLeftFFTData.get())[bin].r, ((FFT::Complex*)forwardLeftFFTData.get())[bin].i);
                    logoFFTBins[i] = int(std::abs(val)); // Get magnitude, this is just for display effect so just use 'raw' value.
                }
                
                fftDataReady = true;
                fftBufferCount = 0;
                
            } else
            {
                fftDataReady = false;
                fftBufferCount += numSamples;
            }
        }
    }

    
    if (getNumInputChannels() == 2 && getNumOutputChannels() == 2)
    {
        float* leftChannelData = buffer.getWritePointer (0);
        float* rightChannelData = buffer.getWritePointer (1);
        
        for (int i = 0; i < numSamples; ++i)
        {

            // Just about everyone wants energy of l and r
            leftEnergy += (leftChannelData[i] * leftChannelData[i]);
            rightEnergy += (rightChannelData[i] * rightChannelData[i]);
            
            // Get overall peak for this track, or until reset.
            leftPeak = std::abs(leftChannelData[i]) > std::abs(leftPeak) ? std::abs(leftChannelData[i]) : leftPeak;
            rightPeak = std::abs(rightChannelData[i]) > std::abs(rightPeak) ? std::abs(rightChannelData[i]) : rightPeak;
            
            // ************ Mono playback! ************
            float frameSum = leftChannelData[i] + rightChannelData[i];
            
            if (mono)
            {
                float frameSumAverage = frameSum / 2.f;
            
                leftChannelData[i] = frameSumAverage;
                rightChannelData[i] = frameSumAverage;
                
            }

            if (mode == UIConstants::Mode::HEADROOM)
            {
                
                // ************ Headroom! ************
                
                if (!headroomBreached)
                {
                    headroomBreached = (std::abs(leftChannelData[i]) > 0.5 || std::abs(rightChannelData[i]) > 0.5) ? true : false;
                }
            
                // ************ LUFS ************
                
                //float leftChannelFiltered = hs_a_0 * leftChannelData[i] + hs_a_1 * x_1 + hs_a_2 * x_2 - hs_b_1 * y_1 - hs_b_2 * y_2;
                float leftChannelFiltered = highShelfLeft.doBiQuad(leftChannelData[i]);
                float rightChannelFiltered = highShelfRight.doBiQuad(rightChannelData[i]);
                
                leftChannelFiltered = highPassLeft.doBiQuad(leftChannelFiltered);
                rightChannelFiltered = highPassRight.doBiQuad(rightChannelFiltered);
                
                lufsMomentaryLoudnessBlockEnergy += (leftChannelFiltered * leftChannelFiltered) + (rightChannelFiltered * rightChannelFiltered);
                
                // We have moved ahead by 100ms, now get the gating block loudness.
                if (sampleCount == lufsMomentaryLoudnessSampleCount / 4) {
                    
                    // Park this sum for the UI thread to use.
                    lufsMomentaryLoudnessBlockEnergySafe = lufsMomentaryLoudnessBlockEnergy;
                    
                    // Reset
                    lufsMomentaryLoudnessBlockEnergy = 0;
                    sampleCount = 0;
                    
                    sendActionMessage(UIConstants::LUFS_MESSAGE);
                    
                }
                
                sampleCount++;
            }
                
            if (mode == UIConstants::Mode::DYNAMIC_RANGE || mode == UIConstants::Mode::STEREO)
            {
                // ************ Vectorscope/Oscilloscope ************
                
                if (i % scopeStride == 0 && scopeCounter < UIConstants::NUMBER_SCOPE_POINTS)
                {
                    
                    // NOTE: R = x and L = y ! This is what polar vectorscope requires.
                    // Repurpose this also for oscilloscope.
                    scopePoints[scopeCounter++] = juce::Point<float>(rightChannelData[i], leftChannelData[i]);
                    
                    
                }
            }
            
            if (mode == UIConstants::Mode::DYNAMIC_RANGE)
            {
                // Get the maximum sample in this block for dynamic range calculation.
                if (leftBlockMax < std::abs(leftChannelData[i]))
                {
                    leftBlockMax = std::abs(leftChannelData[i]);
                }
                if (rightBlockMax < std::abs(rightChannelData[i]))
                {
                    rightBlockMax = std::abs(rightChannelData[i]);
                }
                
            
            }
            
            if (mode == UIConstants::Mode::STEREO)
            {
                // ************ Cross correlation ************
                
                /*
                 Cross correlation between l and r is Rxy(0) = Sum (x(n) * y(n)) (left = x, right = y).
                 Normalised to (-1, 1) is Rxy(0) / Sqrt(Rxx(0) Ryy(0)).
                 e.g. see p 114-116 Ch.2 DSP Proakis/Manolakis 2nd Edition.
                 */
                
                Rxy0 += leftChannelData[i] * rightChannelData[i];
                
            }
                
            if (mode == UIConstants::Mode::BASS_SPACE)
            {
                // ************ Bass space ************
                
                // Apply Linkwitz-Riley filter
                
                // Apply filter to left channel: y(n) = a0 * x(n) + a1 * x(n-1) + a2 * x(n-2) - b1 * y(n-1) - b2 * y(n-2).
//                  float leftChannelFiltered = a_0 * leftChannelData[i] + a_1 * x_1 + a_2 * x_2 - b_1 * y_1 - b_2 * y_2;
                float leftChannelFiltered = linkwitzRiley.doBiQuad(leftChannelData[i] );
             
                leftEnergyFiltered += (leftChannelFiltered * leftChannelFiltered);
            }
            
            
        }
    }
    
    if (mode == UIConstants::Mode::HEADROOM)
    {
        // Calculate RMS
        leftRMS = sqrtf(leftEnergy / numSamples);
        rightRMS = sqrtf(rightEnergy / numSamples);
    }
    
    if (mode == UIConstants::Mode::DYNAMIC_RANGE)
    {
        // Calculate RMS
        leftRMS = sqrtf(leftEnergy / numSamples);
        rightRMS = sqrtf(rightEnergy / numSamples);
        
        // Calculate average abs sample value for this block
        float blockAverageRMS = (leftRMS + rightRMS) / 2;
        
        if (dynamicRangeCounter < 10)
        {
            // Use this value to get dB, i.e. 20log(blockMax/blockAverage).
            if (blockAverageRMS == 0)
            {
                blockAverageRMS = 0.001;
            }
            if (leftBlockMax == 0)
            {
                leftBlockMax = 0.001;
            }
            if (rightBlockMax == 0)
            {
                rightBlockMax = 0.001;
            }
            
            
            dynamicRangeMax[dynamicRangeCounter] = std::max(leftBlockMax, rightBlockMax);
            dynamicRangeAvg[dynamicRangeCounter] = blockAverageRMS;
            
            dynamicRangeCounter++;
            
        } else
        {
            // Notify the editor to check the average value of dynamicRange.
//            sendActionMessage(UIConstants::DYNAMIC_RANGE_MESSAGE);
            dynamicRangeCounter = 0;
        }
    }
    
    if (mode == UIConstants::Mode::STEREO)
    {
        // Again, see Proakis.
        if (leftEnergy == 0 || rightEnergy == 0)
        {
            stereoCorrelation = 0;
        } else
        {
            stereoCorrelation = Rxy0/(sqrtf(leftEnergy * rightEnergy));
        }
    }
    
    if (mode == UIConstants::Mode::BASS_SPACE)
    {
        // For the filtered RMS.
        leftRMSFiltered = sqrtf(leftEnergyFiltered / numSamples);
        
        if (bassSpaceCounter < 100 )
        {
            // Also check blockSize as it may vary, rendering the FFT confused!
            if (fftDataReady && (blockSize == numSamples))
            {
                // We have a full fft buffer so we have fft data.
                
                // For bass space. Get first four bins (after DC).
                for (int i = 0; i < 4; i++) {
                    
                    // Get the amplitude in dB.
                    std::complex<float> val(((FFT::Complex*)forwardLeftFFTData.get())[i+1].r, ((FFT::Complex*)forwardLeftFFTData.get()  )[i+1].i);
                    binAmplitudes[i][bassSpaceCounter] = 20 * log10(std::abs(val) / (float(fftSize) / 2.)) ;
                    
                }
                
                // Also hold the leftRMSFiltered to use to 'normalise' the bass dB.
                leftRMSFilteredAverage[bassSpaceCounter] = leftRMSFiltered;
                
                bassSpaceCounter++;
            }
            
        } else
        {
            // Notify the editor to check the average value of bass space.
            sendActionMessage(UIConstants::BASS_SPACE_MESSAGE);
            bassSpaceCounter = 0;
        }
    }

    
    // ask the host for the current time.
    AudioPlayHead::CurrentPositionInfo newTime;
    
    if (getPlayHead() != nullptr && getPlayHead()->getCurrentPosition (newTime))
    {
        // Successfully got the current time from the host..
        lastPosInfo = newTime;
    }
    else
    {
        // If the host fails to fill-in the current time, we'll just clear it to a default..
        lastPosInfo.resetToDefault();
    }

    
    
    
}

//==============================================================================
bool TestPluginAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* TestPluginAudioProcessor::createEditor()
{
    return new TestPluginAudioProcessorEditor (*this);
}

//==============================================================================
void TestPluginAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void TestPluginAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new TestPluginAudioProcessor();
}
