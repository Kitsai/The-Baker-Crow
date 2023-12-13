#include "states/BakeryState.h"
#include "states/NewGameState.h"

NewGameState::NewGameState(): State(), selector(nullptr){

    GameObject* titleObj = new GameObject();
    Sprite* titleImage = new Sprite(*titleObj, "resources/img/blackBG.jpg");
    
    titleObj->AddComponent(titleImage);

    objectArray.emplace_back(titleObj);
    //backGroundMusic =  std::make_unique<Music>("resources/music/MusicMenu.flac");
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
    else if(InputManager::GetInstance().KeyPress(ENTER_KEY) && (selector.get()->GetSelected() == 1)){
        GameData::intro = true;
        BakeryState* newState = new BakeryState();
        Game::GetInstance().Push(newState);
        popRequested = true;
        GameData::backGroundMusic->Stop();
    }
    else if(InputManager::GetInstance().KeyPress(ENTER_KEY) && (selector->GetSelected() == 2)){
        OverworldState* newState = new OverworldState();
        Game::GetInstance().Push(newState);
        popRequested = true;
        GameData::backGroundMusic->Stop();
    }
    else if(InputManager::GetInstance().KeyPress(ENTER_KEY) && (selector->GetSelected() == 3)){
        OverworldState* newState = new OverworldState();
        Game::GetInstance().Push(newState);
        popRequested = true;
        GameData::backGroundMusic->Stop();
    }
    UpdateArray(dt);
    selector->Update(dt);
}

void NewGameState::LoadAssets(){
    
}

void NewGameState::LoadButtons(){
    std::vector<std::shared_ptr<Button>> buttons;
    Button* buttonGame1 = new Button(Vec2(0, 300),"resources/img/MenuButton.png", "NEW GAME 1", 36);
    Button* buttonGame2 = new Button(Vec2(400, 300),"resources/img/MenuButton.png", "NEW GAME 2", 36);
    Button* buttonGame3 = new Button(Vec2(800, 300),"resources/img/MenuButton.png", "NEW GAME 3", 36);

    buttons.push_back((std::shared_ptr<Button>) buttonGame1);
    buttons.push_back((std::shared_ptr<Button>) buttonGame2);
    buttons.push_back((std::shared_ptr<Button>) buttonGame3);
    
    selector = std::make_unique<Selector>(buttons);
}

void NewGameState::Render() {
    RenderArray();
}

void NewGameState::Start(){
    LoadButtons();
    StartArray();
    started = true;
    //backGroundMusic->Play();
}

void NewGameState::Pause(){
    GameData::backGroundMusic->Stop(0);
}

void NewGameState::Resume(){
    Camera::pos.x = 0;
    Camera::pos.y = 0;
    GameData::backGroundMusic->Play();
}