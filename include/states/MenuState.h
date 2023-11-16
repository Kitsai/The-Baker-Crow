#ifndef MenuState_h
#define MenuState_h

#include "Text.h"
#include "Game.h"
#include "State.h"
#include "Sprite.h"
#include "GameObject.h"
#include "InputManager.h"

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
    Music* backGraundMusic;
};
#endif