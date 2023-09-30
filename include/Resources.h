#ifndef Resources_h_
#define Resources_h_

#include <unordered_map>
#include <string>
#include <iostream>
#include <memory>

#include "SDL2/SDL_mixer.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"
#include <Game.h>

/// @brief Resource manager. That make sure assets are only loaded once.
class Resources {
    private:
        static std::unordered_map<std::string, std::shared_ptr<SDL_Texture>> imageTable;
        static std::unordered_map<std::string, std::shared_ptr<Mix_Music>> musicTable;
        static std::unordered_map<std::string, std::shared_ptr<Mix_Chunk>> soundTable;
        static std::unordered_map<std::string, std::shared_ptr<TTF_Font>> fontTable;
    public:
        static std::shared_ptr<SDL_Texture> GetImage(std::string file);
        static void ClearImages();

        static std::shared_ptr<Mix_Music> GetMusic(std::string file);
        static void ClearMusics();

        static std::shared_ptr<Mix_Chunk> GetSound(std::string file);
        static void ClearSounds();

        static std::shared_ptr<TTF_Font> GetFont(std::string file, int size);
        static void ClearFonts();
};

#endif