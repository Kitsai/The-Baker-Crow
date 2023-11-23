#include "Sprite.h"
#include "Camera.h"
#include "defines/DefineInput.h"
#include "states/NewGameState.h"
#include "selectors/NewGameSelector.h"

NewGameState::NewGameState(): State(), selector(nullptr){

    GameObject* titleObj = new GameObject();
    std::shared_ptr<Sprite> titleImage = std::make_shared<Sprite>(*titleObj, "resources/img/blackBG.jpg");
    
    titleObj->AddComponent(titleImage);

    objectArray.emplace_back(titleObj);
    backGraundMusic = std::make_shared<Music>("resources/music/MusicMenu.flac");
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
        backGraundMusic->Stop();
    }
    else if(InputManager::GetInstance().KeyPress(ENTER_KEY) && (selector->GetSelected() == 1)){
        OverworldState* newState = new OverworldState();
        Game::GetInstance().Push(newState);
        popRequested = true;
        backGraundMusic->Stop();
    }
    else if(InputManager::GetInstance().KeyPress(ENTER_KEY) && (selector->GetSelected() == 2)){
        OverworldState* newState = new OverworldState();
        Game::GetInstance().Push(newState);
        popRequested = true;
        backGraundMusic->Stop();
    }
    selector->Update(dt);
    UpdateArray(dt);
}

void NewGameState::LoadAssets(){
    
}

void NewGameState::Render() {
    RenderArray();
}

void NewGameState::Start(){
    
    GameObject* selectorObj = new GameObject();
    selector = std::make_shared<NewGameSelector>(*selectorObj);
    selectorObj->AddComponent(selector);
    
    objectArray.emplace_back(selectorObj);


    StartArray();
    started = true;
    backGraundMusic->Play();
}

void NewGameState::Pause(){}

void NewGameState::Resume(){
    Camera::pos.x = 0;
    Camera::pos.y = 0;
    backGraundMusic->Play();
}
