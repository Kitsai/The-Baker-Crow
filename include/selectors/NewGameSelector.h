#ifndef NewGameSelector_H
#define NewGameSelector_H

#include <vector>
#include "Button.h"
#include "Component.h"

class NewGameSelector{

public:
    NewGameSelector();

    ~NewGameSelector();

    int GetSelected();
    void Update(float dt);

    private:
        int selected;
        std::shared_ptr<Button> selectedButton;
        
        int nButtons;
        std::vector<std::shared_ptr<Button>> buttons;
};
#endif