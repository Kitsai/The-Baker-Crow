#ifndef Wall_h_
#define Wall_h_

#include "Obstacle.h"
#include "Sprite.h"

class Wall: public Obstacle {
    public:
        Wall(GameObject&);
        ~Wall();

        bool Is(std::string type);

    private:
        void SetCollider();
};

#endif