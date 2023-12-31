#include "SaveController.h"
#include "states/BakeryState.h"
#include "states/LoadGameState.h"

LoadGameState::LoadGameState(): State(), selector(nullptr){

    GameObject* titleObj = new GameObject();

    Sprite* titleImage = new Sprite(*titleObj, "resources/img/LoadSave/backGroundLS.png");
    titleObj->AddComponent(titleImage);

    objectArray.emplace_back(titleObj);
    GameData::backGroundMusic =  std::make_unique<Music>("resources/music/MusicMenu.flac");
}

LoadGameState::~LoadGameState(){
    objectArray.clear();
}

void LoadGameState::Update(float dt){

    if (InputManager::GetInstance().QuitRequested()){
        quitRequested = true;
    }
    else if (InputManager::GetInstance().KeyPress(ESCAPE_KEY)){
        popRequested = true;
        GameData::backGroundMusic->Stop(0);
    }
    else if(InputManager::GetInstance().KeyPress(ENTER_KEY) && (selector.get()->GetSelected() == 1)){
        SaveController::ReadSave(1);
        GameData::currentGame = 1;
        GameData::SaveIsInUse = 1;
        
        BakeryState* newState = new BakeryState();
        Game::GetInstance().Push(newState);
        popRequested = true;
        GameData::backGroundMusic->Stop(0);
    }
    else if(InputManager::GetInstance().KeyPress(ENTER_KEY) && (selector->GetSelected() == 2)){
        GameData::currentGame = 2;
        GameData::SaveIsInUse = 1;
        SaveController::ReadSave(2);
        
        BakeryState* newState = new BakeryState();
        Game::GetInstance().Push(newState);
        popRequested = true;
        GameData::backGroundMusic->Stop(0);
    }
    UpdateArray(dt);
    selector->Update(dt);   
}

void LoadGameState::LoadAssets(){
    
}

void LoadGameState::LoadButtons(){
    std::vector<std::shared_ptr<Button>> buttons;
    Button* buttonGame1 = new Button(Vec2(0, 0),"resources/img/LoadSave/Chossed.png", "NEW GAME 1", false);
    Button* buttonGame2 = new Button(Vec2(0, 20),"resources/img/LoadSave/notChossed.png", "NEW GAME 2", false);


    buttons.push_back((std::shared_ptr<Button>) buttonGame1);
    buttons.push_back((std::shared_ptr<Button>) buttonGame2);
    
    selector = std::make_unique<Selector>(buttons);

}

void LoadGameState::Render() {
    RenderArray();
}

void LoadGameState::Start(){    
    LoadButtons();
    StartArray();
    started = true;
    //GameData::backGroundMusic->Play();
}

void LoadGameState::Pause(){
    GameData::backGroundMusic->Stop(0);
}

void LoadGameState::Resume(){
    Camera::pos.x = 0;
    Camera::pos.y = 0;
    GameData::backGroundMusic->Play();
}