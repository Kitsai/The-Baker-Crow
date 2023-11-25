#ifndef GameObject_h_
#define GameObject_h_

#include <vector>
#include <string>
#include <memory>

#include "Rect.h"
#include "Timer.h"

#include "Component.h"

/// @brief A object in the game. It holds a list of components that make that game object.
class GameObject {
    private:
        /// @brief A vector that keeps unique pointers to the components of this object.
        std::vector<std::shared_ptr<Component>> componentArray;
        /// @brief keeps a flag that tells the game whether this object should be deleted.
        bool isDead;
        /// @brief Flag that keeps the information if this object has already been started. Useful for knowing when to start components that are added latter or not.
        bool started;

    public:
        /// @brief A rectangle corresponding to the area this object occupies.
        Rect box;
        /// @brief The angle the object box is rotated by.
        double angleDeg;

        /// @brief Game Object constructor. Initializes the box with all 0's and isDead as false.
        GameObject();
        /// @brief Clears the Component vector deleting all of them.
        ~GameObject();

        /// @brief Starts all the components on the components vector.
        void Start();

        /// @brief Propagates the Update for all associated Components.
        /// @param dt DeltaTime
        void Update(float dt);
        /// @brief Propagates the Render for all associated Components.
        void Render();

        /// @brief Getter for the isDead.
        /// @return true if the object should be deleted.
        bool IsDead();

        /// @brief Sets the isDead flag to true. So the object should be deleted.
        void RequestDelete();

        /// @brief Sets the isDead flag to false.
        void UnrequestDelete();

        /// @brief Adds a given component to the component vector.
        /// @param cpt A raw pointer to the component that should be added.
        std::weak_ptr<Component> AddComponent(Component* cpt); 
        /// @brief Removes a specific component from the component vector.
        /// @param cpt A raw pointer to the component that should be removed.
        void RemoveComponent(Component* cpt); 
        /// @brief A Getter for a component of given type.
        /// @param type The type of Component that is being looked for.
        /// @return Raw pointer to the component of desired type.
        std::weak_ptr<Component> GetComponent(std::string type);
        /// @brief A Getter for all components of given type. NOTE: Only use  = when instantiating a new vector. if you need to use in an existing vector use .swap on the returning vector.
        /// @param type The type of Component that is being looked for.
        /// @return A vector of Component pointers.
        std::vector<Component*> GetComponents(std::string type);

        /// @brief Propagates the collision to every component.
        /// @param other The object that this instance is colliding with.
        void NotifyCollision(GameObject& other);
        
};

#endif