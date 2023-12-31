#include "Music.h"
#include <SDL2/SDL_mixer.h>
#include <iostream>
#include "Resources.h"

Music::Music(){
    music = nullptr;
}

Music::Music(std::string file): Music() {
    Open(file);
}

Music::~Music() {
    Stop(0);
}

void Music::Play(int times) {
    if(IsOpen()) {
        if(Mix_PausedMusic()) {
            Mix_ResumeMusic();
        } else if(Mix_PlayMusic(music.get(),times) == -1) {
            std::cout << "Error Music:16 - " << SDL_GetError() << std::endl;
        }
    }
    else {   
        std::cout << "Error Music:21 - " << SDL_GetError() << std::endl;
    }
}

void Music::Stop(int msToStop) {
    Mix_FadeOutMusic(msToStop);
}

void Music::Pause() {
    Mix_PauseMusic();
}
void Music::Resume() {
    if(Mix_PausedMusic())
        Mix_ResumeMusic();
}

void Music::Open(std::string file) {
    music = Resources::GetMusic(file);
    if(!IsOpen()) {
        std::cout << "Error Music:33 -  " << SDL_GetError() << std::endl;
    }
}

bool Music::IsOpen(){
    if(!music)
        return false;
    else 
        return true;   
}