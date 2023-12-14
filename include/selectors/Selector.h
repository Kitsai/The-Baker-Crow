#ifndef Selector_H
#define Selector_H

#include <vector>

#include "Sound.h"
#include "Button.h"
#include "InputManager.h"

class Selector{
public:
    Selector(std::vector<std::shared_ptr<Button>> buttons, int startButton = 1);
    virtual ~Selector();
    virtual void Update(float dt);
    
    int  GetSelected();
    void SetSelector(int i);
    int  GetNumberOfButtons();
    std::string GetNameSellectedButton();
    
    protected:
        int nButtons;
        int selected;
        Sound* soundPass;

        std::shared_ptr<Button> selectedButton;
        std::vector<std::shared_ptr<Button>> buttons; 
};
#endif