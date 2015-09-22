/*
  ==============================================================================

    This file was auto-generated by the Introjucer!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include <numeric>

//==============================================================================
TestPluginAudioProcessorEditor::TestPluginAudioProcessorEditor (TestPluginAudioProcessor& p)
    :   AudioProcessorEditor (p),
        headroomBreachedLabel("", "Headroom: OK"),
        dynamicRangeLabel("", "Dynamic Range: 0dB"),
        stereoCorrelationLabel("", "Stereo Correlation: 0"),
        resetButton("Reset"),
        monoButton("Mono")
{
    
    addAndMakeVisible(&logo);
    addAndMakeVisible(vectorScope);
    
    addAndMakeVisible(headroomBreachedLabel);
    headroomBreachedLabel.setFont (Font (15.0f));
    
    addAndMakeVisible(resetButton);
    resetButton.addListener(this);
    
    addAndMakeVisible(monoButton);
    monoButton.addListener(this);
    
    addAndMakeVisible(dynamicRangeLabel);
    dynamicRangeLabel.setFont (Font (15.0f));
    
    addAndMakeVisible(stereoCorrelationLabel);
    stereoCorrelationLabel.setFont(Font(15.0f));
    
    
    leftLevel.barCount = 20;
    leftLevel.minValue = 0;
    leftLevel.maxValue = 1;
    leftLevel.overBar = 11;
    leftLevel.step = 2;
    leftLevel.overColour = Colours::red;
    leftLevel.underColour = Colours::green;
    leftLevel.barColour = Colours::grey;
    addAndMakeVisible(leftLevel);
    
    rightLevel.barCount = 20;
    rightLevel.minValue = 0;
    rightLevel.maxValue = 1;
    rightLevel.overBar = 11;
    rightLevel.step = 2;
    rightLevel.overColour = Colours::red;
    rightLevel.underColour = Colours::green;
    rightLevel.barColour = Colours::grey;
    addAndMakeVisible(rightLevel);
    
    dynamicHeadroomLevel.barCount = 20;
    dynamicHeadroomLevel.minValue = 0;
    dynamicHeadroomLevel.maxValue = 20;
    dynamicHeadroomLevel.overBar = 6;
    dynamicHeadroomLevel.step = 2;
    dynamicHeadroomLevel.overColour = Colours::green; 
    dynamicHeadroomLevel.underColour = Colours::red;
    dynamicHeadroomLevel.barColour = Colours::grey;
    addAndMakeVisible(dynamicHeadroomLevel);
    
    stereoCorrelationLevel.barCount = 20;
    stereoCorrelationLevel.minValue = 0;
    stereoCorrelationLevel.maxValue = 2;
    stereoCorrelationLevel.overBar = 6;
    stereoCorrelationLevel.step = 2;
    stereoCorrelationLevel.overColour = Colours::green;
    stereoCorrelationLevel.underColour = Colours::red;
    stereoCorrelationLevel.barColour = Colours::grey;
    addAndMakeVisible(stereoCorrelationLevel);
    
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (1040, 410);
    
    getProcessor().addChangeListener(this);
    
    startTimer (50);
}

TestPluginAudioProcessorEditor::~TestPluginAudioProcessorEditor()
{
    getProcessor().removeChangeListener(this);
}

//==============================================================================
void TestPluginAudioProcessorEditor::paint (Graphics& g)
{
    
    g.fillAll (Colours::white);

//    g.setColour (Colours::black);
//    g.setFont (15.0f);
//    g.drawFittedText ("Hello World!", getLocalBounds(), Justification::centred, 1);
}

void TestPluginAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    logo.setBounds(0, 0, 540, 200);
    vectorScope.setBounds(550, 0, 192, 286);
    
    headroomBreachedLabel.setBounds(5, 350, 200, 40);
    leftLevel.setBounds(5, 250, 16, 100);
    rightLevel.setBounds(23, 250, 16, 100);
    
    dynamicRangeLabel.setBounds(205, 350, 200, 40);
    dynamicHeadroomLevel.setBounds(205, 250, 16, 100);
    
    stereoCorrelationLabel.setBounds(405, 350, 200, 40);
    stereoCorrelationLevel.setBounds(405, 250, 16, 100);
    
    resetButton.setBounds(5, 210, 50, 20);
    monoButton.setBounds(60, 210, 50, 20);
    
}



void TestPluginAudioProcessorEditor::buttonClicked(juce::Button * button)
{
    
    if (button == &resetButton)
    {
        this->reset();
        return;
    }
    
    if(button == &monoButton)
    {
        monoButton.setToggleState(!monoButton.getToggleState(), dontSendNotification);
        
        getProcessor().mono = monoButton.getToggleState();
    }
    
}


void TestPluginAudioProcessorEditor::timerCallback()
{
    TestPluginAudioProcessor& processor = getProcessor();
    
    if (processor.lastPosInfo.isPlaying)
    {
        vectosScopeFadeoutCount = 0;
        
        logo.setFFTBins(processor.logoFFTBins);
        logo.repaint();
        
        leftLevel.levelData = processor.leftRMS;
        rightLevel.levelData = processor.rightRMS;
        leftLevel.repaint();
        rightLevel.repaint();
        
        if (processor.headroomBreached)
        {
            headroomBreachedLabel.setText("Headroom: Breached", dontSendNotification);
        }
//        else
//        {
//            headroomBreachedLabel.setText("Headroom: OK", dontSendNotification);
//        }
        
        stereoCorrelationLevel.levelData = processor.stereoCorrelation + 1;
        stereoCorrelationLevel.repaint();
        stereoCorrelationLabel.setText("Stereo Correlation: " + String(processor.stereoCorrelation), dontSendNotification);
        
        vectorScope.setCurrentPointArray(processor.vectorScopePoints);
        vectorScope.repaint();
        
    } else
    {
        
        if (vectosScopeFadeoutCount < numberVectorBuffers)
        {
            // Seems like we have just stopped playing so fade out vectorscope.
            vectorScope.setCurrentPointArray(std::array<juce::Point<float>, 100>{ juce::Point<float>(0,0) });
            vectosScopeFadeoutCount++;
            
            vectorScope.repaint();
        }
        
        // Reset the logo
        logo.setFFTBins({ 10, 20, 30, 40, 40, 30, 20, 10 });
        
        logo.repaint();
    }
}

void TestPluginAudioProcessorEditor::changeListenerCallback(juce::ChangeBroadcaster *source)
{
    // We have been notified to check the dynamicRange array.
    TestPluginAudioProcessor& processor = static_cast<TestPluginAudioProcessor&>(*source);
    
    // Get the average of the dynamicRange, note this is still being changed by the audio thread,
    // but this is only a heuristic method anyway.
    float averageDynamicRange = std::accumulate(processor.dynamicRange.begin(), processor.dynamicRange.end(), 0.0) / 100.;

    dynamicHeadroomLevel.levelData = 20 * log10f(averageDynamicRange);
    dynamicHeadroomLevel.repaint();

    dynamicRangeLabel.setText("Dynamic Range: " + String(20 * log10f(averageDynamicRange)), dontSendNotification);
    
}

void TestPluginAudioProcessorEditor::reset()
{
    TestPluginAudioProcessor& processor = getProcessor();
    
    processor.headroomBreached = false;
    
    headroomBreachedLabel.setText("Headroom: OK", dontSendNotification);
}