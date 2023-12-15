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
        void NewDialogue(int type, std::string dad, std::string tuki, std::string text1, std::string text2, std::string text3, std::string text4, std::string text5);
};

#endif