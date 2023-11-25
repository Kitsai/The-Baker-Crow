#include "Sprite.h"
#include "Camera.h"
#include "defines/DefineInput.h"
#include "states/NewGameState.h"
#include "selectors/NewGameSelector.h"
#include <memory>

NewGameState::NewGameState(): State(), selector(nullptr){

    GameObject* titleObj = new GameObject();
    Sprite* titleImage = new Sprite(*titleObj, "resources/img/blackBG.jpg");
    
    titleObj->AddComponent(titleImage);

    objectArray.emplace_back(titleObj);
    backGroundMusic =  std::make_unique<Music>("resources/music/MusicMenu.flac");
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
    else if(InputManager::GetInstance().KeyPress(ENTER_KEY) && (selector.get()->GetSelected() == 0)){
        OverworldState* newState = new OverworldState();
        Game::GetInstance().Push(newState);
        popRequested = true;
        backGroundMusic->Stop();
    }
    else if(InputManager::GetInstance().KeyPress(ENTER_KEY) && (selector->GetSelected() == 1)){
        OverworldState* newState = new OverworldState();
        Game::GetInstance().Push(newState);
        popRequested = true;
        backGroundMusic->Stop();
    }
    else if(InputManager::GetInstance().KeyPress(ENTER_KEY) && (selector->GetSelected() == 2)){
        OverworldState* newState = new OverworldState();
        Game::GetInstance().Push(newState);
        popRequested = true;
        backGroundMusic->Stop();
    }
    for (int i = 0; i < (int) objectArray.size(); i++) {
        objectArray[i]->Update(dt);
    }
    selector->Update(dt);
}

void NewGameState::LoadAssets(){
    
}

void NewGameState::Render() {
    
    for (std::vector<int>::size_type i = 0; i < objectArray.size(); i++){
        objectArray[i]->Render();
    }
}

void NewGameState::Start(){
    

    selector = std::make_unique<NewGameSelector>();

    for (int i = 0; i < (int)objectArray.size(); i++){
        objectArray[i]->Start();
    }
    started = true;
    backGroundMusic->Play();
}

void NewGameState::Pause(){}

void NewGameState::Resume(){
    Camera::pos.x = 0;
    Camera::pos.y = 0;
    backGroundMusic->Play();
}