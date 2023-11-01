#include <OverworldState.h>

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
}

OverworldState::~OverworldState() {

}

void OverworldState::LoadAssets() {

}

void OverworldState::Update(float dt) {
    InputManager& iM = InputManager::GetInstance();

    Camera::Update(dt);

    if(iM.KeyPress(ESCAPE_KEY) || iM.QuitRequested()) quitRequested = true;

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