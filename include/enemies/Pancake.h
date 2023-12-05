#ifndef Pancake_h_
#define Pancake_h_

#include "Enemy.h"

#include "TukiOW.h"

class Pancake: public Enemy {
    public:
        Pancake(GameObject& associated,int hp = 100);

        ~Pancake();

        void Update(float dt);

        bool Is(std::string type);
    private:
        void Move(float dt);  
        void CalcSpeed(float dt);

        void SetState(EnemyState state);

        void DeathAnimation();

        void DropItems();

        void NotifyCollision(GameObject& other);
};

#endif