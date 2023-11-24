#ifndef NewGameSelector_H
#define NewGameSelector_H

#include <vector>
#include "Button.h"
#include "Component.h"
#include "GameObject.h"

class NewGameSelector: public Component {

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
        std::shared_ptr<Button> selectedButton;
        
        int nButtons;
        std::vector<std::shared_ptr<Button>> buttons;
};
#endif