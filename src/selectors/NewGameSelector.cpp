#include "Game.h"
#include "Sprite.h"
#include "MenuButton.h"
#include "selectors/NewGameSelector.h"
#include "InputManager.h"
#include <memory>

NewGameSelector::NewGameSelector() : selected(0), nButtons(2){
    
    MenuButton* buttonGame1 = new MenuButton(Vec2(0, 300),"resources/img/MenuButton.png", "NEW GAME 1");
    MenuButton* buttonGame2 = new MenuButton(Vec2(400, 300),"resources/img/MenuButton.png", "NEW GAME 2");
    MenuButton* buttonGame3 = new MenuButton(Vec2(800, 300),"resources/img/MenuButton.png", "NEW GAME 3");

    buttons.emplace_back(buttonGame1);
    buttons.emplace_back(buttonGame2);
    buttons.emplace_back(buttonGame3);

    buttons[0]->Choose();
}

NewGameSelector::~NewGameSelector() {
    buttons.clear();
}

void NewGameSelector::Update(float dt) {
    
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

void NewGameSelector::Render() {
}

bool NewGameSelector::Is(std::string type) {
    return type == "NewGameSelector";
}

int NewGameSelector::GetSelected(){
    return selected;
}