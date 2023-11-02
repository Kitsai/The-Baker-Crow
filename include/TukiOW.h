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
        void CalcSpeed(float dt);
        std::weak_ptr<GameObject> attack;

};

#endif