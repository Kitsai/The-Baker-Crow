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
#include "selectors/MenuSelector.h"
#include "states/PuzzleState.h"
#include "defines/DefineInput.h"
#include "states/OverworldState.h"

class MenuState : public State {
    
    public:
        MenuState();
        ~MenuState();

        void Render();
        void Update(float dt);
        void LoadAssets();
        
        void Pause();
        void Start();
        void Resume();
    
    private:
    std::shared_ptr<Music> backGraundMusic;
    std::shared_ptr<MenuSelector> selector;
};
#endif