#include <OverworldState.h>

OverworldState::OverworldState(): State() {

    Game& game = Game::GetInstance();

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
    if(iM.KeyPress(ESCAPE_KEY) || iM.QuitRequested()) quitRequested = true;

    UpdateArray(dt);
}

void OverworldState::Render() {
    RenderArray();
}

void OverworldState::Start() {
    StartArray();
}

void OverworldState::Pause() {

}

void OverworldState::Resume() {

}