#include "Music.h"
#include "Camera.h"
#include "states/MenuState.h"
#include "states/StartState.h"
#include "defines/DefineInput.h"
#include "states/OverworldState.h"

StartState::StartState(): State(){
    
    GameObject* titleObj = new GameObject();

    Sprite *titleImage= new Sprite(*titleObj, "resources/img/StartImage.jpg");
    titleObj->AddComponent((std::shared_ptr<Sprite>)  titleImage);

    objectArray.emplace_back(titleObj);
    
    GameObject *textObj = new GameObject();
    std::string texto = "PRESS SPACEBAR OR ENTER TO PLAY";
    
    Text* startText = new Text(*textObj, "resources/font/Base.ttf", 64, TextStyle::BLENDED,texto, {200, 200, 200},{0, 0, 0},  true);
    textObj->AddComponent((std::shared_ptr<Text>) startText);
    textObj->box.SetCenter(Vec2((float)(Game::GetInstance().GetWindowWidth())/2, (float)(Game::GetInstance().GetWindowHeight())*7/8));
    
    objectArray.emplace_back(textObj);
    backGraundMusic = new Music("resources/music/MusicStart.flac");
}

StartState::~StartState(){
    objectArray.clear();
}

void StartState::Update(float dt){
    if ((InputManager::GetInstance().KeyPress(ESCAPE_KEY)) || (InputManager::GetInstance().QuitRequested())){
        quitRequested = true;
    }
    else if(InputManager::GetInstance().KeyPress(ENTER_KEY) || InputManager::GetInstance().KeyPress(SPACE_KEY)){
        MenuState* newState = new MenuState();
        Game::GetInstance().Push(newState);
        backGraundMusic->Stop();
    }
    for (int i = 0; i < objectArray.size(); i++) {
        objectArray[i]->Update(dt);
    }
}

void StartState::LoadAssets(){
    
}

void StartState::Render() {
    
    for (std::vector<int>::size_type i = 0; i < objectArray.size(); i++){
        objectArray[i]->Render();
    }
}

void StartState::Start(){
    LoadAssets();
    for (int i = 0; i < (int)objectArray.size(); i++){
        objectArray[i]->Start();
    }
    backGraundMusic->Play(-1);
    started = true;
}

void StartState::Pause(){

}

void StartState::Resume(){
    Camera::pos.x = 0;
    Camera::pos.y = 0;
    backGraundMusic->Play();
}