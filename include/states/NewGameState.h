#ifndef NewGameState_h
#define NewGameState_h


#include "Game.h"
#include "State.h"
#include "states/OverworldState.h"

class NewGameState : public State {
    
    public:
        NewGameState();
        ~NewGameState();

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