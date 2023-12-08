#include "Game.h"
#include "Sprite.h"
#include "Button.h"
#include "selectors/ResumeSelector.h"
#include "InputManager.h"
#include <memory>

ResumeSelector::ResumeSelector() : selected(0), nButtons(2){
    Button* buttonResumeGame = new Button(Vec2(500, 180),"resources/img/ResumeButton.png", "Resume",36);
    Button* buttonSaveGame = new Button(Vec2(500, 290),"resources/img/ResumeButton.png", "Save Game", 36);
    Button* buttonExitsGame = new Button(Vec2(500, 400),"resources/img/ResumeButton.png", "Exit Game", 36);

    buttons.push_back((std::shared_ptr<Button>) buttonResumeGame);
    buttons.push_back((std::shared_ptr<Button>) buttonSaveGame);
    buttons.push_back((std::shared_ptr<Button>) buttonExitsGame);
    selectedButton = buttons[0];
    selectedButton->Choose();
}

ResumeSelector::~ResumeSelector() {
    buttons.clear();
}

void ResumeSelector::Update(float dt) {
    
    if (InputManager::GetInstance().KeyPress(UP_ARROW_KEY) && selected == 0) {
        selected = nButtons;
        
        selectedButton->UnChoose();
        selectedButton = buttons[selected];
        selectedButton->Choose();
    }
    
    else if (InputManager::GetInstance().KeyPress(UP_ARROW_KEY) && selected > 0) {
        selected--;
        
        selectedButton->UnChoose();
        selectedButton = buttons[selected];
        selectedButton->Choose();
    }
    else if (InputManager::GetInstance().KeyPress(DOWN_ARROW_KEY) && selected < nButtons) {
        selected++;
        
        selectedButton->UnChoose();
        selectedButton = buttons[selected];
        selectedButton->Choose();
    }
    
    else if (InputManager::GetInstance().KeyPress(DOWN_ARROW_KEY) && selected == nButtons) {
        selected = 0;

        selectedButton->UnChoose();
        selectedButton = buttons[selected];
        selectedButton->Choose();
    }
}

int ResumeSelector::GetSelected(){
    return selected;
}