#include "SaveController.h"
#include "TileSet.h"
#include "states/ResumeState.h"

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
    InputManager& iM = InputManager::GetInstance();

    if(iM.QuitRequested()) quitRequested = true;

    if (iM.KeyPress(ESCAPE_KEY) || 
        (iM.KeyPress(ENTER_KEY) && (selector->GetSelected() == 1))){
        popRequested = true;
    }
    
    else if(iM.KeyPress(ENTER_KEY) && (selector->GetSelected() == 2)){
        SaveController::WriteSave(2);
        popRequested = true;
    }
    
    else if(iM.KeyPress(ENTER_KEY) && (selector->GetSelected() == 3)){
        popRequested = true;
        GameData::quitOWState = true;
    }
    UpdateArray(dt);    
    selector->Update(dt);
}

void ResumeState::LoadAssets(){
    
}

void ResumeState::LoadButtons(){
    std::vector<std::shared_ptr<Button>> buttons;
    
    Button* buttonResumeGame = new Button(Vec2(500, 180),"resources/img/ResumeButton.png", "Resume",36);
    Button* buttonSaveGame = new Button(Vec2(500, 290),"resources/img/ResumeButton.png", "Save Game", 36);
    Button* buttonExitsGame = new Button(Vec2(500, 400),"resources/img/ResumeButton.png", "Exit Game", 36);

    buttons.push_back((std::shared_ptr<Button>) buttonResumeGame);
    buttons.push_back((std::shared_ptr<Button>) buttonSaveGame);
    buttons.push_back((std::shared_ptr<Button>) buttonExitsGame);

    selector = std::make_unique<Selector>(buttons);
}

void ResumeState::Render() {
    RenderArray();
}

void ResumeState::Start(){
    Camera::pos.x = 0;
    Camera::pos.y = 0;
    
    LoadButtons();
    StartArray();
    started = true;
}
void ResumeState::Pause(){}

void ResumeState::Resume(){
}