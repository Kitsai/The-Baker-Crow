#ifndef BakeryState_H
#define BakeryState_H

#include "State.h"

class BakeryState : public State {
        
    public:
        BakeryState();
        ~BakeryState();
    
        void Render();
        void Update(float dt);
        void LoadAssets();
            
        void Pause();
        void Start();
        void Resume();
        
        GameObject* shadowObj; 
    private:
        int floor;
};

#endif