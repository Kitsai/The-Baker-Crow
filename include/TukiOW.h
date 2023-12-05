#ifndef TukiOW_h_
#define TukiOW_h_

#include "Player.h"

#include "GameData.h"
#include "InputManager.h"
#include "Attack.h"

#include "Game.h"

class TukiOW: public Player {
    public:
        TukiOW(GameObject&);
        ~TukiOW();

        void Update(float dt);

        bool Is(std::string type);
        
    private:
        void Move(float dt);
        void CalcSpeed(float dt);

        float attackCooldown;
        // std::weak_ptr<GameObject> attack;

        void SetPlayerState(PlayerState state);
};

#endif