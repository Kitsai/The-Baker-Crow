#ifndef LoadGameSelector_H
#define LoadGameSelector_H

#include <vector>
#include "Button.h"
#include "Component.h"

class LoadGameSelector {

public:
    LoadGameSelector();
    LoadGameSelector(std::string buttonPath);
    ~LoadGameSelector();

    int GetSelected();
    void Update(float dt);

    private:
        int selected;
        std::shared_ptr<Button> selectedButton;
        
        int nButtons;
        std::vector<std::shared_ptr<Button>> buttons;
};
#endif