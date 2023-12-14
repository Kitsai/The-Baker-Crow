#ifndef Latinha_h_
#define Latinha_h_

#include "Enemy.h"

class Latinha: public Enemy {
    public:
        Latinha(GameObject& associated, int hp = 100);
        ~Latinha();

        bool Is(std::string type);

    private:
        void CalcSpeed(float dt);

        void SetState(EnemyState state);

        void DeathAnimation();

        void DropItems();
};

#endif