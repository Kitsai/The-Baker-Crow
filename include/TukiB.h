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
        
    private:
        int floor;

        void Move(float dt);
        void CalcSpeed(float dt);

};

#endif