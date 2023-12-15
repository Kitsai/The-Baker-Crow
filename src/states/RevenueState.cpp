#include "states/RevenueState.h"
#include "items.h"
#include "states/PuzzleState.h"
#include "TukiB.h"

std::vector<Vec2> positionsRevenue = {Vec2(463, 153), Vec2(465, 267), Vec2(455, 355), Vec2(448,470), Vec2(450, 573)};

RevenueState::RevenueState(): State(), selector(nullptr){

    positionsRevenue = {Vec2(463, 153), Vec2(465, 267), Vec2(455, 355), Vec2(448,470), Vec2(450, 573)};
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
        if (selector){
            int num = selector->GetSelected();
            int count = 0;
            for (int i = 0; i < (int)positionsRevenue.size(); i++){
                if (positionsRevenue[i] == Vec2(0, 0)) {
                    count++;
                }
                if (count == num) {
                    num = i+1;
                    break;
                }
            }

            popRequested = true;
            Game::GetInstance().Push(new PuzzleState((num)));
        }
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
    std::vector<std::shared_ptr<Button>> buttons;

    for(int i = 0; i < (int)GameData::requests.size(); i++){
        int x;
        for(x = 0; x < (int)GameData::recipes.size(); x++){
            if(GameData::recipes[x] == GameData::requests[i]) break;
        }
        
        if (positionsRevenue[x] != Vec2(0, 0)){
            Button* butter = new Button(positionsRevenue[x], "resources/img/revenues/"+GameData::requests[i]+".png", GameData::requests[i]  ,false);
            buttons.push_back((std::shared_ptr<Button>) butter);
            GameData::chosenRequest = GameData::requests[i];
            positionsRevenue[x] = Vec2(0, 0);
        }
    }
    if(buttons.size()){
        selector = std::make_unique<Selector>(buttons);
    }
}