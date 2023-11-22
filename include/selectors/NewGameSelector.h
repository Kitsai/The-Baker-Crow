#ifndef NewGameSelector_H
#define NewGameSelector_H

#include <vector>
#include "MenuButton.h"
#include "Component.h"

class NewGameSelector : public Component {

public:
    NewGameSelector(GameObject& assoc);
    NewGameSelector(GameObject& assoc, std::string buttonPath);
    ~NewGameSelector();

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