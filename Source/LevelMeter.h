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



class LevelMeter  : public Component
{
public:
    
    LevelMeter ();
    ~LevelMeter();
    
    void paint (Graphics& g);
    void resized();
    
    // At which bar is this an over.
    int overBar;
    Colour overColour;
    Colour underColour;
    
    // How many bars to display
    int barCount;
    
    // How many pixels between each bar;
    int step;
    
    float levelData;
    
    float maxValue;
    float minValue;
    
private:
    
    float scale;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LevelMeter)
};

#endif /* defined(__MasteringExpert__LevelMeter__) */
