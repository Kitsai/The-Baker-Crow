#include "states/OverworldState.h"

OverworldState::OverworldState(): State() {

    // Game& game = Game::GetInstance();
    GameObject* bg = new GameObject();
    bg->AddComponent(new Sprite(*bg,"resources/img/blackBG.jpg"));
    bg->AddComponent(new CameraFollower(*bg));
    AddObject(bg);

    GameObject* map = new GameObject();
    TileSet* ts = new TileSet(*map,64,64,"resources/img/placeholder.png");
    map->AddComponent(new TileMap(*map,"resources/map/placeholder.txt",ts));
    AddObject(map);

    GameObject* tuki = new GameObject();
    tuki->AddComponent(new TukiOW(*tuki));
    AddObject(tuki);

    Camera::Follow(tuki);

    GameData::playerAlive = true;
    backGroundMusic =  std::make_unique<Music>("resources/music/MusicWorld.flac");
}

OverworldState::~OverworldState() {

}

void OverworldState::LoadAssets() {

}

void OverworldState::Update(float dt) {
    InputManager& iM = InputManager::GetInstance();

    Camera::Update(dt);

    if(iM.QuitRequested()){
        quitRequested = true;
    } 
    else if (iM.KeyPress(ESCAPE_KEY)){
        popRequested = true;
        backGroundMusic->Stop(50);

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
    Camera::pos.x = 0;
    Camera::pos.y = 0;
    backGroundMusic->Play();
}