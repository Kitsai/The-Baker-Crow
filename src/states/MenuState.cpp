#include "states/MenuState.h"
#include "states/NewGameState.h"
#include "states/LoadGameState.h"

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
    UpdateArray(dt);
    selector->Update(dt);
}

void MenuState::LoadAssets(){
    
}

void MenuState::LoadButtons(){
    std::vector<std::shared_ptr<Button>> buttons;
    Button* buttonNewGame = new Button(Vec2(500, 200),"resources/img/MenuButton.png", "NEW GAME",36);
    Button* buttonLoadGame = new Button(Vec2(500, 400),"resources/img/MenuButton.png", "LOAD GAME",36);
    Button* buttonExitGame = new Button(Vec2(500, 600),"resources/img/MenuButton.png", "EXIT GAME",36);

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