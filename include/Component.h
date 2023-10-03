#ifndef Component_h_
#define Component_h_

#include <string>

class GameObject;

/// @brief A Game Component it cam be various different types.
class Component {
    protected:
        /// @brief The associated Game Object which the component is part of.
        GameObject& associated;
    public:
        /// @brief Constructor to component that initializes the associated Game object.
        /// @param assoc Game Object the component is part of.
        Component(GameObject& assoc);
        virtual ~Component();

        /// @brief Updates the component.
        /// @param dt Delta time.
        void virtual Update(float dt) = 0;
        /// @brief Renders the component.
        void virtual Render() = 0;
        /// @brief 
        /// Returns whether the object is of a certain type.
        /// @param type 
        /// Type to be checked.
        /// @return 
        /// True if type matches with the passed argument.
        bool virtual Is(std::string type) = 0;

        /// @brief Starts the component.
        void virtual Start();

        /// @brief Responds to a collision with another object.
        /// @param other The object that this instance collided with.
        void virtual NotifyCollision(GameObject& other);
};

#endif