#include "states/OverworldState.h"

OverworldState::OverworldState(): State() {

    // Game& game = Game::GetInstance();
    GameObject* bg = new GameObject();
    bg->AddComponent((std::shared_ptr<Sprite>)new Sprite(*bg,"resources/img/blackBG.jpg"));
    bg->AddComponent((std::shared_ptr<CameraFollower>)new CameraFollower(*bg));
    AddObject(bg);

    GameObject* map = new GameObject();
    TileSet* ts = new TileSet(*map,64,64,"resources/img/placeholder.png");
    map->AddComponent((std::shared_ptr<TileMap>)new TileMap(*map,"resources/map/placeholder.txt",ts));
    AddObject(map);

    GameObject* tuki = new GameObject();
    tuki->AddComponent((std::shared_ptr<TukiOW>)new TukiOW(*tuki));
    AddObject(tuki);

    Camera::Follow(tuki);

    GameData::playerAlive = true;
}

OverworldState::~OverworldState() {

}

void OverworldState::LoadAssets() {

}

void OverworldState::Update(float dt) {
    InputManager& iM = InputManager::GetInstance();

    Camera::Update(dt);

    if(iM.QuitRequested()) quitRequested = true;
    else if (iM.KeyPress(ESCAPE_KEY)) popRequested = true;
    
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
}

void OverworldState::Pause() {

}

void OverworldState::Resume() {

}