#include "states/RevenueState.h"
#include "items.h"
#include "states/PuzzleState.h"
#include "TukiB.h"

int min = 10;

RevenueState::RevenueState(): State(), selector(nullptr){

    min = 10;
    GameObject* titleObj = new GameObject();
    titleObj->box.x = 350;
    titleObj->box.y = 10;
    Sprite* titleImage = new Sprite(*titleObj, "resources/img/RevenuesBook.png");
    titleObj->AddComponent(titleImage);
    AddObject(titleObj);
}

RevenueState::~RevenueState(){
    objectArray.clear();
    ((TukiB*)Player::player)->ChangeCooking(false);
}

void RevenueState::Update(float dt){
    InputManager& iM = InputManager::GetInstance();

    if(iM.QuitRequested()) quitRequested = true;

    if (iM.KeyPress(ESCAPE_KEY)) popRequested = true;

    else if (iM.KeyPress(Z_KEY)){
        popRequested = true;
        Game::GetInstance().Push(new PuzzleState((selector->GetSelected())+min));
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
    std::vector<Vec2> positions = {Vec2(463, 153), Vec2(465, 267), Vec2(455, 355), Vec2(448,470), Vec2(450, 573)};
    std::vector<std::shared_ptr<Button>> buttons;

    for(int i = 0; i < (int)GameData::requests.size(); i++){
        int x;
        for(x = 0; x < (int)GameData::recipes.size(); x++){
            if(GameData::recipes[x] == GameData::requests[i]) break;
        }
        
        if (x < min) min = x;
        
        if (positions[x] != Vec2(0, 0)){
            Button* butter = new Button(positions[x], "resources/img/revenues/"+GameData::requests[i]+".png", GameData::requests[i]  ,false);
            buttons.push_back((std::shared_ptr<Button>) butter);
            GameData::chosenRequest = GameData::requests[i];
            positions[x] = Vec2(0, 0);
        }
    }
    if(buttons.size()){
        selector = std::make_unique<Selector>(buttons);
    }
}