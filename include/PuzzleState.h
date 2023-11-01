#ifndef PuzzleState_h_
#define PuzzleState_h_

#include "State.h"

class PuzzleState: public State {
    public:
        PuzzleState();
        ~PuzzleState();

        void LoadAssets();
        void Update(float dt);
        void Render();

        void Start();
        void Pause();
        void Resume();
};

#endif