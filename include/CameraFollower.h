#ifndef CameraFollower_h_
#define CameraFollower_h_

#include "GameObject.h"
#include "Camera.h"

/// @brief Component that makes an object follow the camera position.
class CameraFollower: public Component {
    public:
        /// @brief Constructor for Camera Follower.
        /// @param go Associated GameObject.
        CameraFollower(GameObject& go);

        /// @brief Updates the component. Gets the current camera position and updates the associated objects position to match it.
        /// @param dt Delta Time.
        void Update(float dt);
        /// @brief Renders the component.
        void Render();
        /// @brief 
        /// Returns whether the object is of a certain type.
        /// @param type 
        /// Type to be checked.
        /// @return 
        /// True if type matches with the passed argument.
        bool Is(std::string type);
};

#endif