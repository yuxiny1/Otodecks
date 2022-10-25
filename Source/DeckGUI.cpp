/*
  ==============================================================================
    DeckGUI.cpp
    Created: 30 Jan 2022 6:56:20pm
    Author:  Xinyi Yu
  ==============================================================================
*/

#include <JuceHeader.h>
#include "DeckGUI.h"

//==============================================================================
DeckGUI::DeckGUI(int _id,
                 DJAudioPlayer* _player,
                 juce::AudioFormatManager & formatManagerToUse,
                 juce::AudioThumbnailCache & cacheToUse

                 ): id(_id),
                    player(_player),
                    waveformDisplay(id, formatManagerToUse,cacheToUse)
{
 
    setLookAndFeel (&otherLookAndFeel);
    
    volSlider.setLookAndFeel (&otherLookAndFeel);
    speedSlider.setLookAndFeel (&otherLookAndFeel);
    
    volSlider.setSliderStyle (juce::Slider::Rotary);
    volSlider.setTextBoxStyle (juce::Slider::NoTextBox, false, 0, 0);
    
    speedSlider.setSliderStyle (juce::Slider::Rotary);
    speedSlider.setTextBoxStyle (juce::Slider::NoTextBox, false, 0, 0);

    addAndMakeVisible(playButton);
    addAndMakeVisible(volSlider);
    addAndMakeVisible(speedSlider);
    addAndMakeVisible(stopButton);
    addAndMakeVisible(loadButton);
    
    addAndMakeVisible(posSlider);
    
    addAndMakeVisible(waveformDisplay);
    
    playButton.addListener(this);
    stopButton.addListener(this);
    loadButton.addListener(this);
    speedSlider.addListener(this);
    volSlider.addListener(this);
    posSlider.addListener(this);
    
    addAndMakeVisible(speedLabel);
    volSlider.setRange(0.0, 1.0);
    speedSlider.setRange(0, 5);
    posSlider.setRange(0.0, 1.0);
    
    startTimer(500);
}

DeckGUI::~DeckGUI()
{
    stopTimer();
    setLookAndFeel (nullptr);

}

void DeckGUI::paint (juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background
    g.setColour (juce::Colours::yellow);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

    g.setColour (juce::Colours::darkred);
    g.setFont (14.0f);
    g.drawText ("Volume & Speed & Position ", getLocalBounds(),
                juce::Justification::centred, true);   // draw some placeholder text
    
    g.setColour (juce::Colours::hotpink);
    auto centralArea = getLocalBounds().toFloat().reduced(10.0f);
    g.drawRoundedRectangle (centralArea, 5.0f, 3.0f);
    
    juce::Array<juce::Colour> colours{ juce::Colours::lightpink, juce::Colours::hotpink, juce::Colours::deeppink
    };
    
    auto colourBarArea = centralArea.reduced(4.0f).withHeight(275.0f);
        
    auto colourArea= colourBarArea.withWidth(colourBarArea.getWidth()/colours.size());
    
    for (auto colour : colours)
    {
        g.setColour (colour);
        g.fillRect (colourArea);
        colourArea.translate (colourArea.getWidth(), 0.0f);
    }
    
    if(colorFlag ==1 )
    {
        g.fillAll(juce::Colours:: palevioletred);
    }
    
    if(colorFlag ==2 )
    {
        g.fillAll(juce::Colours::red);
    }
    if(colorFlag ==3)
    {
        g.fillAll(juce::Colours::hotpink);
    }
}

void DeckGUI::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..
    double rowH = getHeight()/10 ;
    
    playButton.setBounds(rowH, rowH*9, getWidth()/6, rowH);
    loadButton.setBounds(rowH*5, rowH*9, getWidth()/6, rowH);
    stopButton.setBounds(rowH*9, rowH*9, getWidth()/6, rowH);
    playButton.setColour(juce::TextButton::buttonColourId, juce::Colours::yellowgreen);
    stopButton.setColour(juce::TextButton::buttonColourId, juce::Colours::rebeccapurple);
    loadButton.setColour(juce::TextButton::buttonColourId, juce::Colours::lightseagreen);
    waveformDisplay.setBounds(0, rowH*5, getWidth(), rowH*3);
    posSlider.setBounds(rowH*2,rowH*4, getWidth(), rowH);
    
        auto border = 4;

        auto area = getLocalBounds();

        auto dialArea = area.removeFromTop (area.getHeight() / 3);

    volSlider.setBounds (dialArea.removeFromLeft (dialArea.getWidth() / 2).reduced (border));
    speedSlider.setBounds (dialArea.reduced (border));
}

void DeckGUI::buttonClicked(juce::Button* button)
{
    //just look at the memory address clicked on if you get the memory address of which means you clicked
    if(button == &playButton)
    {
        std::cout<<" play button was clicked "<<std::endl;
      
        player->start();
        colorFlag=1;
        repaint();
    }
    if(button == &stopButton)
    {
        std::cout<<"stop  button was clicked "<<std::endl;
        player->stop();
        colorFlag=2;
        repaint();
    }
    if(button == &loadButton)
    {
        juce::FileChooser chooser{"Select a file..."};
        if(chooser.browseForFileToOpen())
        {
            loadFile(juce::URL{ chooser.getResult() });
        }
        colorFlag=3;
        repaint();
    }
}
//
void DeckGUI::sliderValueChanged (juce::Slider *slider)
{
    if(slider == &volSlider )
    {
        player->setGain(slider->getValue());
    }

    if (slider == &speedSlider)
    {
        player->setSpeed(slider->getValue());
    }
    if (slider == &posSlider)
    {
        player->setPositionRelative(slider->getValue());
    }
    }

bool DeckGUI::isInterestedInFileDrag (const juce::StringArray &files)
{
    std::cout<< "DeckGui is Intereseted infile drag "<<std::endl;
    if(files.size()==1)
    {
        player->loadURL(juce::URL{juce::File{files[0]}});
    }
    return true;
}


void DeckGUI::filesDropped(const juce::StringArray &files, int x, int y)
{
    std::cout<<" DeckGUI::filesDropped(const" <<std::endl;
}

void DeckGUI::timerCallback()
{
    if(player->getPositionRelative() >0)
    {
    waveformDisplay.setPositionRelative(
                                        player->getPositionRelative());
    }
}


void DeckGUI::drawRotarySlider (juce::Graphics& g, int x, int y, int width, int height, float sliderPos,
                       const float rotaryStartAngle, const float rotaryEndAngle, juce::Slider&)

{
 
    auto radius = (float) juce::jmin (width / 2, height / 2) - 4.0f;
    auto centreX = (float) x + (float) width  * 0.5f;
    auto centreY = (float) y + (float) height * 0.1f;
    auto rx = centreX - radius;
    auto ry = centreY - radius;
    auto rw = radius * 2.0f;
    auto angle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);
    // fill
    g.setColour (juce::Colours::orange);
    g.fillEllipse (rx, ry, rw, rw);

    // outline
    g.setColour (juce::Colours::red);
    g.drawEllipse (rx, ry, rw, rw, 1.0f);
    
    juce::Path p;
    auto pointerLength = radius * 0.33f;
    auto pointerThickness = 2.0f;
    p.addRectangle (-pointerThickness * 0.5f, -radius, pointerThickness, pointerLength);
    p.applyTransform (juce::AffineTransform::rotation (angle).translated (centreX, centreY));

    // pointer
    g.setColour (juce::Colours::yellow);
    g.fillPath (p);
    
}

void DeckGUI::loadFile(juce::URL audioURL)
{
    DBG("DeckGUI::loadFile called");
    player->loadURL(audioURL);
    waveformDisplay.loadURL(audioURL);
}
