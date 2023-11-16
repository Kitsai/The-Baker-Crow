#include "Camera.h"
#include "states/MenuState.h"
#include "defines/DefineInput.h"
#include "states/OverworldState.h"

MenuState::MenuState(): State(){
    
    GameObject* titleObj = new GameObject();

    Sprite *titleImage= new Sprite(*titleObj, "resources/img/MainMenu.jpg");
    titleObj->AddComponent((std::shared_ptr<Sprite>)  titleImage);

    objectArray.emplace_back(titleObj);
    backGraundMusic = new Music("resources/music/MusicMenu.flac");
}

MenuState::~MenuState(){
    objectArray.clear();
}

void MenuState::Update(float dt){
    if ((InputManager::GetInstance().KeyPress(ESCAPE_KEY)) || (InputManager::GetInstance().QuitRequested())){
        popRequested = true;
        backGraundMusic->Stop();
    }
    else if(InputManager::GetInstance().KeyPress(ENTER_KEY) || InputManager::GetInstance().KeyPress(SPACE_KEY)){
        OverworldState* newState = new OverworldState();
        Game::GetInstance().Push(newState);
        backGraundMusic->Stop();
    }
    for (int i = 0; i < objectArray.size(); i++) {
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
    LoadAssets();
    for (int i = 0; i < (int)objectArray.size(); i++){
        objectArray[i]->Start();
    }
    started = true;
    backGraundMusic->Play();
}

void MenuState::Pause(){

}

void MenuState::Resume(){
    Camera::pos.x = 0;
    Camera::pos.y = 0;
    backGraundMusic->Play();
}