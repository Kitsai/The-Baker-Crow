#ifndef BakeryState_h_
#define BakeryState_h_

#include "State.h"

class BakeryState: public State {
    public:
        BakeryState();
        ~BakeryState();

        LoadAssets();
        Update(float dt);
        Render();

        Start();
        Pause();
        Resume();
};

#endif