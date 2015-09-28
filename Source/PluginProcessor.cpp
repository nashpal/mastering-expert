/*
  ==============================================================================

    This file was auto-generated by the Introjucer!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include <complex>
#include <iostream>
#include <fstream>

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
    return false;
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
    int fftOrder = log2f(samplesPerBlock);
    forwardFFT = new FFT(fftOrder, false);
    forwardLeftFFTData = new float[2 * samplesPerBlock]; // To hold real and Complex
    forwardRightFFTData = new float[2 * samplesPerBlock]; // To hold real and Complex
    multipliedFFT = new float[2 * samplesPerBlock];
    
    // Report to UI what the block size is.
    blockSize = samplesPerBlock;
    
    // Get bass space frequencies.
    float fundamental = (float)sampleRate / (float)samplesPerBlock;
    
    for (int i = 0; i < 4; i++) {
        
        // Get the frequency at this bin.
        binFrequencies[i] = (i+1) * fundamental;
        
    }
    
    // We are going to use a Linkwitz-Riley HPF to calculate a rough idea of of a track's level without bass.
    // We need this to 'normalise' the bass space dB levels.
    
    // From Designing Audio FX PLug-ins, Pirkle p. 186
    float f_c = 1000; // Filter cut-off 1000 Hz
    float theta_c = M_PI * f_c / sampleRate;
    float omega_c = M_PI * f_c;
    float kappa = omega_c / tanf(theta_c);
    float delta = kappa * kappa + omega_c * omega_c + 2 * kappa * omega_c;
    a_0 = (kappa * kappa) / delta;
    a_1 = (-2 * kappa * kappa) / delta;
    a_2 = a_0;
    b_1 = (-2 * kappa * kappa + 2 * omega_c * omega_c) / delta;
    b_2 = (-2 * kappa * omega_c + kappa * kappa + omega_c * omega_c) / delta;
    
    
}

void TestPluginAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
    delete forwardFFT;
    delete [] forwardLeftFFTData;
    delete [] forwardRightFFTData;
    delete [] multipliedFFT;

}

void TestPluginAudioProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{
    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // I've added this to avoid people getting screaming feedback
    // when they first compile the plugin, but obviously you don't need to
    // this code if your algorithm already fills all the output channels.
    
    dynamicRangeCounter++;
    
    const int numSamples = buffer.getNumSamples();
    
    // Just need 100 points for the vector scope
    int vectorScopeStride = floorf(numSamples / numberVectorPoints);
    int vectorScopeCounter = 0;
    
//    for (int i = getNumInputChannels(); i < getNumOutputChannels(); ++i)
//        buffer.clear (i, 0, buffer.getNumSamples());

    // Get left channel FFT (used for logo).
    const float* channelData = buffer.getReadPointer (0);
    zeromem (forwardLeftFFTData, numSamples * sizeof (float));
    memcpy (forwardLeftFFTData, channelData, numSamples * sizeof(float));
    
    // Now get right channel.
    channelData = buffer.getReadPointer (1);
    zeromem (forwardRightFFTData, numSamples * sizeof (float));
    memcpy (forwardRightFFTData, channelData, numSamples * sizeof(float));

    forwardFFT->performRealOnlyForwardTransform(forwardLeftFFTData);
    forwardFFT->performRealOnlyForwardTransform(forwardRightFFTData);
    
    // TODO: Use better bins or average across bins.
    // Maybe don't need this every call.
    // We've only got 8 bars in the logo. Get bins at 10oHz,200Hz,400Hz, ...
    for (int i = 0, frequency = 100; i < 8; i++, frequency*=2)
    {
        int bin = frequency / (getSampleRate() / numSamples);
        std::complex<float> val(((FFT::Complex*)forwardLeftFFTData)[bin].r, ((FFT::Complex*)forwardLeftFFTData)[bin].i);
        logoFFTBins[i] = int(std::abs(val)); // Get magnitude, this is just for display effect so just use 'raw' value.
    }

    // Effectively Rxx(0) is the energy in left channel. See Cross correlation comments below.
    float leftEnergy = 0;
    
    // Effectively Ryy(0) is the energy in right channel.
    float rightEnergy = 0;
    
    // Get the energy in the left channel after filtering.
    float leftEnergyFiltered = 0;
    
    float Rxy0 = 0;
    
    // Hold the sum of all summed abs L/R samples for average.
    float blockAbsFrameSum = 0;
    
    // Hold the block's max sample value from left or right.
    float blockMax = 0;
    
    if (getNumInputChannels() == 2 && getNumOutputChannels() == 2)
    {
        for (int i = 0; i < numSamples; ++i)
        {
            float* leftChannelData = buffer.getWritePointer (0);
            float* rightChannelData = buffer.getWritePointer (1);

            
            // ************ Cross correlation ************
            
            // Cross correlation between l and r is Rxy(0) = Sum (x(n) * y(n)) (left = x, right = y).
            // Normalised to (-1, 1) is Rxy(0) / Sqrt(Rxx(0) Ryy(0)).
            // e.g. see p 114-116 Ch.2 DSP Proakis/Manolakis 2nd Edition.
            
//            std::complex<float> leftVal(((FFT::Complex*)forwardLeftFFTData)[i].r, ((FFT::Complex*)forwardLeftFFTData)[i].i);
//            std::complex<float> rightVal(((FFT::Complex*)forwardRightFFTData)[i].r, ((FFT::Complex*)forwardRightFFTData)[i].i);
//            
//            std::complex<float> product = leftVal * rightVal;
//            ((FFT::Complex*)multipliedFFT)[i].r = product.real();
//            ((FFT::Complex*)multipliedFFT)[i].i = product.imag();
            
            // Now need energy of l and r
            leftEnergy += (leftChannelData[i] * leftChannelData[i]);
            rightEnergy += (rightChannelData[i] * rightChannelData[i]);
            Rxy0 += leftChannelData[i] * rightChannelData[i];
        
            // ************ Headroom! ************

            headroomBreached = (std::abs(leftChannelData[i]) > 0.5 || std::abs(rightChannelData[i]) > 0.5) ? true : false;

            
            // Get the maximum sample in this block for dynamic range calculation.
            if (blockMax < std::abs(leftChannelData[i]))
            {
                blockMax = std::abs(leftChannelData[i]);
            }
            if (blockMax < std::abs(rightChannelData[i]))
            {
                blockMax = std::abs(rightChannelData[i]);
            }
            
            float frameSum = leftChannelData[i] + rightChannelData[i];
            blockAbsFrameSum += (std::abs(leftChannelData[i]) + std::abs(rightChannelData[i]));
            
            // ************ Mono playback! ************
            if (mono)
            {
                float frameSumAverage = frameSum / 2.f;
            
                leftChannelData[i] = frameSumAverage;
                rightChannelData[i] = frameSumAverage;
                
            }
            
            // ************ Vectorscope ************
            if (i % vectorScopeStride == 0)
            {
                vectorScopePoints[vectorScopeCounter++] = juce::Point<float>(leftChannelData[i], rightChannelData[i]);
            }
            
            // ************ Bass space ************
            
            // Apply Linkwitz-Riley filter
            
            if (i <=2)
            {
                
            }
            
            // Apply filter to left channel: y(n) = a0 * x(n) + a1 * x(n-1) + a2 * x(n-2) - b1 * y(n-1) - b2 * y(n-2).
            float leftChannelFiltered = a_0 * leftChannelData[i] + a_1 * x_1 + a_2 * x_2 - b_1 * y_1 - b_2 * y_2;
            y_2 = y_1;
            y_1 = leftChannelFiltered;
            x_2 = x_1;
            x_1 = leftChannelData[i];
            
//            leftChannelData[i] = leftChannelFiltered;
//            rightChannelData[i] = leftChannelFiltered;
            
            leftEnergyFiltered += (leftChannelFiltered * leftChannelFiltered);
        }
    }
    
    // Calculate inverse FFT for cross correlation un-normalised value.
//    inverseFFT->performRealOnlyInverseTransform(multipliedFFT);
    
    // Calculate RMS
    leftRMS = sqrtf(leftEnergy / numSamples);
    rightRMS = sqrtf(rightEnergy / numSamples);
    
    // For the filtered RMS.
    leftRMSFiltered = sqrtf(leftEnergyFiltered / numSamples);
    
    // Calculate average abs sample value for this block
    float blockAverageRMS = (leftRMS + rightRMS) / 2;
    
    // Again, see Proakis.
    if (leftEnergy == 0 || rightEnergy == 0)
    {
        stereoCorrelation = 0;
    } else
    {
        stereoCorrelation = Rxy0/(sqrtf(leftEnergy * rightEnergy));
    }
    
    if (dynamicRangeCounter < 100)
    {
        // Use this value to get dB, i.e. 20log(blockMax/blockAverage).
        if (blockAverageRMS == 0)
        {
            blockAverageRMS = 0.001;
        }
        if (blockMax == 0)
        {
            blockMax = 0.001;
        }

        dynamicRangeMax[dynamicRangeCounter] = blockMax;
        dynamicRangeAvg[dynamicRangeCounter] = blockAverageRMS;
//        std::cout << blockMax << " " <<  blockAverage << " " << std::endl;
        
        // For bass space. Get first four bins (after DC).
        for (int i = 0; i < 4; i++) {
            
            // Get the amplitude in dB.
            std::complex<float> val(((FFT::Complex*)forwardLeftFFTData)[i+1].r, ((FFT::Complex*)forwardLeftFFTData)[i+1].i);
            binAmplitudes[i][dynamicRangeCounter] = 20 * log10(std::abs(val) / (numSamples / 2.)) ;
            
        }
        
        // Also hold the leftRMSFiltered to use to 'normalise' the bass dB.
        leftRMSFilteredAverage[dynamicRangeCounter] = leftRMSFiltered;
        
    } else
    {
        // Notify the editor to check the average value of dynamicRange and stereo correlation.
        sendChangeMessage();
        dynamicRangeCounter = 0;
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
