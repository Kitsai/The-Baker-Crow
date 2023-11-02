#ifndef BakeryState_h_
#define BakeryState_h_

#include "State.h"

class BakeryState: public State {
    public:
        BakeryState();
        ~BakeryState();

        void LoadAssets();
        void Update(float dt);
        void Render();

        void Start();
        void Pause();
        void Resume();
};

#endif