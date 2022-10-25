# Otodecks
# a DJ application using library JUCE and c++


•	R1A: 
The DJAudioplayer is focusing on manipulate and manage the resource of audio.  
Firstly, the DJAudioPlayer.loadURL takes responsible for loading audio files into audio players, and it comes from format manager to recognise the format of the audio files and read them. 
Secondly, the format manager will create a reader and pass resource to reader. 
Thirdly, the transport Source will take care of the resource and the audio is read by the unique pointer and cut by the sample rate. 
Lastly, transport Source will deal with reset, new source, and start to play the audio.
The class DJaudioplayer will have the object players, and they can use the same format manager to load different audio files.
The two players will be created together at the MainComponent  and MainComponent’s function will call the player to do the loading and playing functions.
  
•	R1B: 
Two or more players to play more tracks because they can share the format manager and each player has their own transport source prepared. Furthermore, mixersource inherited from mixerAudiosource helps the main component to manage input sources from different players. 
Those are the core logic of the Audioplayer, and we still need buttons to control the functions, and users can interact with the media player by clicking the buttons created in DeckGUI.
DeckGui will create, paint, and resize those buttons and sliders including play, stop, load, and volume, position, and speed.
Lastly, the two decks created in the main component, and the main component will paint them in a good way with two players of the DJAudioPlayer, and they will share one format manager.
  
•	R1C: 
The music is mixed by the mixersource in the main component, and we mix the music by implementing mixer source in prepare to play, get next audio block, and release Resources. Furthermore, their volumes are controlled by the vol sliders. Sliders will ask player pointer to access the set gain function, and the set gain function get the setgain from transportsource. 

•	R1D: 
The tracks can be speed up and slow down by the speed slider, and sliders created by the juce technically and I kept the position of the song slider same way and changed other two sliders into arch forms, and it looks like what we used to use on the traditional radio machine and easier for user to understand and interact with.
The speed range is 0-5, and the player will get the slider value from the slider we are using, and the value we change will pass into DJAudioplayer.cpp::setSpeed() function, the function received the changed ratio and use this ratio to multiple a resampleSource function, called setResamplingRatio, and the speed of the function will be changed by the slider’s value, hence, if the slider’s value is smaller than 1, and it will be slower, and the speed will be faster if the slider’s value is greater than 1.

 
•	R2: 
The deck control component with graphics could playback controlled by the slider, and I think the position control is reasonable with the length of the song and you can slide it with your finger and control it with this advanced way.
It has three columns of different colours just after launch, and the colour will help users to recognise what is happening and signal the user if any status is changed, and they can quickly recognise it. The playback function is composited by the set position relative function, slider, and labels. Consequently, you can pull the slider or change the number value of the slider to get the position of the track, and that is convenient, and it helps the user to control the playback in multiple ways.
  

•	R2A: 
The DeckGUI component is painted with different colours for different functions. For example, the background of the player will turn red once the song is stopped, and turn hot pink when the song is playing, and turn light pink when loading songs. 
In the middle of the DeckGUI we have the waveform display, and it will show text “feed me music”, and once the music is loaded and it will start to show the waveform and length of the song.
Moreover,  I added more functions to show the status of the player. For example, the flag to indicate that we clicked the button, and we can see the colour change of the player.
 
•	R2B: 
The main part to control the playback of a deck is In the DJAudioPlayer, and we have the formant Manager to manage the format, and we have the set position relative, get position relative to control the position in a music we are playing. Furthermore, the transport source takes responsible for resampling the audio source into different pieces and we get the length of the music, and we get the position in seconds, which means the function set position relative enables the playback function to get the seconds of the music, and we can jump to the seconds in a music as long as we get the position and set the position.
Furthermore, the length of the track will show in minutes in the library, and it is due to the get
length function in the playlist component.
   

•	R3: 
I am lost in the middle and feel hard to understand how to implement xml play list. There is difficulty to read the tutorial of the list box class and difficult to understand how to combine them together. Furthermore, I found music library on the JUCE library, and I start to use library inherited from the table list box, and vector of tracks to store music list, and need to implement the importation function to library function. In simple words, the table list box will contain the library, and the library will show the vector of those tracks name by the file chooser component, and once the button is clicked, and we will load those files as vectors in the library.
   
add and make library visible, and resized the library, and library needs header and se model as well, because it focuses on the music library.
Button click takes responsible for the function load.


•	R3A: 
This component of function allows the user to import files from the file system to the library. We will need to use file chooser again to choose the music documents, and get the name of those music documents, and check is this name existed in the library, and get length of the music document, and push the new name to the tracks vector, so we can see those names in the library file.

   
•	R3B: 
The file name of the loaded file will be displayed due to the file.getFilenameWithoutExtension function, and the song length will be more complicated because it takes long time for me to figure out how does it work.
Moreover, a function named getLength is called, and in the function, we use the pointer of palyerforplaylist to access the functions in DJAudio player, and we can use the load URL and getLengthInSeconds functions. Hence, we can the length of the music by seconds, and we can transfer the result to minutes by the seconds to minutes function.

Lastly, the Is in track function is comparatively simple that it iterates from the begin of the vector to the end of the vector to see is their same name in the vector.

•	R3C:
Search field is a function inherited from juce::textEditor, and we add the visible box to the table list box as usual with the add and make visible function, and the search field will connect with the searchLibrary to implement functions. Furthermore, we need a function to locate the music name in the tracks.  We will pass the search text that you typed in the field to the function and find the tokens I nthe tracks and locate it.
  
•	R3D: 
Users can use the selectedRow function of the library to get rows from the music library, and once the row is selected, and we will click the button to load the file into the DeckGUI. DeckGUI has the ability to access the pointer of player in the DJAudio, and we can access the real component that loads the music, and it is load URL in the DJaudio, and we can load one to each other with two buttons, since we have two DeckGUIs.

•	R3E: 
In order to save the playlist in the library and I used the save library and load library functions to deliver.
 
•	R4: 
The layer out of the DJ audio player designed to show the conditions of the players, and it is a simplified DJ audio player, and the core concept is that the colour of the player will inform the different conditions of the player. For example, the music stopped, and the background of the player will turn to whole red, and DeckGUI is pink while playing music, which is indicative.  
  
•	R4A: 
Moreover, we can use buttons and sliders to control the playing music. For example, the volume is the left side, and the speed is the right-hand side slider. The delete button could delete the music already in the playlist, and the waveform display is in the middle of those buttons, and it is very close to the position of the music because they are closely related, and users can easily identify where the is the position of the music and manipulate it. 


•	R4B: 
R2 is the control deck playback section, and we can see this section blends with waveform display, and three buttons, and the position control. We can see three buttons corresponding to the three-line colours at the back of the DeckGui, and buttons will trigger the change of the background painting. For instance, colour flag is used here to set the colour of the background, and it works with the button click. Three buttons stays at the button of the DeckGui.

•	R4C: GUI layout includes the music library component from R3 
The music library component starts with the import tracks button, and this is the core function of the library with three headers, tracks name, length of the music, and the delete button to control the library. Furthermore, users will see an empty library and once the library is filled with tracks, and it will be full. The search field section is just below the list of the files, and also the add to deck1 and the add to deck 2 buttons stay at the bottom of the table list box. 

