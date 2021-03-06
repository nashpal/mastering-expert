/*
  ==============================================================================

    This file was auto-generated by the Introjucer!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#ifndef PLUGINEDITOR_H_INCLUDED
#define PLUGINEDITOR_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
#include "EmbeddedImage.h"
#include "VectorScope.h"
#include "Oscilloscope.h"
#include "LevelMeter.h"
#include "Settings.h"

//==============================================================================
/**
*/
class TestPluginAudioProcessorEditor  : public AudioProcessorEditor,
                                        public Button::Listener,
                                        public ActionListener, // For infrequent broadcasts from processor.
                                        public Timer
{
public:
    TestPluginAudioProcessorEditor (TestPluginAudioProcessor&);
    ~TestPluginAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;
    
    void buttonClicked      (Button*) override;
    
    void actionListenerCallback (const String& message) override;
    
    void timerCallback() override;

private:

    // Reset display.
    void reset();
    
    // Hide all components.
    void hideComponents();
    
    // Show main components including nav buttons, hyper link.
    void showComponents();
    
    EmbeddedImage logo;
    VectorScope vectorScope;
    Oscilloscope oscilloScope;
    
    Label headroomBreachedLabel;
    Label lufsMomentaryLoudnessLabel;
    Label lufsShortTermLoudnessLabel;
    Label rmsLabel;
    Label peakLabel;
    Label dynamicRangeLabel;
    Label stereoCorrelationLabel;
    Label bassSpaceLabel;
    
    TextButton homeButton;
    
    TextButton headroomButton;
    TextButton dynamicRangeButton;
    TextButton stereoButton;
    TextButton bassSpaceButton;
    
    TextButton resetButton;
    TextButton monoButton;
    TextButton leftButton;
    TextButton rightButton;
    
    TextButton bassSoloButton;
    
    LevelMeter leftLevel;
    LevelMeter rightLevel;
    LevelMeter dynamicRangeLeftLevel;
    LevelMeter dynamicRangeRightLevel;
    
    LevelMeter stereoCorrelationLevel;
    LevelMeter stereoBalance;
    
    Label freq1Label;
    Label freq2Label;
    Label freq3Label;
    Label freq4Label;
    
    LevelMeter freq1BassSpaceLevel;
    LevelMeter freq2BassSpaceLevel;
    LevelMeter freq3BassSpaceLevel;
    LevelMeter freq4BassSpaceLevel;
    
    Label blockSizeLabel;
    
    HyperlinkButton hyperLink;
    
    // Need to fade out 'scopes if play has stopped.
    int scopeFadeoutCount = 0;
    
    TestPluginAudioProcessor& getProcessor() const
    {
        return static_cast<TestPluginAudioProcessor&> (processor);
    }
    
    // This will hold the sum of energy for 100ms blocks for 400ms Momentary Loudness.
    std::array<float, 4> lufsMomentaryLoudnessEnergyBlocks;
    int lufsBlockCount = 0;
    
    // This will hold the sum of energy for 100ms blocks for 3s Short Term Loudness.
    std::array<float, 30> lufsShortTermLoudnessEnergyBlocks;
    
    // Hold a vector of short term loudness values to calculate the Loudness Range.
    std::array<float, 100> lufsShortTermLoudness;
    
    int dynamicRangeBlockCount = 0;
    
    // Hold a vector of 30 most recent left/right peaks for dynamic range calc.
    std::array<float, 50> dynamicRangeLeftPeaks;
    std::array<float, 50> dynamicRangeRightPeaks;
    
    // Hold a vector of 30 most recent left/right RMS for dynamic range calc.
    std::array<float, 50> dynamicRangeLeftRMS;
    std::array<float, 50> dynamicRangeRightRMS;
    
    // Resizable array of lufs short term loudness values that are > LUFS_ABSOLUTE_TRESHOLD and < LUFS_RELATIVE_THRESHOLD
    std::vector<float> lufsAbsoluteGated;
    
    // Resizable array of lufs short term loudness values that are < LUFS_RELATIVE_THRESHOLD
    std::vector<float> lufsRelativeGated;
    
    std::vector<float> lufsLogRemoved;
    
    // LUFS loudness range constants.
    const float LUFS_ABSOLUTE_THRESHOLD = -70;
    const float LUFS_RELATIVE_THRESHOLD = -20;
    const float LUFS_LOWER_PERCENTILE = 10;
    const float LUFS_UPPER_PERCENTILE = 95;
    
    UIConstants::Mode mode = UIConstants::Mode::DYNAMIC_RANGE;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TestPluginAudioProcessorEditor)
};


#endif  // PLUGINEDITOR_H_INCLUDED
