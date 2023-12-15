#include "SaveController.h"
#include "states/BakeryState.h"
#include "states/NewGameState.h"
#include <iostream>
#include <string>

NewGameState::NewGameState(): State(), selector(nullptr){

    GameObject* titleObj = new GameObject();
    Sprite* titleImage = new Sprite(*titleObj, "resources/img/LoadSave/backGroundLS.png");
    
    titleObj->AddComponent(titleImage);

    objectArray.emplace_back(titleObj);
    //backGroundMusic =  std::make_unique<Music>("resources/music/MusicMenu.flac");
}

NewGameState::~NewGameState(){
    objectArray.clear();
}

void NewGameState::Update(float dt){

    if (InputManager::GetInstance().QuitRequested()){
        quitRequested = true;
    }
    else if (InputManager::GetInstance().KeyPress(ESCAPE_KEY)){
        popRequested = true;
    }
    else if(InputManager::GetInstance().KeyPress(ENTER_KEY) && (selector.get()->GetSelected() == 1)){
        SaveController::WriteSave(1);

        GameData::intro = true;
        BakeryState* newState = new BakeryState();
        Game::GetInstance().Push(newState);
        popRequested = true;
        GameData::backGroundMusic->Stop(0);
    }
    else if(InputManager::GetInstance().KeyPress(ENTER_KEY) && (selector->GetSelected() == 2)){
        SaveController::WriteSave(2);

        OverworldState* newState = new OverworldState();
        Game::GetInstance().Push(newState);
        popRequested = true;
        GameData::backGroundMusic->Stop(0);
    }
    UpdateArray(dt);
    selector->Update(dt);
}

void NewGameState::LoadAssets(){
    
}

void NewGameState::LoadButtons(){
    std::vector<std::shared_ptr<Button>> buttons;
    Button* buttonGame1 = new Button(Vec2(0, 0),"resources/img/LoadSave/Chossed.png", "NEW GAME 1", false);
    Button* buttonGame2 = new Button(Vec2(0, 20),"resources/img/LoadSave/notChossed.png", "NEW GAME 2", false);


    buttons.push_back((std::shared_ptr<Button>) buttonGame1);
    buttons.push_back((std::shared_ptr<Button>) buttonGame2);
    
    selector = std::make_unique<Selector>(buttons);
}

void NewGameState::Render() {
    RenderArray();
}

void NewGameState::Start(){
    LoadButtons();
    StartArray();
    started = true;
    //backGroundMusic->Play();
}

void NewGameState::Pause(){
    GameData::backGroundMusic->Stop(0);
}

void NewGameState::Resume(){
    Camera::pos.x = 0;
    Camera::pos.y = 0;
    GameData::backGroundMusic->Play();
}