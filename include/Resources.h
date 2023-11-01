#ifndef Resources_h_
#define Resources_h_

#include <unordered_map>
#include <string>
#include <iostream>
#include <memory>

#include "SDL2/SDL_mixer.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"
#include "Game.h"

/// @brief Resource manager. That make sure assets are only loaded once.
class Resources {
    private:
        /// @brief Table for all allocated images.
        static std::unordered_map<std::string, std::shared_ptr<SDL_Texture>> imageTable;
        /// @brief Table for all allocated musics.
        static std::unordered_map<std::string, std::shared_ptr<Mix_Music>> musicTable;
        /// @brief Table for all allocated sounds.
        static std::unordered_map<std::string, std::shared_ptr<Mix_Chunk>> soundTable;
        /// @brief Table for all allocated fonts.
        static std::unordered_map<std::string, std::shared_ptr<TTF_Font>> fontTable;
    public:
        /// @brief Gets an image from the image table. If the image was not allocated yet allocates it.
        /// @param file Path to the image file.
        /// @return The Texture associated with the path in the table. 
        static std::shared_ptr<SDL_Texture> GetImage(std::string file);
        /// @brief Clears any image that is not being used.
        static void ClearImages();

        /// @brief Gets an music from the music table. If the music was not allocated yet allocates it.
        /// @param file Path to the music file.
        /// @return The Music associated with the path in the table. 
        static std::shared_ptr<Mix_Music> GetMusic(std::string file);
        /// @brief Clears any music that is not being used.
        static void ClearMusics();

        /// @brief Gets an sound from the sound table. If the sound was not allocated yet allocates it.
        /// @param file Path to the sound file.
        /// @return The Chunk associated with the path in the table. 
        static std::shared_ptr<Mix_Chunk> GetSound(std::string file);
        /// @brief Clears any sound that is not being used.
        static void ClearSounds();

        /// @brief Gets an font from the font table. If the font was not allocated yet allocates it.
        /// @param file Path to the font file.
        /// @param size int corresponding to the font size.
        /// @return The Font associated with the path concatenated with the size in the table. 
        static std::shared_ptr<TTF_Font> GetFont(std::string file, int size);
        /// @brief Clears any font that is not being used.
        static void ClearFonts();
};

#endif