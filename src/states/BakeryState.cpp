#include "states/BakeryState.h"
#include "Game.h"
#include "TukiB.h"

BakeryState::BakeryState() : State() {
    floor = 0;

    GameObject* bedroom = new GameObject();
    bedroom->AddComponent((std::shared_ptr<Sprite>) new Sprite(*bedroom, "resources/img/bedroom_ph.png"));
    bedroom->box.SetCenter({Game::GetInstance().GetWindowWidth() * 0.5F,Game::GetInstance().GetWindowHeight() * 0.5F});
    AddObject(bedroom);

    GameObject* tuki = new GameObject();
    tuki->AddComponent((std::shared_ptr<TukiB>)new TukiB(*tuki));
    tuki->box.SetCenter({500,525});
    AddObject(tuki);

    Camera::Follow(tuki);

    GameData::playerAlive = true;
    backGraundMusic = new Music("resources/music/MusicWorld.flac");
}

BakeryState::~BakeryState() {
    objectArray.clear();
}

void BakeryState::LoadAssets() {
    // Load assets
}

void BakeryState::Update(float dt) {
    InputManager& input = InputManager::GetInstance();

    if (input.KeyPress(ESCAPE_KEY) || input.QuitRequested()) {
        quitRequested = true;
    }

    if (((TukiB*)Player::player)->GetFloor() != floor) {
        floor = ((TukiB*)Player::player)->GetFloor();
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
    backGraundMusic->Play();
}

void BakeryState::Pause() {
    backGraundMusic->Stop();
}

void BakeryState::Resume() {
    backGraundMusic->Play();
}