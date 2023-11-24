#ifndef MenuSelector_H
#define MenuSelector_H

#include <vector>
#include "Button.h"
#include "Component.h"

class MenuSelector{

public:
    MenuSelector();
    ~MenuSelector();

    int GetSelected();
    void Update(float dt);
    
    private:
        int selected;
        std::shared_ptr<Button> selectedButton;
        
        int nButtons;
        std::vector<std::shared_ptr<Button>> buttons;
};

#endif