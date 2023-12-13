#ifndef InventoryState_h
#define InventoryState_h

#include "Game.h"
#include "State.h"

class InventoryState : public State {
    
    public:
        InventoryState();
        ~InventoryState();

        void Render();
        void Update(float dt);
        void LoadAssets();
        void LoadIngredients();
        
        void Pause();
        void Start();
        void Resume();
    private:
        std::unique_ptr<Selector> selector;
};
#endif