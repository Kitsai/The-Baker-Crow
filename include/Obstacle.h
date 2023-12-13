#ifndef Obstacle_h_
#define Obstacle_h_

#include "Vec2.h"
#include "Collider.h"

class Obstacle: public Component {
    public: 
        Obstacle(GameObject& associated);
        ~Obstacle();

        void virtual Update(float dt);
        void virtual Render();
        bool virtual Is(std::string type);

        //std::pair<Vec2,Vec2> GetColliderLimits();
        Rect GetColliderBox();
        Vec2 GetNormalSpeed(Vec2 speed, Rect playerBox);
    protected:
        void virtual SetCollider() = 0;

};

#endif