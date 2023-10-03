#include <Sound.h>
#include <SDL2/SDL_mixer.h>
#include <Resources.h>

#include <iostream>
#include <algorithm>

Sound::Sound(GameObject& assoc): Component(assoc) {
    chunk = nullptr;
}

Sound::Sound(GameObject& assoc, std::string file): Sound(assoc) {
    Open(file);
}

Sound::~Sound() {
    if(chunk != nullptr) {
        Stop();
    }
}

void Sound::Play(int times) {
    if(IsOpen()){
        channel = Mix_PlayChannel(-1,chunk.get(),times-1);
    }
}

void Sound::Stop() {
    Mix_HaltChannel(channel);
}

/// @brief Opens the given Sound with the Resource Manager.
/// @param file Path to the sound file.
void Sound::Open(std::string file) {
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