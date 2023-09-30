#ifndef Component_h_
#define Component_h_

#include <string>

class GameObject;

/// @brief A Game Component it cam be various different types.
class Component {
    protected:
        GameObject& associated;
    public:
        Component(GameObject& assoc);
        virtual ~Component();
        void virtual Update(float dt) = 0;
        void virtual Render() = 0;
        bool virtual Is(std::string type) = 0;
        void virtual Start();
        void virtual NotifyCollision(GameObject& other);
};

#endif