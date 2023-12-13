#include "HeartBar.h"

#include "Player.h"
#include "enemies/enemies.h"


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
    TukiOW* tukiC = new TukiOW(*tuki);
    tuki->AddComponent(tukiC);
    AddObject(tuki);
    tuki->box.SetCenter(Vec2(817,2316));


    Player::player = tukiC;
    Camera::Follow(tuki);
    
    GameObject* pancake = new GameObject();
    pancake->AddComponent(new Pancake(*pancake,100));
    AddObject(pancake);
    pancake->box.SetCenter(Vec2(3463,1492));

    GameObject* pavao = new GameObject();
    pavao->AddComponent(new Pavao(*pavao,150));
    pavao->box.SetCenter(Vec2(3427,652));
    AddObject(pavao);

    GameObject* crab = new GameObject();
    crab->AddComponent(new Crab(*crab,100));
    crab->box.SetCenter(Vec2(3752,2436));
    AddObject(crab);

    GameObject* latinha = new GameObject();
    latinha->AddComponent(new Latinha(*latinha,150));
    latinha->box.SetCenter(Vec2(4540,1838));
    AddObject(latinha);

    GameObject* penguin = new GameObject();
    penguin->AddComponent(new Penguin(*penguin,150));
    penguin->box.SetCenter(Vec2(4797,884));
    AddObject(penguin);

    Camera::Follow(tuki);
    GameData::playerAlive = true;

    //GameData::backGroundMusic = std::make_unique<Music>("resources/music/OWGame.flac");
}

OverworldState::~OverworldState() {
    Camera::Unfollow();
}

void OverworldState::Update(float dt) {
    InputManager& iM = InputManager::GetInstance();
    
    if(GameData::quitOWState)
        popRequested = true; 
    
    if(!GameData::playerAlive) {
        timer.Update(dt);
        if(timer.Get() > 1.0) {
            popRequested = true;
        }
    }else{
        Vec2 playerPos = Player::player->GetPlayerBoxPos();

        if(iM.KeyPress(ENTER_KEY)
            && playerPos.y >= 2145 && playerPos.y <= 2228
            && playerPos.x >= 698 && playerPos.x <= 796
        ) popRequested = true;

        Camera::Update(dt);

        if(iM.QuitRequested()) quitRequested = true;
        
        if (iM.KeyPress(ESCAPE_KEY) || iM.KeyPress(P_KEY)){
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
    GameData::backGroundMusic->Resume();
}

void OverworldState::Pause() {
    GameData::backGroundMusic->Pause();
}

void OverworldState::Resume() {
    auto ptr = shadowObj.lock();
    if(ptr) RemoveObject(ptr.get());

    GameData::backGroundMusic->Resume();
}

void OverworldState::LoadAssets() {

    GameObject* heartBarObj = new GameObject();
    AddObject(heartBarObj);
    
    HeartBar* heartBar = new HeartBar(*heartBarObj); 
    heartBarObj->AddComponent(heartBar);
    
}