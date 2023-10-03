#ifndef Collider_h_
#define Collider_h_

#include <GameObject.h>
#include <string>

/// @brief Component that adds a hitbox to the GameObject.
class Collider: public Component {
    private:
        /// @brief Scale of the hitbox.
        Vec2 scale;
        /// @brief Offset of the hitbox.
        Vec2 offset;
    
    public:
        /// @brief Constructor For the Collider.
        /// @param associated Associated GameObject.
        /// @param scale Scale of hitbox.
        /// @param offSet Offset of hitbox.
        Collider(GameObject& associated, Vec2 scale = {1,1},Vec2 offSet = {0,0});

        /// @brief The hitbox itself.
        Rect box;

        /// @brief Updates the component. Follows the associated object position.
        /// @param dt Delta Time.
        void Update(float dt);
        /// @brief Renders the component. If in debug mode draws the box.
        void Render();
        /// @brief Returns whether the object is of a certain type.
        /// @param type Type to be checked.
        /// @return True if type matches with the passed argument.
        bool Is(std::string type);

        /// @brief Sets the hitbox Scale and updates it accordingly.
        /// @param scale Vector with the new scale.
        void SetScale(Vec2 scale);
        /// @brief Sets the hitbx Offset and updates it accordingly.
        /// @param offset Vector with the new Offset.
        void SetOffset(Vec2 offset);
};

#endif