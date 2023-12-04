#ifndef NewGameSelector_H
#define NewGameSelector_H

#include <vector>
#include "UIButton.h"
#include "Component.h"
#include "GameObject.h"


class NewGameSelector{

public:
    NewGameSelector();

    ~NewGameSelector();

    int GetSelected();
    void Update(float dt);

    private:
        int selected;
        
        int nButtons;
        std::vector<std::unique_ptr<UIButton>> buttons;
};
#endif