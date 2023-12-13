#include "selectors/PuzzleSelector.h"

PuzzleSelector::PuzzleSelector(std::vector<std::shared_ptr<Button>> buttons) : Selector(buttons)  {
    this->nButtons = 4;
}

void PuzzleSelector::Update(float dt) {
    
    
    if (InputManager::GetInstance().KeyPress(UP_ARROW_KEY) && selected > 0) {
        selected--;
        
        selectedButton->UnChoose();
        selectedButton = buttons[selected];
        selectedButton->Choose();

        soundPass->Play();
    }
    else if (InputManager::GetInstance().KeyPress(DOWN_ARROW_KEY) && selected <= (nButtons)) {
        selected++;
        
        selectedButton->UnChoose();
        selectedButton = buttons[selected];
        selectedButton->Choose();

        soundPass->Play();
    }
}