#ifndef MenuSelector_H
#define MenuSelector_H

#include <vector>
#include "UIButton.h"
#include "Component.h"

class MenuSelector {

public:
    MenuSelector();
    MenuSelector(std::string buttonPath);
    ~MenuSelector();

    void Update(float dt);
    void Render();
    bool Is(std::string type);

    int GetSelected();
    private:
        int selected;
        
        int nButtons;
        std::vector<std::unique_ptr<UIButton>> buttons;
};

#endif