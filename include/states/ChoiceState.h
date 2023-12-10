#ifndef ChoiceState_H
#define ChoiceState_H

#include "State.h"
#include "InputManager.h"
#include "GameData.h"

class ChoiceState : public State {
    public:
        ChoiceState();
        ~ChoiceState();

        void Render();
        void Update(float dt);
        void LoadAssets();
        
        void Pause();
        void Start();
        void Resume();
};

#endif