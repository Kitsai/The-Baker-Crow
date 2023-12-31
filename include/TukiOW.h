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

        void SetPlayerState(PlayerState state);
    
    private:
        void Move(float dt);
        void CalcSpeed(float dt);

        float attackCooldown;
        void CheckBorders();

        enum faceDirectionEnum {UP, DOWN, LEFT, RIGHT};
        faceDirectionEnum faceDirection;
};

#endif