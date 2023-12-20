#include "Sound.h"
#include "SDL2/SDL_mixer.h"
#include "Resources.h"

#include <exception>
#include <iostream>
#include <algorithm>

Sound::Sound(GameObject& assoc): Component(assoc) {
    chunk = nullptr;
}

Sound::Sound(GameObject& assoc, std::string file): Sound(assoc) {
    Open(file);
}

Sound::~Sound() {
}

void Sound::Play(int times) {
    if(IsOpen()){
        channel = Mix_PlayChannel(-1,chunk.get(),times-1);
    }
}

void Sound::Stop() {
    try {
        Mix_HaltChannel(channel);
    } catch(const std::exception& e) {
        std::cout << "ERROR SOUND STOP: " << e.what() << std::endl;
    }
}

bool Sound::IsPlaying() {
    try {
        return Mix_Playing(channel) > 0;
    } catch (const std::exception& e) {
        std::cerr << "Exceção: " << e.what() << std::endl;
        return false;
    }
}

/// @brief Opens the given Sound with the Resource Manager.
/// @param file Path to the sound file.
void Sound::Open(std::string file) {
    chunk = Resources::GetSound(file);
    if(chunk == nullptr) {
        std::cout << "Error Sound:24 - " << SDL_GetError() << std::endl;
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


void Sound::Update(float dt) {

}

void Sound::Render() {

}

bool Sound::Is(std::string type) {
    if(type == "Sound") 
        return true;
    else
        return false; 
}