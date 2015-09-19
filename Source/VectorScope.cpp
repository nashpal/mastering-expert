//
//  VectorScope.cpp
//  MasteringExpert
//
//  Created by Anthony Nash on 18/09/2015.
//
//

#include "VectorScope.h"

//==============================================================================
VectorScope::VectorScope ()
{
    
    
    setSize (410, 410);
    
}

VectorScope::~VectorScope()
{
    
}

//==============================================================================
void VectorScope::paint (Graphics& g)
{
    
    g.fillAll (Colours::white);
    
    Path diamondPath;
    
    float xOffset = 5.f;
    float yOffset = 5.f;
    
    // Draw the diamond.
    float sqrt2 = sqrtf(2);
   
    diamondPath.startNewSubPath (200 + xOffset, 0 + yOffset);
    diamondPath.lineTo (200 + xOffset + 100 * sqrt2, 0 + yOffset + 100 * sqrt2);
    diamondPath.lineTo(200 + xOffset, 0 + yOffset + 200 * sqrt2);
    diamondPath.lineTo(200 + xOffset - 100 * sqrt2, 0 + yOffset + 100 * sqrt2);
    diamondPath.closeSubPath();
    
    g.setColour (Colours::orange);
    g.strokePath(diamondPath, {4., juce::PathStrokeType::curved},AffineTransform::identity);
    
    Path vectorScopePath;
    // Now iterate over points.
    int count = 0;
    for (auto& points : allPoints)
    {
        float alpha = 1 - ((currentPointsIndex - count + 5) % 5) * 0.2;
        g.setColour(Colour::fromFloatRGBA(1., 0.65 , 0, alpha)) ;
        
        for (auto& point : points)
        {
//            g.setPixel(200 + point.x * 100, 200 - point.y * 100);
            vectorScopePath.addEllipse(200 + point.x * 100, 200 - point.y * 100, 5, 5);
        }
        count++;
    }
    
    g.fillPath(vectorScopePath, AffineTransform::rotation(-M_PI / 4, 200, 200));
    
}

void VectorScope::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]
    
    //    image->setBounds (0, 50, 450, 159);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void VectorScope::setCurrentPointArray(std::array<juce::Point<float>, 100> currentPoints)
{
    allPoints[currentPointsIndex] = currentPoints;
    currentPointsIndex = (currentPointsIndex + 1) % 5;
}


