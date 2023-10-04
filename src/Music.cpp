#include <Music.h>
#include <iostream>
#include <Resources.h>

Music::Music(){
    music = nullptr;
}

Music::Music(std::string file): Music() {
    Open(file);
}

Music::~Music() {
    Stop();
}

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

void Music::Stop(int msToStop) {
    Mix_FadeOutMusic(msToStop);
}

void Music::Open(std::string file) {
    music = Resources::GetMusic(file);
    if(!IsOpen()) {
        std::cout << "Error Music:33 -  " << SDL_GetError() << std::endl;
        exit(-1);
    }
}

bool Music::IsOpen(){
    if(music == nullptr)
        return false;
    else 
        return true;   
}