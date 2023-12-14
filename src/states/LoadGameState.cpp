#include "states/LoadGameState.h"

LoadGameState::LoadGameState(): State(), selector(nullptr){

    GameObject* titleObj = new GameObject();

    Sprite* titleImage = new Sprite(*titleObj, "resources/img/blackBG.jpg");
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
        PuzzleState* newState = new PuzzleState(1);
        Game::GetInstance().Push(newState);
        popRequested = true;
        GameData::backGroundMusic->Stop(0);
    }
    else if(InputManager::GetInstance().KeyPress(ENTER_KEY) && (selector->GetSelected() == 2)){
        PuzzleState* newState = new PuzzleState(2);
        Game::GetInstance().Push(newState);
        popRequested = true;
        GameData::backGroundMusic->Stop(0);
    }
    else if(InputManager::GetInstance().KeyPress(ENTER_KEY) && (selector->GetSelected() == 3)){
        PuzzleState* newState = new PuzzleState(3);
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
    Button* buttonGame1 = new Button(Vec2(0, 300),"resources/img/MenuButton.png", "LOAD GAME 1", 36);
    Button* buttonGame2 = new Button(Vec2(400, 300),"resources/img/MenuButton.png", "LOAD GAME 2", 36);
    Button* buttonGame3 = new Button(Vec2(800, 300),"resources/img/MenuButton.png", "LOAD GAME 3", 36);

    buttons.push_back((std::shared_ptr<Button>) buttonGame1);
    buttons.push_back((std::shared_ptr<Button>) buttonGame2);
    buttons.push_back((std::shared_ptr<Button>) buttonGame3);
    
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