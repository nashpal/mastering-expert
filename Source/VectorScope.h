//
//  VectorScope.h
//  MasteringExpert
//
//  Created by Anthony Nash on 18/09/2015.
//
//

#ifndef __MasteringExpert__VectorScope__
#define __MasteringExpert__VectorScope__

#include <stdio.h>
#include "JuceHeader.h"
#include <array>
class VectorScope  : public Component
{
public:
   
    VectorScope ();
    ~VectorScope();
    
    void paint (Graphics& g);
    void resized();
    
   
    void setCurrentPointArray(std::array<juce::Point<float> , 100>);
    
private:
    
    // An array of 5 arrays of Point arrays!
    std::array<std::array<juce::Point<float> , 100>, 5> allPoints { { juce::Point<float>(0,0) } };
    
    // Which points are the lates to display.
    int currentPointsIndex = 0;
    
//    ScopedPointer<ImageComponent> image;
    

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (VectorScope)
};



#endif /* defined(__MasteringExpert__VectorScope__) */
