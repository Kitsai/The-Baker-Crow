#ifndef StartState_h
#define StartState_h

#include "Text.h"
#include "Game.h"
#include "State.h"
#include "Sprite.h"
#include "GameObject.h"
#include "InputManager.h"

class StartState : public State {
    public:
        StartState();
        ~StartState();

        void Render();
        void Update(float dt);
        void LoadAssets();
        
        void Pause();
        void Start();
        void Resume();
    private:


};
#endif