#ifndef Pancake_h_
#define Pancake_h_

#include "Enemy.h"

class Pancake: public Enemy {
    public:
        Pancake(GameObject& associated,int hp = 100);
};

#endif