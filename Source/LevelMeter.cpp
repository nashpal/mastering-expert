//
//  LevelMeter.cpp
//  MasteringExpert
//
//  Created by Anthony Nash on 21/09/2015.
//
//

#include "LevelMeter.h"

LevelMeter::LevelMeter ()
{
    
//    setSize (277, 394);
    
}

LevelMeter::~LevelMeter()
{
    
}

//==============================================================================
void LevelMeter::paint (Graphics& g)
{
    
    g.fillAll (Colours::white);
    
    //[UserPaint] Add your own custom painting code here..
    Path wavePath;
    
    int barHeight = (getBounds().getHeight() - ((barCount - 1) * step)) / barCount;
    int barWidth = getBounds().getWidth();
    int xOffset = 0;
    int yOffset = getBounds().getHeight();
    
    int currentBarCount = levelData / (maxValue - minValue) * barCount;
    
    int x, y;
    
    x = xOffset;
    y = yOffset;
    
    for (int count = 1; count <= barCount; count++) {
        
        if (count <= currentBarCount)
        {
            if (count < overBar)
                g.setColour (underColour);
            else
                g.setColour (overColour);
        } else
        {
            g.setColour (barColour);
        }
        g.drawLine(x, y, x+barWidth, y, barHeight);
//        wavePath.addLineSegment (Line<float> (x, y, x + barWidth, y), barHeight);
        
        y -= (step + barHeight);
    }

    g.fillPath (wavePath);
    
}

void LevelMeter::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]
    
    //    image->setBounds (0, 50, 450, 159);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

