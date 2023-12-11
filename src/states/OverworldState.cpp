#include "HeartBar.h"

#include "enemies/Pavao.h"
#include "enemies/Pancake.h"

#include "states/ResumeState.h"
#include "states/InventoryState.h"
#include "states/OverworldState.h"

OverworldState::OverworldState(): State(){

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

    backGroundMusic = std::make_unique<Music>("resources/music/OWGame.flac");
}

OverworldState::~OverworldState() {
}

void OverworldState::Update(float dt) {
    InputManager& iM = InputManager::GetInstance();
    
    if(GameData::quitOWState){
        popRequested = true; 
        GameData::quitOWState = false;
    }
    
    if(!GameData::playerAlive) {
        timer.Update(dt);
        if(timer.Get() > 1.0) {
            popRequested = true;
        }
    }else{
        Camera::Update(dt);
        
        if (iM.KeyPress(ESCAPE_KEY) || iM.QuitRequested() || iM.KeyPress(P_KEY)){
            LoadNewState(new ResumeState());
        }
        
        else if (iM.KeyPress(I_KEY)){
            LoadNewState(new InventoryState());
        }
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

void OverworldState::LoadAssets() {

    GameObject* heartBarObj = new GameObject();
    AddObject(heartBarObj);
    
    HeartBar* heartBar = new HeartBar(*heartBarObj); 
    heartBarObj->AddComponent(heartBar);
    
}