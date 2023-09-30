#ifndef GameObject_h_
#define GameObject_h_

#include <Rect.h>
#include <Component.h>
#include <Collider.h>

#include <vector>
#include <string>
#include <memory>

#include <Sprite.h>
#include <Sound.h>

/// @brief A object in the game. It holds a list of components that make that game object.
class GameObject {
    private:
        std::vector<std::unique_ptr<Component>> components;
        bool isDead;
        bool started;

    public:
        Rect box;
        double angleDeg;

        GameObject();
        ~GameObject();

        void Start();

        void Update(float dt);
        void Render();
        bool IsDead();
        void RequestDelete();
        void AddComponent(Component* cpt);
        void RemoveComponent(Component* cpt);
        Component* GetComponent(std::string type);
        bool IsEntity();

        void NotifyCollision(GameObject& other);
        
};

#endif