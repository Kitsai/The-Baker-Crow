#include <Music.h>
#include <iostream>
#include <Resources.h>

/// @brief 
/// Basic constructor for music.
/// Initializes music as nullptr.
Music::Music(){
    music = nullptr;
}

/// @brief 
/// Parametrized constructor for Music.
/// Links the basic constructor and opens the given file.
/// @param file 
/// Path to music file.
Music::Music(std::string file): Music() {
    Open(file);
}

/// @brief 
/// Plays the associated music a number of times. If no argument is passed plays indefinetly.
/// @param times
/// Number times to be played. If not specified is -1. 
void Music::Play(int times) {
    if(IsOpen()) {
        if(Mix_PlayMusic(music.get(),times) == -1) {
            std::cout << "Error Music:16 - " << SDL_GetError() << std::endl;
            exit(-1);
        }
    }
    else {   
        std::cout << "Error Music:21 - " << SDL_GetError() << std::endl;
        exit(-1);
    }
}

/// @brief 
/// Stops the music that is playing.
/// @param msToStop 
/// How long should the fade out be.
void Music::Stop(int msToStop) {
    Mix_FadeOutMusic(msToStop);
}

/// @brief 
/// Opens a given music using the Resource Manager.
/// @param file 
/// Path to music file.
void Music::Open(std::string file) {
    music = Resources::GetMusic(file);
    if(!IsOpen()) {
        std::cout << "Error Music:33 -  " << SDL_GetError() << std::endl;
        exit(-1);
    }
}

/// @brief 
/// Checks if music has been open succesfully.
/// @return 
/// True if music is open and false if it is not.
bool Music::IsOpen(){
    if(music == nullptr)
        return false;
    else 
        return true;   
}

/// @brief 
/// Stops the music before deleting.
Music::~Music() {
    Stop();
}