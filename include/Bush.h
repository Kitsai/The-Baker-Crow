#ifndef Bush_h_
#define Bush_h_

#include "Obstacle.h"
#include "Sprite.h"

class Bush: public Obstacle {
    public: 
        Bush(GameObject& associated);
        ~Bush();

        bool Is(std::string type);

    private:
        void SetCollider();
};

#endif