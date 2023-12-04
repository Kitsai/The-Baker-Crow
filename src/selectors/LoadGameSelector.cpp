#include "Game.h"
#include "Sprite.h"
#include "Button.h"
#include "selectors/LoadGameSelector.h"
#include "InputManager.h"
#include <memory>

LoadGameSelector::LoadGameSelector() : selected(0), nButtons(2){
    
    Button* buttonGame1 = new Button(Vec2(0, 300),"resources/img/MenuButton.png", "LOAD GAME 1");
    Button* buttonGame2 = new Button(Vec2(400, 300),"resources/img/MenuButton.png", "LOAD GAME 2");
    Button* buttonGame3 = new Button(Vec2(800, 300),"resources/img/MenuButton.png", "LOAD GAME 3");

    buttons.push_back((std::shared_ptr<Button>) buttonGame1);
    buttons.push_back((std::shared_ptr<Button>) buttonGame2);
    buttons.push_back((std::shared_ptr<Button>) buttonGame3);

    selectedButton = buttons[0];
    selectedButton->Choose();
}

LoadGameSelector::~LoadGameSelector() {
    buttons.clear();
}

void LoadGameSelector::Update(float dt) {
    
    if (InputManager::GetInstance().KeyPress(LEFT_ARROW_KEY) && selected == 0) {
        selected = nButtons;
        
        selectedButton->UnChoose();
        selectedButton = buttons[selected];
        selectedButton->Choose();
    }
    
    else if (InputManager::GetInstance().KeyPress(LEFT_ARROW_KEY) && selected > 0) {
        selected--;
        
        selectedButton->UnChoose();
        selectedButton = buttons[selected];
        selectedButton->Choose();
    }
    else if (InputManager::GetInstance().KeyPress(RIGHT_ARROW_KEY) && selected < nButtons) {
        selected++;
        
        selectedButton->UnChoose();
        selectedButton = buttons[selected];
        selectedButton->Choose();
    }
    
    else if (InputManager::GetInstance().KeyPress(RIGHT_ARROW_KEY) && selected == nButtons) {
        selected = 0;

        selectedButton->UnChoose();
        selectedButton = buttons[selected];
        selectedButton->Choose();
    }
}

int LoadGameSelector::GetSelected(){
    return selected;
}