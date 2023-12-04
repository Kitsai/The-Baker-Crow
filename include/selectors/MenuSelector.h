#ifndef MenuSelector_H
#define MenuSelector_H

#include <vector>
#include "UIButton.h"
#include "Component.h"

class MenuSelector{

public:
    MenuSelector();
    ~MenuSelector();

    int GetSelected();
    void Update(float dt);
    
    private:
        int selected;
        
        int nButtons;
        std::vector<std::unique_ptr<UIButton>> buttons;
};

#endif