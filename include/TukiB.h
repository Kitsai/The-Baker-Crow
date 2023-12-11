#ifndef TukiB_h_
#define TukiB_h_

#include "Player.h"

#include "GameData.h"
#include "InputManager.h"

#include "Game.h"

class TukiB: public Player {
    public:
        TukiB(GameObject&);
        ~TukiB();

        void Update(float dt);

        bool Is(std::string type);
        
        void SetFloor(int floor);
        int GetFloor();
        
        void SetPlayerState(PlayerState state);
        
        void Talk(std::string file, float time);
    private:
        void Move(float dt);
        void CalcSpeed(float dt);

        int floor;

        enum faceDirectionEnum {UP, DOWN, LEFT, RIGHT};
        faceDirectionEnum faceDirection;
};

#endif