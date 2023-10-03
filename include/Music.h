#ifndef Music_h_
#define Music_h_

#include "SDL2/SDL_mixer.h"
#include <string>
#include <memory>

/// @brief A music component.
class Music {
    private:
        /// @brief Shared pointer that holds a music from sdl_mix.
        std::shared_ptr<Mix_Music> music;

    public:
        /// @brief Basic constructor for Music. Starts the music as nullptr.
        Music();
        /// @brief Parameterized Constructor that receives a music file. 
        /// @param file A string that is the relative path to the desired file.
        Music(std::string file);
        /// @brief stops the music before ending.
        ~Music();

        /// @brief Plays the music n times if it has one. 
        /// @param times the number of times the music should be played. If not specified = -1 which means it loops indefinetly.
        void Play(int times = -1);
        /// @brief Stops the music from playing applying a fade out.
        /// @param msToStop how many ms the fade out should be.
        void Stop(int msToStop = 1500);

        /// @brief Opens a givein sound file by using the resource manager.
        /// @param file relative path to the file that should be opened.
        void Open(std::string file);
        /// @brief Checks wheter a file is open or not.
        /// @return true if music != nullptr. That means a music has been opened.
        bool IsOpen();
};

#endif