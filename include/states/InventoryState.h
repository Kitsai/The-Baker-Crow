#ifndef InventoryState_h
#define InventoryState_h

#include "Text.h"
#include "Game.h"
#include "State.h"
#include "Music.h"
#include "Sprite.h"
#include "Camera.h"
#include "GameObject.h"
#include "InputManager.h"
#include "states/PuzzleState.h"
#include "defines/DefineInput.h"
#include "states/OverworldState.h"

class InventoryState : public State {
    
    public:
        InventoryState();
        ~InventoryState();

        void Render();
        void Update(float dt);
        void LoadAssets();
        
        void Pause();
        void Start();
        void Resume();
};
#endif