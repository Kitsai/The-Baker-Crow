#ifndef LoadGameState_h
#define LoadGameState_h

#include "Text.h"
#include "Game.h"
#include "State.h"
#include "Music.h"
#include "Sprite.h"
#include "Camera.h"
#include "GameObject.h"
#include "InputManager.h"
#include "selectors/LoadGameSelector.h"
#include "states/PuzzleState.h"
#include "defines/DefineInput.h"
#include "states/OverworldState.h"

class LoadGameState : public State {
    
    public:
        LoadGameState();
        ~LoadGameState();

        void Render();
        void Update(float dt);
        void LoadAssets();
        
        void Pause();
        void Start();
        void Resume();
    
    private:
    std::shared_ptr<Music> backGraundMusic;
    std::shared_ptr<LoadGameSelector> selector;
};
#endif