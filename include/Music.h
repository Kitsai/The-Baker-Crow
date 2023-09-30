#ifndef Music_h_
#define Music_h_

#include "SDL2/SDL_mixer.h"
#include <string>
#include <memory>

/// @brief A music component.
class Music {
    private:
        std::shared_ptr<Mix_Music> music;

    public:
        Music();
        Music(std::string file);
        ~Music();

        void Play(int times = -1);
        void Stop(int msToStop = 1500);
        void Open(std::string file);
        bool IsOpen();
};

#endif