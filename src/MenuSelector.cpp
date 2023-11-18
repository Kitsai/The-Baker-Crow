#include "Game.h"
#include "Sprite.h"
#include "Button.h"
#include "MenuSelector.h"
#include "InputManager.h"
#include <memory>

MenuSelector::MenuSelector(GameObject& assoc) : Component(assoc), selected(0), nButtons(2), selectedButton(nullptr) {
    
    Button* buttonNewGame = new Button(Vec2(500, 200),"resources/img/MenuButton.png", "NEW GAME");
    Button* buttonLoadGame = new Button(Vec2(500, 400),"resources/img/MenuButton.png", "LOAD GAME");
    Button* buttonCreditsGame = new Button(Vec2(500, 600),"resources/img/MenuButton.png", "CREDITS");

    buttons.push_back((std::shared_ptr<Button>) buttonNewGame);
    buttons.push_back((std::shared_ptr<Button>) buttonLoadGame);
    buttons.push_back((std::shared_ptr<Button>) buttonCreditsGame);
}

MenuSelector::~MenuSelector() {
    buttons.clear();
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
    if(selectedButton){
        selectedButton->UnChoose();
    }
    else if(selectedButton != buttons[selected]){
        selectedButton->Choose();
    }
}

void MenuSelector::Render() {
}

bool MenuSelector::Is(std::string type) {
    return type == "MenuSelector";
}

int MenuSelector::GetSelected(){
    return selected;
}