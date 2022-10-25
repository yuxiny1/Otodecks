/*
  ==============================================================================

    WaveformDisplay.cpp
    Created: 13 Feb 2022 7:13:13pm
    Author:  Xinyi Yu

  ==============================================================================
*/

#include <JuceHeader.h>
#include "WaveformDisplay.h"

//==============================================================================
WaveformDisplay::WaveformDisplay(int _id,
                                 juce::AudioFormatManager & formatManagerToUser,
                                 juce::AudioThumbnailCache & cacheToUse
                                 ) :
                                 audioThumb(1000, formatManagerToUser, cacheToUse),
                                fileLoaded(false),
                                position(0),
                                id(_id)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    audioThumb.addChangeListener(this);
}

WaveformDisplay::~WaveformDisplay()
{
}

void WaveformDisplay::paint (juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background

    g.setColour (juce::Colours::pink);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

    g.setColour (juce::Colours::orange);
    
    if(fileLoaded)
    {
        audioThumb.drawChannel(g
                               , getLocalBounds()
                               , 0
                               , audioThumb.getTotalLength()
                               , 0
                               , 1.0f);
        g.setColour(juce::Colours::lightpink);
        g.drawRect(position* getWidth(), 0, getWidth()/20 , getHeight());
    }
    
    else
    {
        g.setFont (20.0f);
        g.drawText (" i am hungry Feed me some music ", getLocalBounds(),
                    juce::Justification::centred, true);   // draw some placeholder text
        
    }
    
}

void WaveformDisplay::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}

void WaveformDisplay::loadURL(juce::URL audioURL)
{
    std::cout<<"wfd: loadURL"<<std::endl;
    
    audioThumb.clear();
    
    fileLoaded = audioThumb.setSource(new juce::URLInputSource(audioURL));
    if(fileLoaded)
    {
        std::cout<<"wfd:loaded "<< std::endl;
        repaint();
        
    }
    else{
        std::cout<<"wfd:not loaded!" <<std::endl;
    }
}



void WaveformDisplay::changeListenerCallback(juce::ChangeBroadcaster *source)
{
    std::cout<<"wft : change received !  "<<std::endl;
    
    repaint();
}

void WaveformDisplay::setPositionRelative(double pos)
{
    if(pos != position && pos >0)
    {
        position = pos;
        repaint();
    }
}
