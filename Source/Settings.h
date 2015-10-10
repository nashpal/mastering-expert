/*
  ==============================================================================

    Settings.h
    Created: 25 Sep 2015 11:58:52am
    Author:  Anthony Nash

  ==============================================================================
*/

#ifndef SETTINGS_H_INCLUDED
#define SETTINGS_H_INCLUDED

#define FLT_MIN_PLUS          1.175494351e-38         /* min positive value */
#define FLT_MIN_MINUS        -1.175494351e-38         /* min negative value */

// Used for vectorscope configuration.
const int NUMBER_VECTOR_POINTS = 100;
const int NUMBER_VECTOR_BUFFERS = 20;

// Messaging from processor.
const juce::String DYNAMIC_RANGE_MESSAGE("DynamicRangeChange");
const juce::String LUFS_MESSAGE("LUFSChange");
const juce::String BASS_SPACE_MESSAGE("BassSpaceChange");

#endif  // SETTINGS_H_INCLUDED
