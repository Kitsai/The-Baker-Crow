#include "Game.h"
#include "selectors/Selector.h"

Selector::Selector(std::vector<std::shared_ptr<Button>> buttons) : selected(0), nButtons(2), buttons(buttons){
    
    GameObject* soundPassObj = new GameObject();
    soundPass = new Sound(*soundPassObj, "resources/Sound/ButtonUI.flac");
    soundPassObj->AddComponent(soundPass);

    selectedButton = buttons[0];
    selectedButton->Choose();
    
    Game::GetInstance().GetCurrentState().AddObject(soundPassObj);
}

Selector::~Selector() {
    buttons.clear();
    this->soundPass = nullptr;
}

void Selector::Update(float dt) {
    
    if (InputManager::GetInstance().KeyPress(UP_ARROW_KEY) && selected == 0) {
        selected = nButtons;
        
        selectedButton->UnChoose();
        selectedButton = buttons[selected];
        selectedButton->Choose();
        
        soundPass->Play();
    }
    
    else if (InputManager::GetInstance().KeyPress(UP_ARROW_KEY) && selected > 0) {
        selected--;
        
        selectedButton->UnChoose();
        selectedButton = buttons[selected];
        selectedButton->Choose();

        soundPass->Play();
    }
    else if (InputManager::GetInstance().KeyPress(DOWN_ARROW_KEY) && selected < nButtons) {
        selected++;
        
        selectedButton->UnChoose();
        selectedButton = buttons[selected];
        selectedButton->Choose();

        soundPass->Play();
    }
    
    else if (InputManager::GetInstance().KeyPress(DOWN_ARROW_KEY) && selected == nButtons) {
        selected = 0;

        selectedButton->UnChoose();
        selectedButton = buttons[selected];
        selectedButton->Choose();

        soundPass->Play();
    }
}

int Selector::GetSelected(){
    return selected;
}