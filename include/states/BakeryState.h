#ifndef BakeryState_H
#define BakeryState_H

#include "NPC.h"
#include "Game.h"
#include "State.h"
#include "TukiB.h"
#include "states/ResumeState.h"
#include "states/InventoryState.h"
#include "states/OverworldState.h"

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
    private:
        int floor;
        void ChangeFloor(int newFloor);
};

#endif