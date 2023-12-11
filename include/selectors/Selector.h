#ifndef Selector_H
#define Selector_H

#include <vector>

#include "Game.h"
#include "Sound.h"
#include "Sprite.h"
#include "Button.h"
#include "InputManager.h"

class Selector{
public:
    Selector();
    virtual ~Selector();

    virtual int GetSelected();
    virtual void Update(float dt);
    
    protected:
        int selected;
        std::shared_ptr<Button> selectedButton;
        
        int nButtons;
        std::vector<std::shared_ptr<Button>> buttons;
        
        Sound* soundPass;
};
#endif