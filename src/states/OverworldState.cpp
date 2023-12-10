#include "CameraFollower.h"
#include "Component.h"
#include "GameData.h"
#include "HeartBar.h"
#include "Player.h"
#include "defines/DefineInput.h"
#include "enemies/Pancake.h"
#include "enemies/Pavao.h"
#include "states/OverworldState.h"
#include "states/ResumeState.h"

OverworldState::OverworldState(): State(), shadowObj() {

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

    Camera::Follow(tuki);
    
    GameObject* pancake = new GameObject();
    pancake->AddComponent(new Pancake(*pancake,100));
    AddObject(pancake);
    pancake->box.SetCenter(Vec2(3463,1492));

    GameObject* pavao = new GameObject();
    pavao->AddComponent(new Pavao(*pavao,100));
    pavao->box.SetCenter(Vec2(3427,652));
    AddObject(pavao);


    Camera::Follow(tuki);
    GameData::playerAlive = true;

    GameData::playerAlive = true;
    backGroundMusic = std::make_unique<Music>("resources/music/MusicWorld.flac");
}

OverworldState::~OverworldState() {
    backGroundMusic->Stop(0);
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

    if(iM.QuitRequested()) quitRequested = true;

    if(!GameData::playerAlive) {
        timer.Update(dt);
        if(timer.Get() > 1.0) {
            popRequested = true;
        }
    }

    if (iM.KeyPress(ESCAPE_KEY) ||  iM.KeyPress(P_KEY)){
        GameObject* go = new GameObject();        
        Sprite* shadow = new  Sprite(*go,"resources/img/Shadow.png");
        shadow->SetAlpha(128);
        go->AddComponent(shadow);
        go->AddComponent(new CameraFollower(*go));
        shadowObj = AddObject(go);
        
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
    auto ptr = shadowObj.lock();

    if(ptr) ptr->RequestDelete();
}