#ifndef Crab_h_
#define Crab_h_

#include "Enemy.h"

class Crab: public Enemy {
    public:
        Crab(GameObject& associated, int hp = 100);
        ~Crab();

        bool Is(std::string type);

    private:
        void CalcSpeed(float dt);

        void SetState(EnemyState state);

        void DeathAnimation();

        void DropItems();
};

#endif