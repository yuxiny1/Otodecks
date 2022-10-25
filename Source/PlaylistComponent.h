/*
  ==============================================================================
    PlaylistComponent.h
    Created: 17 Feb 2022 9:35:00pm
    Author:  Xinyi Yu
  ==============================================================================
*/
#pragma once
#include <JuceHeader.h>
#include <vector>
#include "DJAudioPlayer.h"
#include <fstream>
#include "Track.h"
#include "DeckGUI.h"
#include <algorithm>


//==============================================================================
/*
*/
class PlaylistComponent  : public juce::Component,
                        public juce::TableListBoxModel,
                        public juce::Button::Listener,
                        public juce::TextEditor::Listener

{
public:
    PlaylistComponent(DJAudioPlayer* _playerForPlaylist,
                      DeckGUI* _deckGUI1,
                      DeckGUI* _deckGUI2
                      );
    
    ~PlaylistComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;
    
    int getNumRows() override;
    
    void paintRowBackground (juce::Graphics &,
                            int rowNumber,
                            int width,
                            int height,
                            bool rowIsSelected)override;
    
    void paintCell (juce::Graphics &,
                            int rowNumber,
                            int columnID,
                            int width,
                            int height,
                            bool rowIsSelected)override;
    

    juce::Component* refreshComponentForCell (
                                        int rowNumber,
                                        int columnID,
                                        bool isRowSelected,
                                        juce::Component *existingComponentToUpdate) override;

    void buttonClicked(juce::Button* button) override;
    
//    void loadData(juce::File tableFile);
    
//    int getColumnAutoSizeWidth(int columnID) override;
    
    std::unique_ptr<juce::XmlElement> tutorialData;
    juce::XmlElement* columnList = nullptr;
    juce::XmlElement* dataList = nullptr;
    int numRows = 0;
    
//    juce::String getAttributeNameForColumnId (const int columnId) const;
    
//    juce::String getText (const int columnNumber, const int rowNumber) const;
//
//    void setText (const int columnNumber, const int rowNumber, const juce::String& newText);


private:
    
    
    std::vector<Track> tracks;
    juce::TableListBox library;
    juce::TextEditor searchField;
    
    juce::TableListBox tableComponent;
    std::vector<std::string> trackTitles;
    juce::Font font           { 14.0f };

    DJAudioPlayer* playerForPlaylist;
    DeckGUI* deckGUI1;
    DeckGUI* deckGUI2;
    
    juce::TextButton addToPlayer1Button {"Add to deck 1"};
    juce::TextButton addToPlayer2Button {"Add to deck 2"};
    juce::TextButton importButton{"IMPORT TRACKS"};
    
//    juce::FileChooser fileChooser { "Browse for TableData.xml",
//                                    juce::File::getSpecialLocation (juce::File::invokedExecutableFile) };
//

    void importToLibrary();
    void saveLibrary();
    void loadLibrary();
    void deleteFromTracks(int id);
    
    juce::String getLength(juce::URL audioURL);
    juce::String secondsToMinutes(double seconds);
    
    bool isInTracks(juce::String fileNameWithoutExtension);
    
    int whereInTracks(juce::String searchText);
    
    void loadInPlayer(DeckGUI* deckGUI);
    
    void searchLibrary(juce::String searchText);
    
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PlaylistComponent)
};




