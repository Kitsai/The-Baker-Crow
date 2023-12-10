#include "states/ChoiceState.h"

ChoiceState::ChoiceState() : State() {

    GameData::requests = {"cake", "brigadeiro", "macarons"};

    GameObject* titleObj = new GameObject();
    titleObj->box.x = 450;
    titleObj->box.y = 10;
    Sprite* titleImage = new Sprite(*titleObj, "resources/img/recipes.png");
    titleObj->AddComponent(titleImage);
    AddObject(titleObj);

    for (int i = 0; i < GameData::requests.size(); i++){
        GameObject* requestObj = new GameObject();
        requestObj->box.x = 450;
        requestObj->box.y = 100 + 100*i;
        Sprite* requestImage = new Sprite(*requestObj, "resources/img/food/" + GameData::requests[i] + ".png");
        requestObj->AddComponent(requestImage);
        AddObject(requestObj);
    }

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
