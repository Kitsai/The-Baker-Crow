#include "Game.h"
#include "selectors/Selector.h"

Selector::Selector(std::vector<std::shared_ptr<Button>> buttons, int startButton) :buttons(buttons), selected(startButton-1), nButtons(buttons.size()-1){
    
    GameObject* soundPassObj = new GameObject();
    soundPass = new Sound(*soundPassObj, "resources/Sound/ButtonUI.flac");
    soundPassObj->AddComponent(soundPass);

    selectedButton = buttons[selected];
    selectedButton->Choose();
    
    Game::GetInstance().GetCurrentState().AddObject(soundPassObj);
}

Selector::~Selector() {
    buttons.clear();
    this->soundPass = nullptr;
}

void Selector::Update(float dt) {
    
    
    if (InputManager::GetInstance().KeyPress(UP_ARROW_KEY) && selected > 0) {
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
    std::cout <<selectedButton->name <<std::endl;
    
}

int Selector::GetSelected(){
    return selected+1;
}
int Selector::GetNumberOfButtons(){
    return buttons.size();
}

void Selector::SetSelector(int i){
    if (i > 0 && i <= GetNumberOfButtons()){
        selected = i-1;

        selectedButton->UnChoose();
        selectedButton = buttons[selected];
        selectedButton->Choose();
        
        soundPass->Play();
    
    }else{
        printf("valor errado");
    }
}