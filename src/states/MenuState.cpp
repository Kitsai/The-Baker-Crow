#include "Camera.h"
#include "states/MenuState.h"
#include "defines/DefineInput.h"
#include "states/NewGameState.h"
#include "states/LoadGameState.h"
#include "selectors/MenuSelector.h"
#include <memory>

MenuState::MenuState(): State(), selector(nullptr){

    GameObject* titleObj = new GameObject();

    Sprite* titleImage = new Sprite(*titleObj, "resources/img/MainMenu.jpg");
    titleObj->AddComponent(titleImage);


    objectArray.emplace_back(titleObj);
    backGroundMusic =  std::make_unique<Music>("resources/music/MusicMenu.flac");
}

MenuState::~MenuState(){
    objectArray.clear();
}

void MenuState::Update(float dt){

    if (InputManager::GetInstance().QuitRequested()){
        quitRequested = true;
    }
    else if (InputManager::GetInstance().KeyPress(ESCAPE_KEY)){
        popRequested = true;
    }
    else if(InputManager::GetInstance().KeyPress(ENTER_KEY) && (selector->GetSelected() == 0)){
        NewGameState* newState = new NewGameState();
        Game::GetInstance().Push(newState);
        popRequested = true;
        backGroundMusic->Stop(50);
    }
    else if(InputManager::GetInstance().KeyPress(ENTER_KEY) && (selector->GetSelected() == 1)){
        LoadGameState* newState = new LoadGameState();
        Game::GetInstance().Push(newState);
        popRequested = true;
        backGroundMusic->Stop(50);
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

void MenuState::Pause(){}

void MenuState::Resume(){
    Camera::pos.x = 0;
    Camera::pos.y = 0;

    backGroundMusic->Play();
}
