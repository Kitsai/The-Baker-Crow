#include "states/ChoiceState.h"

ChoiceState::ChoiceState() : State() {

    GameObject* titleObj = new GameObject();
    titleObj->box.x = 400;
    titleObj->box.y = 50;
    Sprite* titleImage = new Sprite(*titleObj, "resources/img/MenuButton.png");
    titleImage->SetScale(3.0f, 9.0f);
    titleObj->AddComponent(titleImage);
    AddObject(titleObj);

    GameObject* icon = new GameObject();


}

ChoiceState::~ChoiceState() {
    objectArray.clear();
}

void ChoiceState::Update(float dt) {
    InputManager& iM = InputManager::GetInstance();
    if (iM.KeyPress(ESCAPE_KEY) || iM.QuitRequested()) {
        popRequested = true; 
    }
}

void ChoiceState::Render() {
    for (std::vector<int>::size_type i = 0; i < objectArray.size(); i++){
        objectArray[i]->Render();
    }
}

void ChoiceState::Start() {
    Camera::pos.x = 0;
    Camera::pos.y = 0;
    for (int i = 0; i < (int)objectArray.size(); i++){
        objectArray[i]->Start();
    }
    started = true;
}

void ChoiceState::Pause() {}

void ChoiceState::Resume() {}

void ChoiceState::LoadAssets() {}
