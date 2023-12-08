#include "Camera.h"
#include "states/BakeryState.h"
#include "states/MenuState.h"
#include "defines/DefineInput.h"
#include "states/NewGameState.h"
#include "states/LoadGameState.h"
#include "selectors/MenuSelector.h"
#include <memory>

MenuState::MenuState(): State(), selector(nullptr){

    GameObject* titleObj = new GameObject();

    Sprite* titleImage = new Sprite(*titleObj, "resources/img/MenuBackground.png");
    titleObj->AddComponent(titleImage);


    objectArray.emplace_back(titleObj);
    backGroundMusic =  std::make_unique<Music>("resources/music/MusicMenu.flac");
}

MenuState::~MenuState(){
    objectArray.clear();
    backGroundMusic->Stop(0);
}

void MenuState::Update(float dt){

    if (InputManager::GetInstance().QuitRequested()){
        quitRequested = true;
    }
    else if (InputManager::GetInstance().KeyPress(ESCAPE_KEY)){
        quitRequested = true;
    }
    else if(InputManager::GetInstance().KeyPress(ENTER_KEY) && (selector->GetSelected() == 0)){
        NewGameState* newState = new NewGameState();
        Game::GetInstance().Push(newState);
    }
    else if(InputManager::GetInstance().KeyPress(ENTER_KEY) && (selector->GetSelected() == 1)){
        LoadGameState* newState = new LoadGameState();
        Game::GetInstance().Push(newState);
    }
    else if(InputManager::GetInstance().KeyPress(ENTER_KEY) && (selector->GetSelected() == 2)){
        quitRequested = true;
    }
    for (int i = 0; i < (int) objectArray.size(); i++) {
        objectArray[i]->Update(dt);
    }
    selector->Update(dt);
}

void MenuState::LoadAssets(){
    
}

void MenuState::Render() {
    RenderArray();
}

void MenuState::Start(){
    
    selector = std::make_unique<MenuSelector>();

    StartArray();
    started = true;
    backGroundMusic->Play();
}

void MenuState::Pause(){
    backGroundMusic->Stop(50);
}

void MenuState::Resume(){
    Camera::pos.x = 0;
    Camera::pos.y = 0;
    backGroundMusic->Play();
}