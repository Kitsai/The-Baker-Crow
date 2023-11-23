#ifndef LoadGameSelector_H
#define LoadGameSelector_H

#include <vector>
#include "Button.h"
#include "Component.h"

class LoadGameSelector : public Component {

public:
    LoadGameSelector(GameObject& assoc);
    LoadGameSelector(GameObject& assoc, std::string buttonPath);
    ~LoadGameSelector();

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