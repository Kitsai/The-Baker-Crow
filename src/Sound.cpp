#include <Sound.h>
#include <SDL2/SDL_mixer.h>
#include <Resources.h>

#include <iostream>
#include <algorithm>

/// @brief 
/// Basic constructor for sound.
/// Initializes sound as nullptr.
Sound::Sound(GameObject& assoc): Component(assoc) {
    chunk = nullptr;
}

/// @brief 
/// Parametrized constructor for Sound.
/// Links the basic constructor and opens the given file.
/// @param file 
/// Path to sound file.
Sound::Sound(GameObject& assoc, const char* file): Sound(assoc) {
    Open(file);
}

/// @brief 
/// Stops the sound before deleting.
Sound::~Sound() {
    if(chunk != nullptr) {
        Stop();
    }
}

/// @brief Plays the associated sound a certain number of times. If it is not determined will play only once.
/// @param times number of times sound should be played. Default value is 1.

void Sound::Play(int times) {
    if(IsOpen()){
        channel = Mix_PlayChannel(-1,chunk.get(),times-1);
    }
}

/// @brief 
/// Stops the sound from playing.
void Sound::Stop() {
    Mix_HaltChannel(channel);
}

/// @brief Opens the given Sound with the Resource Manager.
/// @param file Path to the sound file.
void Sound::Open(const char* file) {
    chunk = Resources::GetSound(file);
    if(chunk == nullptr) {
        std::cout << "Error Sound:24 - " << SDL_GetError() << std::endl;
        exit(-1);
    }
}

/// @brief 
/// Checks if the sound has been properly opened.
/// @return 
/// true if the sound is open.
bool Sound::IsOpen() {
    if(chunk != nullptr) 
        return true;
    else
        return false;  
}

/// @brief Checks if the the associated sound is playing.
/// @return true if the sound is playing at the moment.
bool Sound::IsPlaying() {
    return Mix_Playing(channel)>0;
}

void Sound::Update(float dt) {

}

void Sound::Render() {

}

/// @brief 
/// Returns whether the object is of a certain type.
/// @param type 
/// Type to be checked.
/// @return 
/// True if type matches with the passed argument.
bool Sound::Is(std::string type) {
    if(type == "Sound") 
        return true;
    else
        return false; 
}