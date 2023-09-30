#ifndef Sound_h_
#define Sound_h_

#include "SDL2/SDL_mixer.h"
#include <GameObject.h>

/// @brief A sound component.
class Sound: public Component {
    private:
        std::shared_ptr<Mix_Chunk> chunk;
        int channel;

    public:
        Sound(GameObject& assoc);
        Sound(GameObject& assoc, const char* file);

        ~Sound();

        void Play(int times = 1);
        void Stop();
        void Open(const char* file);
        bool IsOpen();
        bool IsPlaying();

        void Update(float dt);
        void Render();
        bool Is(std::string type);
};

#endif