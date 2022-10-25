/*
  ==============================================================================
    DJAudioPlayer.h
    Created: 30 Jan 2022 11:11:32am
    Author:  Xinyi Yu
  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>


class DJAudioPlayer : public juce::AudioSource
{
public:
    DJAudioPlayer(juce::AudioFormatManager& _formatManager);
    
    ~DJAudioPlayer();
    
    void prepareToPlay(int samplePerBlockExpected, double sampleRate) override;
    
    void getNextAudioBlock (const juce::AudioSourceChannelInfo& bufferToFill) override;
    
    void releaseResources() override;
    
    void loadURL(juce::URL audioURL);
    
    void setGain(double gain);
    
    void setSpeed(double ratio);
    
    void setPosition(double posInSecs);
    
    void start();
    
    void stop();
    
    double getLengthInSeconds();
    
    void setPositionRelative(double pos);
    
    /* get the relative poistion of the playhead */
    double getPositionRelative();
//    void registerBasicFormats();
    
private :
    
    juce::AudioFormatManager& formatManager;
    
    std::unique_ptr<juce::AudioFormatReaderSource> readerSource;
    
    juce::AudioTransportSource transportSource;
    
    juce::ResamplingAudioSource resampleSource{&transportSource, false, 2};
    
};
