#include <iostream>

#include "Game.h"
#include "Sprite.h"
#include "Button.h"
#include "MenuSelector.h"
#include "InputManager.h"
#include "Vec2.h"

MenuSelector::MenuSelector(GameObject& assoc) : Component(assoc), selected(0), nButtons(2) {
    
    Button* buttonNewGame = new Button(Vec2(500, 200),"resources/img/MenuButton.png", "NEW GAME");
    Button* buttonLoadGame = new Button(Vec2(500, 400),"resources/img/MenuButton.png", "LOAD GAME");
    Button* buttonCreditsGame = new Button(Vec2(500, 600),"resources/img/MenuButton.png", "CREDITS");

    buttons.push_back(*buttonNewGame);
    buttons.push_back(*buttonLoadGame);
    buttons.push_back(*buttonCreditsGame);
}

MenuSelector::MenuSelector(GameObject& assoc, std::string filePath) : MenuSelector(assoc) {
    associated.AddComponent((std::shared_ptr<Sprite>)new Sprite(associated, filePath));
}

MenuSelector::~MenuSelector() {

}

void MenuSelector::Update(float dt) {
    
    if (InputManager::GetInstance().KeyPress(UP_ARROW_KEY) && selected == 0) {
        selected = nButtons;
        
    }
    
    else if (InputManager::GetInstance().KeyPress(UP_ARROW_KEY) && selected > 0) {
        selected--;
        
    }
    else if (InputManager::GetInstance().KeyPress(DOWN_ARROW_KEY) && selected < nButtons) {
        selected++;
        
    }
    
    else if (InputManager::GetInstance().KeyPress(DOWN_ARROW_KEY) && selected == nButtons) {
        selected = 0;
        
    }
    Button* selectedButton = &buttons[selected];
}

void MenuSelector::Render() {
}

bool MenuSelector::Is(std::string type) {
    return type == "MenuSelector";
}