#ifndef LoadGameSelector_H
#define LoadGameSelector_H

#include <memory>
#include <vector>
#include "UIButton.h"
#include "Component.h"

class LoadGameSelector {

public:
    LoadGameSelector();
    ~LoadGameSelector();

    int GetSelected();
    void Update(float dt);

    private:
        int selected;
        
        int nButtons;
        std::vector<std::unique_ptr<UIButton>> buttons;
};
#endif