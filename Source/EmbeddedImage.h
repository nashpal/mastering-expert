/*
  ==============================================================================

  This is an automatically generated GUI class created by the Introjucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Introjucer version: 3.2.0

  ------------------------------------------------------------------------------

  The Introjucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright (c) 2015 - ROLI Ltd.

  ==============================================================================
*/

#ifndef __JUCE_HEADER_1FBB470E3B653A36__
#define __JUCE_HEADER_1FBB470E3B653A36__

//[Headers]     -- You can add your own extra header files here --
#include "JuceHeader.h"
#include <array>

//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Introjucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class EmbeddedImage  : public Component
{
public:
    //==============================================================================
    EmbeddedImage ();
    ~EmbeddedImage();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    void setFFTBins(std::array<float, 8> fftBins);
    //[/UserMethods]

    void paint (Graphics& g);
    void resized();

    // Binary resources:
    static const char* logo_png;
    static const int logo_pngSize;
    
    static const char* logo_svg;
    static const int logo_svgSize;
    
    Path logoPath;
    Path maskPath;


private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    std::array<float, 8> fftBins { 10, 20, 30, 40, 40, 30, 20, 10 };
    //[/UserVariables]

    //==============================================================================
    ScopedPointer<ImageComponent> image;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (EmbeddedImage)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif   // __JUCE_HEADER_1FBB470E3B653A36__
