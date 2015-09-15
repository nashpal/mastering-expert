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

const float defaultGain = 1.0f;

class FloatParameter : public AudioProcessorParameter
{
public:
    
    FloatParameter (float defaultParameterValue, const String& paramName)
    : defaultValue (defaultParameterValue),
    value (defaultParameterValue),
    name (paramName)
    {
    }
    
    float getValue() const override
    {
        return value;
    }
    
    void setValue (float newValue) override
    {
        value = newValue;
    }
    
    float getDefaultValue() const override
    {
        return defaultValue;
    }
    
    String getName (int maximumStringLength) const override
    {
        return name;
    }
    
    String getLabel() const override
    {
        return String();
    }
    
    float getValueForText (const String& text) const override
    {
        return text.getFloatValue();
    }
    
private:
    float defaultValue, value;
    String name;
};

//==============================================================================
/**
*/
class TestPluginAudioProcessor  : public AudioProcessor
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
        Order = 7,
        Size  = 1 << Order
    };
    
    enum class LongFFT : int
    {
        Order = 10,
        Size  = 1 << Order
    };

    std::array<float, 8> logoFFTBins;
    
private:
    
    // Used for logo
    FFT shortFFT;
    
    // Used for analysis.
    FFT longFFT;
    
    float shortFFTData [2 * int(ShortFFT::Size)];
    float longFFTData [2 * int(LongFFT::Size)];
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TestPluginAudioProcessor)
};


#endif  // PLUGINPROCESSOR_H_INCLUDED
