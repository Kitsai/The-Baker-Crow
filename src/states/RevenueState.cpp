#include "states/RevenueState.h"
#include "items.h"
#include "states/PuzzleState.h"

RevenueState::RevenueState(): State(), selector(nullptr){

    GameObject* titleObj = new GameObject();
    titleObj->box.x = 350;
    titleObj->box.y = 10;
    Sprite* titleImage = new Sprite(*titleObj, "resources/img/RevenuesBook.png");
    titleObj->AddComponent(titleImage);
    AddObject(titleObj);
}

RevenueState::~RevenueState(){
    objectArray.clear();
}

void RevenueState::Update(float dt){
    InputManager& iM = InputManager::GetInstance();

    if(iM.QuitRequested()) quitRequested = true;

    else if (iM.KeyPress(ENTER_KEY)){
        popRequested = true;
        Game::GetInstance().Push(new PuzzleState(selector->GetSelected()));
    }
    if (selector){
        selector->Update(dt);
    }

    for (int i = 0; i < (int) objectArray.size(); i++) {
        objectArray[i]->Update(dt);
    }
}

void RevenueState::LoadAssets(){
}

void RevenueState::Render() {
    for (std::vector<int>::size_type i = 0; i < objectArray.size(); i++){
        objectArray[i]->Render();
    }
}

void RevenueState::Start(){
    Camera::pos.x = 0;
    Camera::pos.y = 0;
    LoadRevenues();
    for (int i = 0; i < (int)objectArray.size(); i++){
        objectArray[i]->Start();
    }
    started = true;
}

void RevenueState::Pause(){}

void RevenueState::Resume(){
}

void RevenueState::LoadRevenues() {

    std::stack<Vec2> positions;
    std::vector<std::shared_ptr<Button>> buttons;

    positions.push(Vec2(450, 573));
    positions.push(Vec2(448, 470));
    positions.push(Vec2(455, 355));
    positions.push(Vec2(465, 267));
    positions.push(Vec2(463, 153));

    for(std::pair<bool, RevenuesItemType> item : GameData::revenuesCompleted ){
        //if(item.first){
        Button* butter = new Button(positions.top(), "resources/img/revenues/"+RevenuesItemTypeToString[item.second]+".png", RevenuesItemTypeToString[item.second]  ,false);
        buttons.push_back((std::shared_ptr<Button>) butter);
        positions.pop();
        //}
    }
    if(buttons.size()){
        selector = std::make_unique<Selector>(buttons);
    }
}