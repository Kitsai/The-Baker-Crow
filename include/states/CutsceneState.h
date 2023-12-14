#ifndef Cutscene_H
#define Cutscene_H

#include "states/State.h"

class CutsceneState : public State {
    public:
        CutsceneState();
        ~CutsceneState();

        void Render();
        void Update(float dt);
        void LoadAssets();
        
        void Pause();
        void Start();
        void Resume();
    private:
        int stage;

        void NextStage();
};

#endif