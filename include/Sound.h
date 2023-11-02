#ifndef Sound_h_
#define Sound_h_

#include "SDL2/SDL_mixer.h"
#include <GameObject.h>

/// @brief A sound component.
class Sound: public Component {
    private:
        /// @brief shared pointer that contains a sound shunk.
        std::shared_ptr<Mix_Chunk> chunk;
        /// @brief the channel that the sound should be played.
        int channel;

    public:
        /// @brief Basic constructor to Sound. Links the associated object and sets the chunk to nullptr.
        /// @param assoc Game Object that the component is part of.
        Sound(GameObject& assoc);
        /// @brief Parameterized constructor for sound. Receives the file that should be opened.
        /// @param assoc Game Object that the component is part of.
        /// @param file relative path to the sound file that should be opened.
        Sound(GameObject& assoc, std::string file);

        /// @brief Stops the sound before deleting.
        ~Sound();

        /// @brief Plays the associated sound a certain number of times. If it is not determined will play only once.
        /// @param times number of times sound should be played. Default value is 1.
        void Play(int times = 1);
        /// @brief Stops the sound from playing.
        void Stop();
        /// @brief Checks whether the sound is currently playing.
        /// @return true if the channel is being played.
        bool IsPlaying();
        
        /// @brief Opens given sound file using the resource manager.
        /// @param file relative path to the sound file.
        void Open(std::string file);
        /// @brief Checks whether the sound is opened.
        /// @return true if chunk != nullptr if it isn't the sound has been opened successfully.
        bool IsOpen();
        
        /// @brief Updates the component.
        /// @param dt Delta Time.
        void Update(float dt);
        /// @brief Renders the component.
        void Render();
        /// @brief Returns whether the object is of a certain type.
        /// @param type Type to be checked.
        /// @return True if type matches with the passed argument.
        bool Is(std::string type);
};

#endif