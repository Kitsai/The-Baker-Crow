#ifndef Penguin_h_
#define Penguin_h_

#include "Enemy.h"

class Penguin: public Enemy {
    public:
        Penguin(GameObject& associated, int hp = 100);
        ~Penguin();

        bool Is(std::string type);

    private:
        void CalcSpeed(float dt);

        void SetState(EnemyState state);

        void DeathAnimation();

        void DropItems();
};

#endif