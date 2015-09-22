/*
  ==============================================================================

    This file was auto-generated by the Introjucer!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#ifndef PLUGINPROCESSOR_H_INCLUDED
#define PLUGINPROCESSOR_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include <array>



//==============================================================================
/**
*/
class TestPluginAudioProcessor : public AudioProcessor,
                                 public ChangeBroadcaster
{
public:
    //==============================================================================
    TestPluginAudioProcessor();
    ~TestPluginAudioProcessor();

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

    void processBlock (AudioSampleBuffer&, MidiBuffer&) override;

    //==============================================================================
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const String getName() const override;

    const String getInputChannelName (int channelIndex) const override;
    const String getOutputChannelName (int channelIndex) const override;
    bool isInputChannelStereoPair (int index) const override;
    bool isOutputChannelStereoPair (int index) const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool silenceInProducesSilenceOut() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;

    //==============================================================================
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    
    // Our parameters
    AudioProcessorParameter* gain;
    
    enum class ShortFFT : int
    {
        Order = 9,
        Size  = 1 << Order
    };
    
    enum class LongFFT : int
    {
        Order = 10,
        Size  = 1 << Order
    };

    std::array<float, 8> logoFFTBins;
    
    // Points for vector scope.
    std::array<juce::Point<float>, numberVectorPoints> vectorScopePoints;
    
    bool headroomBreached = false;
    
    AudioPlayHead::CurrentPositionInfo lastPosInfo;
    
    // Determine whether to sum stereo;
    bool mono = false;
    
    // TODO: Change name of this var.
    // How many dynmaic range measurements have we taken.
    int dynamicRangeCounter = 0;
    
    // Hold the dynmaic range for 100 blocks.
    std::array<float, 100>  dynamicRange {};

    // Hold the stereo correlation. Using convolution method.
    float stereoCorrelation;
    
    float leftRMS;
    float rightRMS;
    
private:
    
    // Used for logo
    FFT* forwardFFT;
    FFT* inverseFFT;
    
    float* forwardLeftFFTData;
    float* forwardRightFFTData;
    
    // Used to hold result of multilying l and r for correlation.
    float* multipliedFFT;
        
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TestPluginAudioProcessor)
};


#endif  // PLUGINPROCESSOR_H_INCLUDED
