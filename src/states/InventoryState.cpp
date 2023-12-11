#include "Camera.h"
#include "InputManager.h"
#include "states/InventoryState.h"
#include "defines/DefineInput.h"
#include "states/NewGameState.h"
#include "states/LoadGameState.h"

InventoryState::InventoryState(): State(){

    GameObject* titleObj = new GameObject();
    titleObj->box.x = 400;
    titleObj->box.y = 50;
    Sprite* titleImage = new Sprite(*titleObj, "resources/img/RevenueBook.png");
    titleObj->AddComponent(titleImage);
    AddObject(titleObj);
}

InventoryState::~InventoryState(){
    objectArray.clear();
}

void InventoryState::Update(float dt){
    InputManager& iM = InputManager::GetInstance();

    if(iM.QuitRequested()) quitRequested = true;

    if (iM.KeyPress(ESCAPE_KEY)){
        popRequested = true;
    }
    else if(iM.KeyPress(ENTER_KEY)){
        popRequested = true;
    }
    
    for (int i = 0; i < (int) objectArray.size(); i++) {
        objectArray[i]->Update(dt);
    }
    
}

void InventoryState::LoadAssets(){
    
}

void InventoryState::Render() {
    
    for (std::vector<int>::size_type i = 0; i < objectArray.size(); i++){
        objectArray[i]->Render();
    }
}

void InventoryState::Start(){
    Camera::pos.x = 0;
    Camera::pos.y = 0;
    for (int i = 0; i < (int)objectArray.size(); i++){
        objectArray[i]->Start();
    }
    started = true;
}

void InventoryState::Pause(){}

void InventoryState::Resume(){
}