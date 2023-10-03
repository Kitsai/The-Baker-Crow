#include <Resources.h>


std::unordered_map<std::string, std::shared_ptr<SDL_Texture>> Resources::imageTable = {};

std::unordered_map<std::string, std::shared_ptr<Mix_Music>> Resources::musicTable = {};

std::unordered_map<std::string, std::shared_ptr<Mix_Chunk>> Resources::soundTable = {};

std::unordered_map<std::string,std::shared_ptr<TTF_Font>> Resources::fontTable = {};

std::shared_ptr<SDL_Texture> Resources::GetImage(std::string file) {
    if(imageTable.find(file) != imageTable.end()) 
        return imageTable[file];

    SDL_Texture* image = IMG_LoadTexture(Game::GetInstance().GetRenderer() , file.data());
    if(image == nullptr) {
        std::cerr << "Error Resources:9 - " << SDL_GetError() << std::endl;
        exit(-1);
    }

    imageTable[file] = std::shared_ptr<SDL_Texture>(image,[](SDL_Texture* p) {SDL_DestroyTexture(p);});
    return imageTable[file];
}

void Resources::ClearImages() {
    for(auto i: imageTable) 
        if(i.second.unique())
            imageTable.erase(i.first); 
}

std::shared_ptr<Mix_Music> Resources::GetMusic(std::string file) {
    if(musicTable.find(file) != musicTable.end())
        return musicTable[file];
    
    Mix_Music* music = Mix_LoadMUS(file.data());
    if(music == nullptr) {
        std::cerr << "Error Resources:29 - " << SDL_GetError() << std::endl;
        exit(-1);
    }

    musicTable[file] = std::shared_ptr<Mix_Music>(music,[](Mix_Music* p) {Mix_FreeMusic(p);});
    return musicTable[file];
}

void Resources::ClearMusics() {
    for(auto i: musicTable)
        if(i.second.unique())
            musicTable.erase(i.first);
}

std::shared_ptr<Mix_Chunk> Resources::GetSound(std::string file) {
    if(soundTable.find(file) != soundTable.end())
        return soundTable[file];
    
    Mix_Chunk* sound = Mix_LoadWAV(file.data());
    if(sound == nullptr) {
        std::cerr << "Error Resources:49 - " << SDL_GetError() << std::endl;
        exit(-1);
    }

    soundTable[file] = std::shared_ptr<Mix_Chunk>(sound,[](Mix_Chunk* p) {Mix_FreeChunk(p);});
    return soundTable[file];
}

void Resources::ClearSounds() {
    for(auto i: soundTable)
        if(i.second.unique())
            soundTable.erase(i.first);
}

std::shared_ptr<TTF_Font> Resources::GetFont(std::string file, int size) {
    std::string key = file + std::to_string(size);
    if(fontTable.find(key) != fontTable.end())
        return fontTable[key];
    
    TTF_Font* font = TTF_OpenFont(file.data(),size);
    if(font == nullptr) {
        std::cerr << "Error - " << SDL_GetError() << '\n';
        exit(-1);
    }

    fontTable[key] = std::shared_ptr<TTF_Font>(font,[](TTF_Font* p) {TTF_CloseFont(p);});
    return fontTable[key];
}

void Resources::ClearFonts() {
    for(auto i: fontTable) 
        if(i.second.unique())
            fontTable.erase(i.first);
}