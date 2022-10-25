#include <JuceHeader.h>
#include "PlaylistComponent.h"

//==============================================================================
PlaylistComponent::PlaylistComponent(DJAudioPlayer* _playerForPlaylist,
                                     DeckGUI* _deckGUI1,
                                     DeckGUI* _deckGUI2
                                     ):playerForPlaylist(_playerForPlaylist),
                                    deckGUI1(_deckGUI1),
                                    deckGUI2(_deckGUI2)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    
//register the playlist component with the table list box as a table list model

    addAndMakeVisible(tableComponent);
    addAndMakeVisible(importButton);
    addAndMakeVisible(library);
    addAndMakeVisible(addToPlayer1Button);
    addAndMakeVisible(addToPlayer2Button);
    addAndMakeVisible(searchField);
    
    importButton.addListener(this);
    tableComponent.setModel(this);
    searchField.addListener(this);
    addToPlayer1Button.addListener(this);
    addToPlayer2Button.addListener(this);
    
    searchField.setTextToShowWhenEmpty("search music name here and press ENTER !",juce::Colours::blue);
    
    searchField.onReturnKey = [this]{searchLibrary (searchField.getText());};
    
    library.getHeader().addColumn("Tracks", 1, 1);
    library.getHeader().addColumn("Length", 2, 1);
    library.getHeader().addColumn("", 3, 1);
    library.setModel(this);
    loadLibrary();
    
}

PlaylistComponent::~PlaylistComponent()
{
    saveLibrary();
}

void PlaylistComponent::paint (juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.
       You should replace everything in this method with your own
       drawing code..
    */

    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background

    g.setColour (juce::Colours::hotpink);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

    g.setColour (juce::Colours::white);
    g.setFont (14.0f);
    g.drawText ("PlaylistComponent", getLocalBounds(),
                juce::Justification::centred, true);   // draw some placeholder text
}

void PlaylistComponent::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..
    tableComponent.setBounds(0, 0, getWidth(), getHeight());
    importButton.setBounds(0, 0, getWidth(), getHeight() / 10);
    library.setBounds(0, 1 * getHeight() / 10, getWidth(), 13 * getHeight() / 10);
    searchField.setBounds(0, 13 * getHeight() / 16, getWidth(), 1.5*getHeight() / 16);
    addToPlayer1Button.setBounds(0, 14 * getHeight() / 16, getWidth() /2 , 2*getHeight() / 16);
    addToPlayer2Button.setBounds(getWidth() / 2, 14 * getHeight() / 16, getWidth() / 2, 2*getHeight() / 16);
    //set columns
    library.getHeader().setColumnWidth(1, 12.8 * getWidth() / 20);
    library.getHeader().setColumnWidth(2, 5 * getWidth() / 20);
    library.getHeader().setColumnWidth(3, 2 * getWidth() / 20);
}


int PlaylistComponent::getNumRows()
{
    return tracks.size();
}

void PlaylistComponent::paintRowBackground (
                        juce::Graphics & g,
                        int rowNumber,
                        int width,
                        int height,
                        bool rowIsSelected)
{
    if (rowIsSelected)
    {
        g.fillAll(juce::Colours::orange);
    }
    else{
        g.fillAll(juce::Colours::lightblue);
    }
}

void PlaylistComponent::paintCell (juce::Graphics & g,
                        int rowNumber,
                        int columnId,
                        int width,
                        int height,
                        bool rowIsSelected)
{

    if(rowNumber < getNumRows())
    {
        if(columnId==1)
        {
            g.drawText(tracks[rowNumber].title,
                       2, 0,
                       width-4, height,
                       juce::Justification::centredLeft,
                       true
                       );
        }
        if(columnId ==2)
        {
            g.drawText(tracks[rowNumber].length, 2
                       , 0, width -4 ,
                       height,
                       juce::Justification::centred,
                       true
                       );
                }
            }
        }



juce::Component* PlaylistComponent::refreshComponentForCell (
                                    int rowNumber,
                                    int columnId,
                                    bool isRowSelected,
                                    juce::Component *existingComponentToUpdate)
{
    if(columnId ==3)
    {
        if(existingComponentToUpdate == nullptr)
        {
            
            juce::TextButton*btn = new juce::TextButton{"Delete"};
            juce::String id{std::to_string(rowNumber)};
            //text button is a component of the child class
            btn->setComponentID(id);
            
            btn->juce::Button::addListener(this);
            btn->setColour(juce::TextButton::buttonColourId, juce::Colours::darkblue);
            
            existingComponentToUpdate = btn;
        }
    }
    return existingComponentToUpdate;
}


void PlaylistComponent::buttonClicked(juce::Button* button)
{
    if(button ==& importButton)
    {
        DBG("Load butto nclicked ");
        importToLibrary();
        library.updateContent();
    }
    else if (button == & addToPlayer1Button)
    {
        DBG("Add to player 1 clicked");
        loadInPlayer(deckGUI1);
        
    }
    else if(button == & addToPlayer2Button)
    {
        DBG("add to player 2 clicked");
        loadInPlayer(deckGUI2);
    }
    else {
        int id = std::stoi(button->getComponentID().toStdString());
        DBG(tracks[id].title + "removed from librart ");
        deleteFromTracks(id);
        library.updateContent();
    }
}

    


void PlaylistComponent::importToLibrary()
{
    DBG("PlaylistComponent::importToLibrary called");

    //initialize file chooser
    juce::FileChooser chooser{ "Select files" };
    if (chooser.browseForMultipleFilesToOpen())
    {
        for (const juce::File& file : chooser.getResults())
        {
            juce::String fileNameWithoutExtension{ file.getFileNameWithoutExtension() };
            if (!isInTracks(fileNameWithoutExtension)) // if not already loaded
            {
                Track newTrack{ file };
                juce::URL audioURL{ file };
                newTrack.length = getLength(audioURL) ;
                tracks.push_back(newTrack);
                DBG("loaded file: " << newTrack.title);
            }
            else // display info message
            {
                juce::AlertWindow::showMessageBox(juce::AlertWindow::AlertIconType::InfoIcon,
                    "Load information:",
                    fileNameWithoutExtension + " already loaded",
                    "OK",
                    nullptr
                );
            }
        }
    }
}



juce::String PlaylistComponent::getLength(juce::URL audioURL)
{
    playerForPlaylist->loadURL(audioURL);
    double seconds{playerForPlaylist->getLengthInSeconds() };
    juce::String minutes{secondsToMinutes(seconds)} ;
    return minutes;
}

juce::String PlaylistComponent::secondsToMinutes(double seconds)
{
    int secondsRounded{ int (std::round(seconds))} ;
    juce::String min{ std::to_string(secondsRounded /60 )};
    juce::String sec{std::to_string(secondsRounded %60)};
    
    if(sec.length() < 2)
    {
        sec = sec.paddedLeft('0', 2);
    }
    return juce::String{ min + ":" + sec } ;
}


bool PlaylistComponent::isInTracks(juce::String fileNameWithoutExtension)
{
    return(std::find(tracks.begin(),tracks.end(),
                     fileNameWithoutExtension) != tracks.end());
}



void PlaylistComponent::saveLibrary()
{
    std::ofstream myLibrary("My-library.csv");
    
    for(Track& t: tracks)
    {
        myLibrary <<t.file.getFullPathName()<< "," <<t.length<< "\n";
    }
}


void PlaylistComponent::loadLibrary()
{
    std::ifstream myLibrary("My-library.csv");
    std::string filePath;
    std::string length;
    
    if( myLibrary.is_open())
    {
        while(getline(myLibrary, filePath, ',')) {
            juce::File file{ filePath };
            Track newTrack{ file };
            
            getline(myLibrary, length);
            newTrack.length = length;
            tracks.push_back(newTrack);
        }
    }
    myLibrary.close();
}



void PlaylistComponent::deleteFromTracks(int id)
{
    tracks.erase(tracks.begin() + id);
}


int PlaylistComponent::whereInTracks(juce::String searchText)
{
    auto it= find_if(tracks.begin(), tracks.end(),
                     [&searchText](const Track& obj) {return obj.title.contains(searchText);});
    int i=-1;
    
    if( it != tracks.end())
    {
        i = std::distance(tracks.begin(), it);
    }
                         return  i;
}



void PlaylistComponent::loadInPlayer(DeckGUI* deckGUI)
{
    int selectedRow{ library.getSelectedRow() };
    if ( selectedRow != -1)
    {
        DBG("Adding: " <<tracks[selectedRow].title<<" to player ");
        deckGUI->loadFile(tracks[selectedRow].URL);
    }
    else
    {
        juce::AlertWindow::showMessageBox(juce::AlertWindow::AlertIconType::InfoIcon,
                                          "Add to deck information",
                                          "Please selecte a track to add to deck ",
                                          "ok",
                                          nullptr
);
    }
}

void PlaylistComponent::searchLibrary(juce::String searchText){
    DBG("search library for the track :" <<searchText);
    if ( searchText !="")
    {
        int rowNumber = whereInTracks(searchText);
        library.selectRow(rowNumber);
    }
    else
    {
        library.deselectAllRows();
    }
}

