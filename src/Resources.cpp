#include "Resources.h"

std::unordered_map<std::string, std::shared_ptr<TTF_Font>> Resources::fontTable;
std::unordered_map<std::string, std::shared_ptr<Mix_Chunk>> Resources::soundTable;
std::unordered_map<std::string, std::shared_ptr<Mix_Music>> Resources::musicTable;
std::unordered_map<std::string, std::shared_ptr<SDL_Texture>> Resources::imageTable;

std::shared_ptr<SDL_Texture> Resources::GetImage(std::string file) {
    if(imageTable.find(file) != imageTable.end()) 
        return imageTable[file];

    SDL_Texture* image = IMG_LoadTexture(Game::GetInstance().GetRenderer() , file.data());
    if(image == nullptr) {
        std::cerr << "Error Resources:9 - " << SDL_GetError() << std::endl;
    }

    imageTable[file] = std::shared_ptr<SDL_Texture>(image,[](SDL_Texture* p) {SDL_DestroyTexture(p);});
    return imageTable[file];
}


std::shared_ptr<Mix_Music> Resources::GetMusic(std::string file) {
    if(musicTable.find(file) != musicTable.end())
        return musicTable[file];
    
    Mix_Music* music = Mix_LoadMUS(file.data());
    if(music == nullptr) {
        std::cerr << "Error Resources:29 - " << SDL_GetError() << std::endl;
    }

    musicTable[file] = std::shared_ptr<Mix_Music>(music,[](Mix_Music* p) {Mix_FreeMusic(p);});
    return musicTable[file];
}

std::shared_ptr<Mix_Chunk> Resources::GetSound(std::string file) {
    if(soundTable.find(file) != soundTable.end())
        return soundTable[file];
    
    Mix_Chunk* sound = Mix_LoadWAV(file.data());
    if(sound == nullptr) {
        std::cerr << "Error Resources:49 - " << SDL_GetError() << std::endl;
    }

    soundTable[file] = std::shared_ptr<Mix_Chunk>(sound,[](Mix_Chunk* p) {Mix_FreeChunk(p);});
    return soundTable[file];
}


std::shared_ptr<TTF_Font> Resources::GetFont(std::string file, int size) {
    std::string key = file + std::to_string(size);
    if(fontTable.find(key) != fontTable.end())
        return fontTable[key];
    
    TTF_Font* font = TTF_OpenFont(file.data(),size);
    if(font == nullptr) {
        std::cerr << "Error - " << SDL_GetError() << '\n';
    }

    fontTable[key] = std::shared_ptr<TTF_Font>(font,[](TTF_Font* p) {TTF_CloseFont(p);});
    return fontTable[key];
}

void Resources::ClearImages() {
    auto it = imageTable.begin();
    
    while (it != imageTable.end()) {
        if (it->second.use_count() == 1) {
            it = imageTable.erase(it);
        } else {
            ++it;
        }
    }
}
    
void Resources::ClearSounds() {
    auto it = soundTable.begin();

    while (it != soundTable.end()) {
        if (it->second.use_count() == 1) {
            it = soundTable.erase(it);
        } else {
            ++it;
        }
    }
}

void Resources::ClearMusics() {
    auto it = musicTable.begin();

    while (it != musicTable.end()) {
        if (it->second.use_count() == 1) {
            it = musicTable.erase(it);
        } else {
            ++it;
        }
    }
}
void Resources::ClearFonts() {
    auto it = fontTable.begin();

    while (it != fontTable.end()) {
        if (it->second.use_count() == 1) {
            it = fontTable.erase(it);
        } else {
            ++it;
        }
    }
}