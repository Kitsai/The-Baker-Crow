#ifndef LoadGameState_h
#define LoadGameState_h

#include "Game.h"
#include "State.h"
#include "states/PuzzleState.h"

class LoadGameState : public State {
    
    public:
        LoadGameState();
        ~LoadGameState();

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