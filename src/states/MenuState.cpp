#include "Camera.h"
#include "states/MenuState.h"
#include "defines/DefineInput.h"
#include "states/NewGameState.h"
#include "states/LoadGameState.h"
#include "selectors/MenuSelector.h"

MenuState::MenuState(): State(), selector(nullptr){

    GameObject* titleObj = new GameObject();

    std::shared_ptr<Sprite> titleImage = std::make_shared<Sprite>(*titleObj, "resources/img/MainMenu.jpg");
    titleObj->AddComponent(titleImage);

    objectArray.emplace_back(titleObj);
    backGraundMusic = std::make_shared<Music>("resources/music/MusicMenu.flac");
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
    else if(InputManager::GetInstance().KeyPress(ENTER_KEY) && (selector.get()->GetSelected() == 0)){
        NewGameState* newState = new NewGameState();
        Game::GetInstance().Push(newState);
        popRequested = true;
        backGraundMusic->Stop();
    }
    else if(InputManager::GetInstance().KeyPress(ENTER_KEY) && (selector->GetSelected() == 1)){
        LoadGameState* newState = new LoadGameState();
        Game::GetInstance().Push(newState);
        popRequested = true;
        backGraundMusic->Stop();
    }
    for (int i = 0; i < (int) objectArray.size(); i++) {
        objectArray[i]->Update(dt);
    }   
}

void MenuState::LoadAssets(){
    
}

void MenuState::Render() {
    
    for (std::vector<int>::size_type i = 0; i < objectArray.size(); i++){
        objectArray[i]->Render();
    }
}

void MenuState::Start(){
    
    GameObject* selectorObj = new GameObject();
    selector = std::make_shared<MenuSelector>(*selectorObj);
    selectorObj->AddComponent(selector);
    
    objectArray.emplace_back(selectorObj);

    for (int i = 0; i < (int)objectArray.size(); i++){
        objectArray[i]->Start();
    }
    started = true;
    backGraundMusic->Play();
}

void MenuState::Pause(){}

void MenuState::Resume(){
    Camera::pos.x = 0;
    Camera::pos.y = 0;
    backGraundMusic->Play();
}