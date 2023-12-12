#ifndef ResumeState_h
#define ResumeState_h

#include "Game.h"
#include "State.h"
#include "selectors/Selector.h"
#include "states/PuzzleState.h"
#include "states/OverworldState.h"

class ResumeState : public State {
    
    public:
        ResumeState();
        ~ResumeState();

        void Render();
        void Update(float dt);
        void LoadAssets();
        void LoadButtons();
        
        void Pause();
        void Start();
        void Resume();
    
    private:
    std::unique_ptr<Selector> selector;
};
#endif