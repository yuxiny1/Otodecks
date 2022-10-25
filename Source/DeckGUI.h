/*
  ==============================================================================

    DeckGUI.h
    Created: 30 Jan 2022 6:56:20pm
    Author:  Xinyi Yu

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "DJAudioPlayer.h"
#include "WaveformDisplay.h"

//==============================================================================
/*
*/
class DeckGUI  : public juce::Component,
                public juce::Button::Listener,
                public juce::Slider::Listener,
                public juce::FileDragAndDropTarget,
                public juce::Timer,
                public juce::LookAndFeel_V4

//abstract class, pure virtual function in it , cannot use timmer directly as a class
// you have to use pure virtual functiosn
{
public:
    DeckGUI(int _id,
            DJAudioPlayer* _player,
            juce::AudioFormatManager & formatManagerToUse,
            juce::AudioThumbnailCache & cacheToUse );
    
    ~DeckGUI() override;
    

    void buttonClicked(juce::Button *) override;
    void sliderValueChanged(juce::Slider *slider) override;


    void paint (juce::Graphics&) override;
    void resized() override;
    
    bool isInterestedInFileDrag (const juce::StringArray &files) override;
    void filesDropped(const juce::StringArray &files, int x, int y) override;

    void timerCallback() override;
    
    void drawRotarySlider (juce::Graphics& g, int x, int y, int width, int height, float sliderPos,
                           const float rotaryStartAngle, const float rotaryEndAngle, juce::Slider&) override;
    int colorFlag;

    
private:
    
    int id;
    
    juce::LookAndFeel_V4 otherLookAndFeel; 

    juce::TextButton playButton{"PLAY"};
    juce::TextButton stopButton{"STOP"};
    juce::TextButton loadButton{"LOAD"};
    
    juce::Label speedLabel;
    juce::Label posLabel;
    juce::Label volLabel;
    
    juce::Slider volSlider;
    juce::Slider speedSlider;
    juce::Slider posSlider;
    
    DJAudioPlayer* player;
    
    WaveformDisplay waveformDisplay;
    
    void loadFile(juce::URL audioURL);
    
    friend class PlaylistComponent;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DeckGUI)
};
