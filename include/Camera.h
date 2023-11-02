#ifndef Camera_h_
#define Camera_h_

#include <GameObject.h>
#include <defines/DefineMovement.h>
#include <defines/DefineInput.h>


/// @brief A static class that saves the current position of the camera.
class Camera {
    private:
        /// @brief The object the camera is focusing. If focus == nullptr camera is not following anything.
        static GameObject* focus;

    public:
        /// @brief A vector representing the current Camera position.
        static Vec2 pos;
        /// @brief A vector representing the current Camera speed.
        static Vec2 speed;

        /// @brief Switch the current focus of the Camera.
        /// @param newFocus Object that is going to be followed.
        static void Follow(GameObject* newFocus);
        /// @brief Removes the camera focus.
        static void Unfollow();

        /// @brief Updates the Camera position based on its focus and/or speed.
        /// @param dt Time passed since last frame.
        ///@todo Change limits or get rid of them.
        static void Update(float dt);
};

#endif