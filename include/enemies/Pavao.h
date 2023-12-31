#ifndef Pavao_h_
#define Pavao_h_

#include "Enemy.h"

class Pavao: public Enemy {
    public:
        Pavao(GameObject& associated, int hp = 100);
        ~Pavao();

        bool Is(std::string type);

    private:
        void CalcSpeed(float dt);

        void SetState(EnemyState state);

        void DeathAnimation();

        void DropItems();      
};
 
#endif  