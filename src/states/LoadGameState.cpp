#include "Camera.h"
#include "Sprite.h"
#include "defines/DefineInput.h"
#include "states/LoadGameState.h"
#include "selectors/LoadGameSelector.h"

LoadGameState::LoadGameState(): State(), selector(nullptr){

    GameObject* titleObj = new GameObject();

    std::shared_ptr<Sprite> titleImage = std::make_shared<Sprite>(*titleObj, "resources/img/blackBG.jpg");
    titleObj->AddComponent(titleImage);

    objectArray.emplace_back(titleObj);
    backGraundMusic = std::make_shared<Music>("resources/music/MusicMenu.flac");
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
        backGraundMusic->Stop();
    }
    else if(InputManager::GetInstance().KeyPress(ENTER_KEY) && (selector.get()->GetSelected() == 0)){
        PuzzleState* newState = new PuzzleState(1);
        Game::GetInstance().Push(newState);
        popRequested = true;
        backGraundMusic->Stop();
    }
    else if(InputManager::GetInstance().KeyPress(ENTER_KEY) && (selector->GetSelected() == 1)){
        PuzzleState* newState = new PuzzleState(1);
        Game::GetInstance().Push(newState);
        popRequested = true;
        backGraundMusic->Stop();
    }
    else if(InputManager::GetInstance().KeyPress(ENTER_KEY) && (selector->GetSelected() == 2)){
        PuzzleState* newState = new PuzzleState(1);
        Game::GetInstance().Push(newState);
        popRequested = true;
        backGraundMusic->Stop();
    }
    for (int i = 0; i < (int) objectArray.size(); i++) {
        objectArray[i]->Update(dt);
    }   
}

void LoadGameState::LoadAssets(){
    
}

void LoadGameState::Render() {
    
    for (std::vector<int>::size_type i = 0; i < objectArray.size(); i++){
        objectArray[i]->Render();
    }
}

void LoadGameState::Start(){
    
    GameObject* selectorObj = new GameObject();
    selector = std::make_shared<LoadGameSelector>(*selectorObj);
    selectorObj->AddComponent(selector);
    
    objectArray.emplace_back(selectorObj);

    for (int i = 0; i < (int)objectArray.size(); i++){
        objectArray[i]->Start();
    }
    started = true;
    backGraundMusic->Play();
}

void LoadGameState::Pause(){}

void LoadGameState::Resume(){
    Camera::pos.x = 0;
    Camera::pos.y = 0;
    backGraundMusic->Play();
}