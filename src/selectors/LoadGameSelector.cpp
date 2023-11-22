#include "Game.h"
#include "Sprite.h"
#include "MenuButton.h"
#include "selectors/LoadGameSelector.h"
#include "InputManager.h"
#include <memory>

LoadGameSelector::LoadGameSelector(GameObject& assoc) : Component(assoc), selected(0), nButtons(2){
    
    MenuButton* buttonGame1 = new MenuButton(Vec2(0, 300),"resources/img/MenuButton.png", "LOAD GAME 1");
    MenuButton* buttonGame2 = new MenuButton(Vec2(400, 300),"resources/img/MenuButton.png", "LOAD GAME 2");
    MenuButton* buttonGame3 = new MenuButton(Vec2(800, 300),"resources/img/MenuButton.png", "LOAD GAME 3");

    buttons.emplace_back( buttonGame1);
    buttons.emplace_back( buttonGame2);
    buttons.emplace_back( buttonGame3);

    buttons[selected]->Choose();
}

LoadGameSelector::~LoadGameSelector() {
    buttons.clear();
}

void LoadGameSelector::Update(float dt) {
    
    if (InputManager::GetInstance().KeyPress(LEFT_ARROW_KEY) && selected == 0) {
        buttons[selected]->UnChoose();
        selected = nButtons;
        buttons[selected]->Choose();
    }
    
    else if (InputManager::GetInstance().KeyPress(LEFT_ARROW_KEY) && selected > 0) {
        buttons[selected]->UnChoose();
        selected--;
        buttons[selected]->Choose();
    }
    else if (InputManager::GetInstance().KeyPress(RIGHT_ARROW_KEY) && selected < nButtons) {
        buttons[selected]->UnChoose();
        selected++;
        buttons[selected]->Choose();
    }
    
    else if (InputManager::GetInstance().KeyPress(RIGHT_ARROW_KEY) && selected == nButtons) {
        buttons[selected]->UnChoose();
        selected = 0;
        buttons[selected]->Choose();
    }
}

void LoadGameSelector::Render() {
}

bool LoadGameSelector::Is(std::string type) {
    return type == "LoadGameSelector";
}

int LoadGameSelector::GetSelected(){
    return selected;
}