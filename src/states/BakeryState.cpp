#include "states/BakeryState.h"
#include "Game.h"
#include "TukiB.h"
#include "states/ResumeState.h"
#include "states/OverworldState.h"

BakeryState::BakeryState() : State() {
    floor = 0;

    GameObject* bg = new GameObject();
    bg->AddComponent(new Sprite(*bg, "resources/img/blackBG.jpg"));
    bg->box.SetCenter({Game::GetInstance().GetWindowWidth() * 0.5F,Game::GetInstance().GetWindowHeight() * 0.5F});
    bg->AddComponent(new CameraFollower(*bg));
    AddObject(bg);

    // keep as game object 1 of bakeryState
    GameObject* room = new GameObject();
    room->AddComponent(new Sprite(*room, "resources/img/bedroom/bedroom.png"));
    room->box.SetCenter({Game::GetInstance().GetWindowWidth() * 0.5F,Game::GetInstance().GetWindowHeight() * 0.5F});
    AddObject(room);


    GameObject* tuki = new GameObject();
    tuki->AddComponent(new TukiB(*tuki));
    tuki->box.SetCenter({500,525});
    AddObject(tuki);

    Camera::Follow(tuki);

    GameData::playerAlive = true;
    backGroundMusic = std::make_unique<Music>("resources/music/MusicWorld.flac");

    GameObject* speakBalloon = new GameObject();
    Sprite* sprite = new Sprite(*speakBalloon, "resources/img/MenuButton.png");
    speakBalloon->AddComponent(sprite);
    sprite->SetScale(3.0f, 2.5f);
    speakBalloon->box.x = 320;
    speakBalloon->box.y = 570;

    //AddObject(speakBalloon);
}

BakeryState::~BakeryState() {
    objectArray.clear();
}

void BakeryState::LoadAssets() {
    // Load assets
}

void BakeryState::Update(float dt) {
    InputManager& iM = InputManager::GetInstance();

     if (iM.KeyPress(ESCAPE_KEY) || iM.QuitRequested() || iM.KeyPress(P_KEY)){
        shadowObj = new GameObject();        
        Sprite* shadow = new  Sprite(*shadowObj,"resources/img/Shadow.png");
        shadow->SetAlpha(128);
        shadowObj->box.x = 0;
        shadowObj->box.y = 0;
        shadowObj->AddComponent(shadow);
        AddObject(shadowObj);
        
        ResumeState* newState = new ResumeState();
        Game::GetInstance().Push(newState);
    }
    if(GameData::quitOWState){
        popRequested = true; 
        GameData::quitOWState = false;
    }

    // changes floor if Tuki goes down/up stairs
    int newFloor = ((TukiB*)Player::player)->GetFloor();
    if (newFloor != floor) {
        floor = newFloor;
        objectArray[1]->RemoveComponent(objectArray[1]->GetComponent("Sprite").lock().get());
        if (floor == 0) 
            objectArray[1]->AddComponent(new Sprite(*objectArray[1], "resources/img/bedroom/bedroom.png"));
        else if (floor == 1)
            objectArray[1]->AddComponent(new Sprite(*objectArray[1], "resources/img/bakery_test.png"));
        objectArray[1]->box.SetCenter({Game::GetInstance().GetWindowWidth() * 0.5F,Game::GetInstance().GetWindowHeight() * 0.5F});
        if (floor == 2) {
            OverworldState* overworld = new OverworldState();
            Game::GetInstance().Push(overworld);
            popRequested = true;
            GameData::quitOWState = false;
            backGroundMusic->Stop(50);
        }
    }

    UpdateArray(dt);
    CheckCollisions();
    DeleteObjects();
}

void BakeryState::Render() {
    RenderArray();
}

void BakeryState::Start() {
    LoadAssets();
    StartArray();
    started = true;
    backGroundMusic->Play();
}

void BakeryState::Pause() {
    backGroundMusic->Stop();
}

void BakeryState::Resume() {
    if(shadowObj){
        RemoveObject(shadowObj);
        shadowObj = nullptr;
    }
    backGroundMusic->Play();
}