#ifndef House_h_
#define House_h_

#include "Obstacle.h"
#include "Sprite.h"

class House: public Obstacle {
    public: 
        House(GameObject& associated, std::string file);
        ~House();

        bool Is(std::string type);

    private:
        void SetCollider();
};

#endif