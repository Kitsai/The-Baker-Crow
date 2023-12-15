#include "states/MenuState.h"
#include "states/NewGameState.h"
#include "states/LoadGameState.h"

MenuState::MenuState(): State(), selector(nullptr){

    GameObject* titleObj = new GameObject();

    Sprite* titleImage = new Sprite(*titleObj, "resources/img/main_page.png");
    titleObj->AddComponent(titleImage);


    objectArray.emplace_back(titleObj);
    GameData::backGroundMusic = std::make_unique<Music>("resources/music/MusicMenu.flac");
}

MenuState::~MenuState(){
    objectArray.clear();
    GameData::backGroundMusic->Stop(0);
}

void MenuState::Update(float dt){

    if (InputManager::GetInstance().QuitRequested()){
        quitRequested = true;
    }
    else if (InputManager::GetInstance().KeyPress(ESCAPE_KEY)){
        quitRequested = true;
    }
    else if(InputManager::GetInstance().KeyPress(ENTER_KEY) && (selector->GetSelected() == 1)){
        NewGameState* newState = new NewGameState();
        Game::GetInstance().Push(newState);
    }
    else if(InputManager::GetInstance().KeyPress(ENTER_KEY) && (selector->GetSelected() == 2)){
        LoadGameState* newState = new LoadGameState();
        Game::GetInstance().Push(newState);
    }
    else if(InputManager::GetInstance().KeyPress(ENTER_KEY) && (selector->GetSelected() == 3)){
        quitRequested = true;
    }
    UpdateArray(dt);
    selector->Update(dt);
}

void MenuState::LoadAssets(){
    
}

void MenuState::LoadButtons(){
    std::vector<std::shared_ptr<Button>> buttons;
    Button* buttonNewGame  = new Button(Vec2(376, 286),"resources/img/MenuButton.png", "NEW GAME",30);
    Button* buttonLoadGame = new Button(Vec2(376, 427),"resources/img/MenuButton.png", "LOAD GAME",30);
    Button* buttonExitGame = new Button(Vec2(376, 565),"resources/img/MenuButton.png", "EXIT GAME",30);

    buttons.push_back((std::shared_ptr<Button>) buttonNewGame);
    buttons.push_back((std::shared_ptr<Button>) buttonLoadGame);
    buttons.push_back((std::shared_ptr<Button>) buttonExitGame);

    selector = std::make_unique<Selector>(buttons);
}

void MenuState::Render() {
    RenderArray();
}

void MenuState::Start(){
    LoadButtons();
    StartArray();
    started = true;
    GameData::backGroundMusic->Play();
}

void MenuState::Pause(){
    //GameData::backGroundMusic->Pause();
}

void MenuState::Resume(){
    Camera::pos.x = 0;
    Camera::pos.y = 0;
    GameData::backGroundMusic = std::make_unique<Music>("resources/music/MusicMenu.flac");
    GameData::backGroundMusic->Play();
}