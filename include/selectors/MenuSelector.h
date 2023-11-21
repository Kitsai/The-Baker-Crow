#ifndef MenuSelector_H
#define MenuSelector_H

#include <vector>
#include "Button.h"
#include "Component.h"

class MenuSelector : public Component {

public:
    MenuSelector(GameObject& assoc);
    MenuSelector(GameObject& assoc, std::string buttonPath);
    ~MenuSelector();

    void Update(float dt);
    void Render();
    bool Is(std::string type);

    int GetSelected();
    private:
        int selected;
        std::shared_ptr<Button> selectedButton;
        
        int nButtons;
        std::vector<std::shared_ptr<Button>> buttons;
};

#endif