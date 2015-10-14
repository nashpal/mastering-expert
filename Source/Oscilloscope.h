/*
  ==============================================================================

    Oscilloscope.h
    Created: 12 Oct 2015 4:32:52pm
    Author:  Anthony Nash

  ==============================================================================
*/

#ifndef OSCILLOSCOPE_H_INCLUDED
#define OSCILLOSCOPE_H_INCLUDED

#include "JuceHeader.h"
#include "Settings.h"

#include <array>

class Oscilloscope : public Component
{
    
public:
    
    Oscilloscope ();
    ~Oscilloscope();
    
    void paint (Graphics& g);
    void resized();
    
    
    void setCurrentPointArray(std::array<juce::Point<float> , UIConstants::NUMBER_SCOPE_POINTS>);
    
    
private:
    
    // Normalise the magnitude of the points.
    void normalisePoints();
    
    // An array of 5 arrays of Point arrays!
    std::array<std::array<juce::Point<float> , UIConstants::NUMBER_SCOPE_POINTS>, UIConstants::NUMBER_SCOPE_BUFFERS> allPoints { { juce::Point<float>(0,0) } };
    
    // Which points are the latest to display.
    int currentPointsIndex = 0;
    
    Path logoPath;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Oscilloscope)
};


#endif  // OSCILLOSCOPE_H_INCLUDED
