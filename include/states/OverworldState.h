#ifndef OverworldState_h_
#define OverworldState_h_

#include "State.h"
#include "TukiOW.h"
#include "GameData.h"
#include "InputManager.h"

class OverworldState: public State {
    public:
        OverworldState();
        ~OverworldState();

        void LoadAssets();
        void Update(float dt);
        void Render();

        void Start();
        void Pause();
        void Resume();
};

#endif