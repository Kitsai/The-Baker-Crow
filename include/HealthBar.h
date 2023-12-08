#ifndef HealthBar_h_
#define HealthBar_h_

#include "Component.h"
#include "Sprite.h"
#include "CameraFollower.h"
#include <memory>
#include <stack>

class HealthBar: public Component {
    public:
        HealthBar(GameObject& associated);
        ~HealthBar();

        void Update(float dt);
        void Render();
        void Start();

        bool Is(std::string type);

    private:
        std::stack<std::weak_ptr<GameObject>> hearts;
        void AddHeart(int id);
};


#endif