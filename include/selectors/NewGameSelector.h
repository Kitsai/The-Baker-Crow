#ifndef NewGameSelector_H
#define NewGameSelector_H

#include <vector>
#include "UIButton.h"
#include "Component.h"

class NewGameSelector {

public:
    NewGameSelector();
    NewGameSelector(std::string buttonPath);
    ~NewGameSelector();

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