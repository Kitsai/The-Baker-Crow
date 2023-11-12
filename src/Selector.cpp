#include "Selector.h"
#include "Sprite.h"
#include "InputManager.h"
#include <iostream>

Selector::Selector(GameObject& assoc) : Component(assoc) {
    selected = 0;
    associated.AddComponent((std::shared_ptr<Sprite>)new Sprite(associated, "resources/img/circleselection_puzzle.png"));
}

Selector::~Selector() {}

void Selector::Update(float dt) {
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

void Selector::Render() {}

bool Selector::Is(std::string type) {
    return type == "Selector";
}

void Selector::RenderSelected(){
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