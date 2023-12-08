#include "Component.h"
#include "GameData.h"
#include "HeartBar.h"
#include "Player.h"
#include "defines/DefineInput.h"
#include "enemies/Pancake.h"
#include "states/OverworldState.h"
#include "states/ResumeState.h"

OverworldState::OverworldState(): State(), shadowObj(nullptr) {

    // Game& game = Game::GetInstance();
    GameObject* bg = new GameObject();
    bg->AddComponent(new Sprite(*bg,"resources/img/blackBG.jpg"));
    bg->AddComponent(new CameraFollower(*bg));
    AddObject(bg);

    GameObject* map = new GameObject();
    map->AddComponent(new Sprite(*map, "resources/img/mapa_1_4x.jpg"));
    AddObject(map);
    
    GameObject* tuki = new GameObject();
    tuki->AddComponent(new TukiOW(*tuki));
    AddObject(tuki);
    tuki->box.SetCenter(Vec2(817,2316));
    
    GameObject* pancake = new GameObject();
    pancake->AddComponent(new Pancake(*pancake,100));
    AddObject(pancake);
    pancake->box.SetCenter(Vec2(3463,1492));

    Camera::Follow(tuki);

    GameData::playerAlive = true;
    backGroundMusic = std::make_unique<Music>("resources/music/MusicWorld.flac");
}

OverworldState::~OverworldState() {
}

void OverworldState::LoadAssets() {
    GameObject* heartBarObj = new GameObject();
    AddObject(heartBarObj);
    
    HeartBar* heartBar = new HeartBar(*heartBarObj); 
    heartBarObj->AddComponent(heartBar);
}

void OverworldState::Update(float dt) {
    InputManager& iM = InputManager::GetInstance();

    Camera::Update(dt);

    if (iM.KeyPress(ESCAPE_KEY) || iM.QuitRequested() || iM.KeyPress(P_KEY)){
        shadowObj = new GameObject();        
        Sprite* shadow = new  Sprite(*shadowObj,"resources/img/Shadow.png");
        shadow->SetAlpha(128);
        shadowObj->box.x =Player::player->GetPlayerPos().x;
        shadowObj->box.y =Player::player->GetPlayerPos().y;
        shadowObj->AddComponent(shadow);
        AddObject(shadowObj);
        
        ResumeState* newState = new ResumeState();
        Game::GetInstance().Push(newState);
    }
    if(GameData::quitOWState){
        popRequested = true; 
        GameData::quitOWState = false;
    }

    UpdateArray(dt);
    CheckCollisions();
    DeleteObjects();
}

void OverworldState::Render() {
    RenderArray();
}

void OverworldState::Start() {
    LoadAssets();
    StartArray();
    started = true;
    backGroundMusic->Play();
}

void OverworldState::Pause() {
}

void OverworldState::Resume() {
    if(shadowObj){
        RemoveObject(shadowObj);
        shadowObj = nullptr;
    }
}