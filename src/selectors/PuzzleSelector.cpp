#include "selectors/PuzzleSelector.h"
#include "Sprite.h"
#include "InputManager.h"
#include <iostream>

PuzzleSelector::PuzzleSelector(GameObject& assoc) : Component(assoc) {
    selected = 0;
    associated.AddComponent(new Sprite(associated, "resources/img/circleselection_puzzle.png"));
}

PuzzleSelector::~PuzzleSelector() {}

void PuzzleSelector::Update(float dt) {
    if (InputManager::GetInstance().KeyPress(UP_ARROW_KEY) && selected > 0) {
        selected--;
        RenderSelected();
    }
    if (InputManager::GetInstance().KeyPress(DOWN_ARROW_KEY) && selected < 3) {
        selected++;
        RenderSelected();
    }
    if (InputManager::GetInstance().KeyPress(ENTER_KEY)) associated.RequestDelete();
}

void PuzzleSelector::Render() {}

bool PuzzleSelector::Is(std::string type) {
    return type == "PuzzleSelector";
}

void PuzzleSelector::RenderSelected(){
    switch(selected){
        case 0:
            associated.box.y = 32;
            break;
        case 1:
            associated.box.y = 187;
            break;
        case 2:
            associated.box.y = 342;
            break;
        case 3:
            associated.box.y = 505;
            break;
        default:
            associated.box.y = 32;
            break;
    }
}