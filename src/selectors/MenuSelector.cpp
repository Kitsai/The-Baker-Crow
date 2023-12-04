#include "Game.h"
#include "Sprite.h"
#include "UIButton.h"
#include "selectors/MenuSelector.h"
#include "InputManager.h"
#include <memory>

MenuSelector::MenuSelector() : selected(0), nButtons(2){
    
    UIButton* buttonNewGame = new UIButton(Vec2(500, 200),"resources/img/MenuButton.png", "NEW GAME");
    UIButton* buttonLoadGame = new UIButton(Vec2(500, 400),"resources/img/MenuButton.png", "LOAD GAME");
    UIButton* buttonCreditsGame = new UIButton(Vec2(500, 600),"resources/img/MenuButton.png", "CREDITS");

    buttons.emplace_back(buttonNewGame);
    buttons.emplace_back(buttonLoadGame);
    buttons.emplace_back(buttonCreditsGame);

    buttons[0]->Choose();
}

MenuSelector::~MenuSelector() {
    buttons.clear();
}

void MenuSelector::Update(float dt) {
    
    if (InputManager::GetInstance().KeyPress(UP_ARROW_KEY) && selected == 0) {
        buttons[selected]->UnChoose();
        selected = nButtons;
        buttons[selected]->Choose();
    }
    
    else if (InputManager::GetInstance().KeyPress(UP_ARROW_KEY) && selected > 0) {
        buttons[selected]->UnChoose();
        selected--;
        buttons[selected]->Choose();
    }
    else if (InputManager::GetInstance().KeyPress(DOWN_ARROW_KEY) && selected < nButtons) {
        buttons[selected]->UnChoose();
        selected++;
        buttons[selected]->Choose();
    }
    
    else if (InputManager::GetInstance().KeyPress(DOWN_ARROW_KEY) && selected == nButtons) {
        buttons[selected]->UnChoose();
        selected = 0;
        buttons[selected]->Choose();
    }
}

int MenuSelector::GetSelected(){
    return selected;
}