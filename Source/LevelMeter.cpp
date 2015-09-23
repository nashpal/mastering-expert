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
    

    bottomLabel.setJustificationType(juce::Justification::left);
    bottomLabel.setText(bottomLabelText, dontSendNotification);
    addAndMakeVisible(bottomLabel);
    bottomLabel.setFont (Font (10.0f));
    
    midLabel.setJustificationType(juce::Justification::left);
    midLabel.setText(midLabelText, dontSendNotification);
    addAndMakeVisible(midLabel);
    midLabel.setFont (Font (10.0f));
    
    topLabel.setJustificationType(juce::Justification::left);
    topLabel.setText(topLabelText, dontSendNotification);
    addAndMakeVisible(topLabel);
    topLabel.setFont (Font (10.0f));
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
    int xOffset = 0;
    int yOffset = getBounds().getHeight();
    
    int currentBarCount = levelData / (maxValue - minValue) * barCount;
    
    int x, y;
    
    x = xOffset;
    y = yOffset;
    
    
    if (meterType == MeterType::CORRRELATION)
    {
        // Draw background bars.
        g.setColour (barColour);
        
        for (int count = 1; count <= barCount; count++)
        {
            g.drawLine(x, y, x+barWidth, y, barHeight);
            y -= (step + barHeight);
        }
        
        y = yOffset - currentBarCount * (step + barHeight);
        
        // Now draw the correlation bar.
        if (currentBarCount >= overBar)
        {
            g.setColour (underColour);
        }
        else
        {
            g.setColour (overColour);
        }
        
        g.drawLine(x, y, x+barWidth, y, barHeight);
    }
    else
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
                   
            g.drawLine(x, y, x+barWidth, y, barHeight);
            
            y -= (step + barHeight);
        }
        
    }

    g.fillPath (wavePath);
    
}

void LevelMeter::resized()
{
    bottomLabel.setBounds(barWidth + 4, getBounds().getHeight() - 15, 30, 20);
    midLabel.setBounds(barWidth + 4, getBounds().getHeight() / 2. - 10, 30, 20);
    topLabel.setBounds(barWidth + 4, 0, 30, 20);
}

