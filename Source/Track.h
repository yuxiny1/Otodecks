/*
  ==============================================================================

    Track.h
    Created: 25 Mar 2022 2:59:03pm
    Author:  Xinyi Yu

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class Track
{
    public:
        Track(juce::File _file);
        juce::File file;
        juce::URL URL;
        juce::String title;
        juce::String length;
    
    bool operator==(const juce::String& other)const;
};
