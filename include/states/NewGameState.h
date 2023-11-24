#ifndef NewGameState_h
#define NewGameState_h

#include "Text.h"
#include "Game.h"
#include "State.h"
#include "Music.h"
#include "Sprite.h"
#include "Camera.h"
#include "GameObject.h"
#include "InputManager.h"
#include "selectors/NewGameSelector.h"
#include "states/PuzzleState.h"
#include "defines/DefineInput.h"
#include "states/OverworldState.h"

class NewGameState : public State {
    
    public:
        NewGameState();
        ~NewGameState();

        void Render();
        void Update(float dt);
        void LoadAssets();
        
        void Pause();
        void Start();
        void Resume();
    
    private:
    std::shared_ptr<NewGameSelector> selector;
};
#endif