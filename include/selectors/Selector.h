#ifndef Selector_H
#define Selector_H

#include <vector>

#include "Sound.h"
#include "Button.h"
#include "InputManager.h"

class Selector{
public:
    Selector(std::vector<std::shared_ptr<Button>> buttons);
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