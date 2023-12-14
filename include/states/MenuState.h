#ifndef MenuState_h
#define MenuState_h

#include "Game.h"
#include "State.h"
#include "states/NewGameState.h"
#include "states/LoadGameState.h"

class MenuState : public State {
    
    public:
        MenuState();
        ~MenuState();

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