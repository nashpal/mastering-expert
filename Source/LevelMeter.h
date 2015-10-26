//
//  LevelMeter.h
//  MasteringExpert
//
//  Created by Anthony Nash on 21/09/2015.
//
//

#ifndef __MasteringExpert__LevelMeter__
#define __MasteringExpert__LevelMeter__

#include <stdio.h>
#include "JuceHeader.h"

enum class MeterType
{
    NORMAL,
    DYNAMICRANGE,
    CORRRELATION,
    STEREOBALANCE
};

enum class MeterOrientation
{
    VERTICAL,
    HORIZONTAL
};

class LevelMeter  : public Component
{
public:
    
    LevelMeter (String bottomLabelText, String midLabelText, String topLabelText);
    ~LevelMeter();
    
    void paint (Graphics& g);
    void resized();
    
    // At which bar is this an over.
    int overBar;
    Colour overColour;
    Colour underColour;
    Colour barColour;
    
    // How many bars to display
    int barCount;
    
    // How many pixels between each bar;
    int step;
    
    float levelData;
    
    float maxValue;
    float minValue;
    
    float barLength;
    
    MeterType meterType;
    MeterOrientation meterOrientation = MeterOrientation::VERTICAL;

    Label minLabel;
    Label midLabel;
    Label maxLabel;
    
private:
    
    
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LevelMeter)
};

#endif /* defined(__MasteringExpert__LevelMeter__) */
