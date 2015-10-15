//
//  VectorScope.h
//  MasteringExpert
//
//  Created by Anthony Nash on 18/09/2015.
//
//

#ifndef __MasteringExpert__VectorScope__
#define __MasteringExpert__VectorScope__


#include "JuceHeader.h"
#include "Settings.h"

#include <array>
#include <stdio.h>


class VectorScope  : public Component
{
public:
   
    enum class Mode {
        
        LISSAJOUS,
        POLAR
        
    };
    
    VectorScope (Mode mode);
    ~VectorScope();
    
    void paint (Graphics& g);
    void resized();
    
   
    void setCurrentPointArray(std::array<juce::Point<float> , UIConstants::NUMBER_SCOPE_POINTS>);
    
    // Radius if this a polar sample vectorscope.
    float radius;
    
    Mode mode;
    
private:
    
    // Normalise the magnitude of the points.
    void normalisePoints();
    
    // Draw the outline of the scope.
    void drawScope(Graphics&, Path&, float xOffset, float yOffset);
    
    void drawPoints(Graphics&, float xOffset, float yOffset);
    
    // An array of 5 arrays of Point arrays!
    std::array<std::array<juce::Point<float> , UIConstants::NUMBER_SCOPE_POINTS>, UIConstants::NUMBER_SCOPE_BUFFERS> allPoints { { juce::Point<float>(0,0) } };
    
    // Which points are the latest to display.
    int currentPointsIndex = 0;
    
    Path logoPath;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (VectorScope)
};



#endif /* defined(__MasteringExpert__VectorScope__) */
