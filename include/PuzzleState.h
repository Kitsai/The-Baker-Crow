#ifndef PuzzleState_h_
#define PuzzleState_h_

#include <State.h>

class PuzzleState: public State {
    public:
        PuzzleState();
        ~PuzzleState();

        LoadAssets();
        Update(float dt);
        Render();

        Start();
        Pause();
        Resume();
};

#endif