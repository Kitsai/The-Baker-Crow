#ifndef ResumeState_h
#define ResumeState_h

#include "Text.h"
#include "Game.h"
#include "State.h"
#include "Music.h"
#include "Sprite.h"
#include "Camera.h"
#include "GameObject.h"
#include "InputManager.h"
#include "selectors/ResumeSelector.h"
#include "states/PuzzleState.h"
#include "defines/DefineInput.h"
#include "states/OverworldState.h"

class ResumeState : public State {
    
    public:
        ResumeState();
        ~ResumeState();

        void Render();
        void Update(float dt);
        void LoadAssets();
        
        void Pause();
        void Start();
        void Resume();
    
    private:
    std::unique_ptr<ResumeSelector> selector;
};
#endif