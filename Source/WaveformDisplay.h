/*
  ==============================================================================
    WaveformDisplay.h
    Created: 13 Feb 2022 7:13:13pm
    Author:  Xinyi Yu
  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class WaveformDisplay  : public juce::Component,
                     public juce::ChangeListener
{
public:
    WaveformDisplay( int _id,
                    juce::AudioFormatManager & formatManagerToUse,
                     juce::AudioThumbnailCache & cacheToUse);
    ~WaveformDisplay() override;

    void paint (juce::Graphics&) override;
    
    void resized() override;
    
    void changeListenerCallback (juce::ChangeBroadcaster *source) override;
    
    void loadURL(juce::URL audioURL);
    
    void setPositionRelative(double pos);
    
private:
    
    int id;

    juce::AudioThumbnail audioThumb;
    
    bool fileLoaded;
    
    double position;

    //    juce::string fileName;
//    juce::AudioThumbnail audioThumb;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (WaveformDisplay)
};
