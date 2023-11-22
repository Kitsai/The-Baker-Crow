#ifndef LoadGameSelector_H
#define LoadGameSelector_H

#include <memory>
#include <vector>
#include "MenuButton.h"
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
        
        int nButtons;
        std::vector<std::unique_ptr<MenuButton>> buttons;
};
#endif