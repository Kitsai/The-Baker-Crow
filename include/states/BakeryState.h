#ifndef BakeryState_H
#define BakeryState_H

#include "Game.h"
#include "GameObject.h"
#include "State.h"
#include "TukiB.h"
#include "states/ResumeState.h"
#include "states/InventoryState.h"
#include "states/OverworldState.h"
#include "Timer.h"
#include "NPC.h"

class BakeryState : public State {
        
    public:
        BakeryState();
        ~BakeryState();
    
        void Render();
        void Update(float dt);
        void LoadAssets();
            
        void Pause();
        void Start();
        void Resume();

        static Timer* clientTimer;
    private:
        int floor;
        void ChangeFloor(int newFloor);

        float nextTime;
        void ManageClients();
};

#endif
