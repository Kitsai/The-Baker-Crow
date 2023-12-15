#ifndef RevenueState_h
#define RevenueState_h

#include "Game.h"
#include "State.h"

class RevenueState : public State {
    
    public:
        RevenueState();
        ~RevenueState();

        void Render();
        void Update(float dt);
        void LoadAssets();
        void LoadRevenues();
        
        void Pause();
        void Start();
        void Resume();
    private:
        std::unique_ptr<Selector> selector;
};
#endif