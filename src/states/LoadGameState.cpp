#include "Camera.h"
#include "Sprite.h"
#include "defines/DefineInput.h"
#include "states/LoadGameState.h"
#include "selectors/LoadGameSelector.h"
#include <memory>

LoadGameState::LoadGameState(): State(), selector(nullptr){

    GameObject* titleObj = new GameObject();

    Sprite* titleImage = new Sprite(*titleObj, "resources/img/blackBG.jpg");
    titleObj->AddComponent(titleImage);

    objectArray.emplace_back(titleObj);
    backGroundMusic =  std::make_unique<Music>("resources/music/MusicMenu.flac");
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
        backGroundMusic->Stop(50);
    }
    else if(InputManager::GetInstance().KeyPress(ENTER_KEY) && (selector.get()->GetSelected() == 0)){
        PuzzleState* newState = new PuzzleState(1);
        Game::GetInstance().Push(newState);
        popRequested = true;
        backGroundMusic->Stop(50);
    }
    else if(InputManager::GetInstance().KeyPress(ENTER_KEY) && (selector->GetSelected() == 1)){
        PuzzleState* newState = new PuzzleState(2);
        Game::GetInstance().Push(newState);
        popRequested = true;
        backGroundMusic->Stop(50);
    }
    else if(InputManager::GetInstance().KeyPress(ENTER_KEY) && (selector->GetSelected() == 2)){
        PuzzleState* newState = new PuzzleState(3);
        Game::GetInstance().Push(newState);
        popRequested = true;
        backGroundMusic->Stop(50);
    }
    for (int i = 0; i < (int) objectArray.size(); i++) {
        objectArray[i]->Update(dt);
    }
    selector->Update(dt);   
}

void LoadGameState::LoadAssets(){
    
}

void LoadGameState::Render() { 
    RenderArray();
}

void LoadGameState::Start(){
    
    selector = std::make_unique<LoadGameSelector>();
    for (int i = 0; i < (int)objectArray.size(); i++){
        objectArray[i]->Start();
    }
    started = true;
    backGroundMusic->Play();
}

void LoadGameState::Pause(){}

void LoadGameState::Resume(){
    Camera::pos.x = 0;
    Camera::pos.y = 0;
    backGroundMusic->Play();
}