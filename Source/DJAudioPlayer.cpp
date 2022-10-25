/*
  ==============================================================================

    DJAudioPlayer.cpp
    Created: 30 Jan 2022 11:11:32am
    Author:  Xinyi Yu

  ==============================================================================
*/
#include "DJAudioPlayer.h"

DJAudioPlayer::DJAudioPlayer(juce::AudioFormatManager& _formatManager)
: formatManager(_formatManager)
{
}

DJAudioPlayer::~DJAudioPlayer(){
}

void DJAudioPlayer::prepareToPlay (int samplesPerBlockExpected, double sampleRate)
{
    transportSource.prepareToPlay(samplesPerBlockExpected,sampleRate);
    resampleSource.prepareToPlay(samplesPerBlockExpected,sampleRate);    
}

void DJAudioPlayer::getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill)
{
    transportSource.getNextAudioBlock(bufferToFill);
    resampleSource.getNextAudioBlock(bufferToFill);
}

void DJAudioPlayer::releaseResources()
{
    transportSource.releaseResources();
    resampleSource.releaseResources();
}

void DJAudioPlayer::setGain(double gain)
{
    if(gain <0 || gain > 1.0)
    {
        std::cout<<" DJauiodplayer::setgain should be between 0 and 1 "<<std::endl;
    }
    else {
        transportSource.setGain(gain);
    }
}

void DJAudioPlayer::setSpeed(double ratio)
{
    if(ratio <0 || ratio > 100.0)
    {
        std::cout<<" DJauiodplayer::speed should be between 0 and 10 "<<std::endl;
    }
    else {
        resampleSource.setResamplingRatio(ratio);
    }
}

void DJAudioPlayer::setPosition(double posInSecs)
{
    transportSource.setPosition(posInSecs);
}

void DJAudioPlayer::setPositionRelative(double pos)
{
    if (pos < 0 || pos> 1.0)
    {
        std::cout<<"DJaiod player :; setPosition Relative erro"<<std::endl;
    }
    else {
        double posInSecs = transportSource.getLengthInSeconds()* pos;
        setPosition(posInSecs);
    }
}

void DJAudioPlayer::start()
{
    transportSource.start();
    
}
void DJAudioPlayer::stop()
{
    transportSource.stop();
}

void DJAudioPlayer::loadURL(juce::URL audioURL)
{
    auto* reader =formatManager.createReaderFor(audioURL.createInputStream(false));
//if it goes worng it will eraze the memoery
        if(reader !=nullptr) //good file !
        {
    std::unique_ptr<juce::AudioFormatReaderSource> newSource (new juce::AudioFormatReaderSource (reader,true));

            //pass reader to transport source
            transportSource.setSource(newSource.get(),
                              0,
                              nullptr,
                              reader->sampleRate);
            /* becasue it is unique pointer smart only one ownership, one pointer , this is class scope variable which menas we can retain acces to it becasue we need to play */
            readerSource.reset(newSource.release());
            transportSource.start();
    }
    }

double DJAudioPlayer::getPositionRelative()
{
    return transportSource.getCurrentPosition() / transportSource.getLengthInSeconds();
}

double DJAudioPlayer::getLengthInSeconds()
{
    return transportSource.getLengthInSeconds();
}

