#include "Camera.h"
#include "states/ResumeState.h"
#include "defines/DefineInput.h"
#include "states/NewGameState.h"
#include "states/LoadGameState.h"
#include "selectors/ResumeSelector.h"


ResumeState::ResumeState(): State(), selector(nullptr){

    GameObject* titleObj = new GameObject();
    titleObj->box.x = 400;
    titleObj->box.y = 50;
    Sprite* titleImage = new Sprite(*titleObj, "resources/img/ResumeBackground.png");
    titleObj->AddComponent(titleImage);
    AddObject(titleObj);
}

ResumeState::~ResumeState(){
    objectArray.clear();
}

void ResumeState::Update(float dt){

    if (InputManager::GetInstance().QuitRequested() || 
        InputManager::GetInstance().KeyPress(ESCAPE_KEY) || 
        (InputManager::GetInstance().KeyPress(ENTER_KEY) && (selector->GetSelected() == 0))){
        popRequested = true;
    }
    
    else if(InputManager::GetInstance().KeyPress(ENTER_KEY) && (selector->GetSelected() == 1)){

    }
    
    else if(InputManager::GetInstance().KeyPress(ENTER_KEY) && (selector->GetSelected() == 2)){
        popRequested = true;
        GameData::quitOWState = true;
    }
    
    for (int i = 0; i < (int) objectArray.size(); i++) {
        objectArray[i]->Update(dt);
    }
    
    selector->Update(dt);
}

void ResumeState::LoadAssets(){
    
}

void ResumeState::Render() {
    
    for (std::vector<int>::size_type i = 0; i < objectArray.size(); i++){
        objectArray[i]->Render();
    }
}

void ResumeState::Start(){
    Camera::pos.x = 0;
    Camera::pos.y = 0;
    selector = std::make_unique<ResumeSelector>();
    for (int i = 0; i < (int)objectArray.size(); i++){
        objectArray[i]->Start();
    }
    started = true;
}
void ResumeState::Pause(){}

void ResumeState::Resume(){
}