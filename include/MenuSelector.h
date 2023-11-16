#ifndef MenuSelector_H
#define MenuSelector_H

#include <vector>
#include "Button.h"
#include "Component.h"

class MenuSelector : public Component {
    int selected;

public:
    MenuSelector(GameObject& assoc);
    MenuSelector(GameObject& assoc, std::string buttonPath);
    ~MenuSelector();

    int nButtons;

    void Update(float dt);
    void Render();
    bool Is(std::string type);

    std::vector<Button> buttons;
};

#endif