//
//  LevelMeter.cpp
//  MasteringExpert
//
//  Created by Anthony Nash on 21/09/2015.
//
//

#include "LevelMeter.h"

LevelMeter::LevelMeter (String bottomLabelText, String midLabelText, String topLabelText)
{
    

    minLabel.setJustificationType(juce::Justification::left);
    minLabel.setText(bottomLabelText, dontSendNotification);
    addAndMakeVisible(minLabel);
    minLabel.setFont (Font (10.0f));
    
    midLabel.setJustificationType(juce::Justification::left);
    midLabel.setText(midLabelText, dontSendNotification);
    addAndMakeVisible(midLabel);
    midLabel.setFont (Font (10.0f));
    
    maxLabel.setJustificationType(juce::Justification::left);
    maxLabel.setText(topLabelText, dontSendNotification);
    addAndMakeVisible(maxLabel);
    maxLabel.setFont (Font (10.0f));
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
    
    int barThickness = 0;
    int xOffset = 0;
    int yOffset = getBounds().getHeight();
    
    int currentBarCount = levelData / (maxValue - minValue) * barCount;
    
    int x, y;
    
    x = xOffset;
    y = yOffset;
    
    switch (meterOrientation) {
        case MeterOrientation::VERTICAL:
            
            barThickness = (getBounds().getHeight() - ((barCount - 1) * step)) / barCount;
            break;
        case MeterOrientation::HORIZONTAL:
            barThickness = (getBounds().getWidth() - ((barCount - 1) * step)) / barCount;
            
        default:
            break;
    }
    
    if (meterType == MeterType::CORRRELATION)
    {
        
        
        // Draw background bars.
        g.setColour (barColour);
        
        for (int count = 1; count <= barCount; count++)
        {
            g.drawLine(x, y, x + barLength, y, barThickness);
            y -= (step + barThickness);
        }
        
        y = yOffset - currentBarCount * (step + barThickness);
        
        // Now draw the correlation bar.
        if (currentBarCount >= overBar)
        {
            g.setColour (underColour);
        }
        else
        {
            g.setColour (overColour);
        }
        
        g.drawLine(x, y, x + barLength, y, barThickness);
    }
    else if (meterType == MeterType::STEREOBALANCE)
    {
        
        // Draw background bars.
        g.setColour (barColour);
        
        for (int count = 1; count <= barCount; count++)
        {
            g.drawLine(x, y, x, y - barLength, barThickness);
            x += (step + barThickness);
        }
        
        x = xOffset + currentBarCount * (step + barThickness);
        
        // Now draw the balance bar.
        g.setColour (underColour);
        
        g.drawLine(x, y, x, y - barLength, barThickness);
 
        
    } else
    {
    
        for (int count = 1; count <= barCount; count++)
        {
            
            switch (meterType) {
                    
                case MeterType::NORMAL:
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

                    break;
                    
                case MeterType::DYNAMICRANGE:
                    
                    if (count <= currentBarCount)
                    {
                        // If level is over then set all bars to over colour
                        if (currentBarCount >= overBar)
                        {
                            g.setColour(underColour);
                        } else{
                            g.setColour(overColour);
                        }
                    } else
                    {
                        g.setColour (barColour);
                    }
                    
                    break;
                    
                default:
                    break;
            }
                   
            g.drawLine(x, y, x + barLength, y, barThickness);
            
            y -= (step + barThickness);
        }
        
    }

    g.fillPath (wavePath);
    
}

void LevelMeter::resized()
{
    switch (meterOrientation) {
        case MeterOrientation::VERTICAL:
            
            minLabel.setBounds(barLength + 4, getBounds().getHeight() - 15, 30, 20);
            midLabel.setBounds(barLength + 4, getBounds().getHeight() / 2. - 10, 30, 20);
            maxLabel.setBounds(barLength + 4, 0, 30, 20);

            break;
        case MeterOrientation::HORIZONTAL:
            
            minLabel.setBounds(0, 0, 30, 20);
            midLabel.setBounds(getBounds().getWidth() / 2. - 10, 0, 30, 20);
            maxLabel.setBounds(getBounds().getWidth() - 15, 0, 30, 20);
        default:
            break;
    }
    
}

