#include "states/BakeryState.h"
#include "GameObject.h"

BakeryState::BakeryState() : State() {
    GameObject* tuki = new GameObject();
    TukiB* tukiB = new TukiB(*tuki);

    GameObject* dad = new GameObject();
    dad->AddComponent(new NPC(*dad, "resources/img/dad.png"));
    dad->box.SetCenter({520,280});


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

    tukiB->SetFloor(floor);
    tuki->AddComponent(tukiB);
    tuki->box.SetCenter({810,260});
    AddObject(tuki);
    // Camera::Follow(tuki);

    AddObject(dad);

    GameObject* speakBalloon = new GameObject();
    Sprite* sprite = new Sprite(*speakBalloon, "resources/img/MenuButton.png");
    speakBalloon->AddComponent(sprite);
    sprite->SetScale(3.0f, 2.5f);
    speakBalloon->box.x = 320;
    speakBalloon->box.y = 570;

    // AddObject(speakBalloon);

    GameData::intro = false;


    GameData::playerAlive = true;

}

BakeryState::~BakeryState() {
    objectArray.clear();
    GameData::backGroundMusic->Stop(0);
}

void BakeryState::LoadAssets() {
    // Load assets
}

void BakeryState::Update(float dt) {
    InputManager& iM = InputManager::GetInstance();

    if(iM.QuitRequested()) quitRequested = true;

    if (iM.KeyPress(ESCAPE_KEY) || iM.KeyPress(P_KEY))
        LoadNewState(new ResumeState());
    else if (iM.KeyPress(I_KEY))
        LoadNewState(new InventoryState());

    if(GameData::quitOWState){
        popRequested = true; 
        GameData::quitOWState = false;
    }

    // changes floor if Tuki goes down/up stairs
    int newFloor = ((TukiB*)Player::player)->GetFloor();

    if (newFloor != floor) 
        ChangeFloor(newFloor);
    

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
    GameData::backGroundMusic = std::make_unique<Music>("resources/music/OWGame.flac");
    GameData::backGroundMusic->Play();
}

void BakeryState::Pause() {
    GameData::backGroundMusic->Pause();
}

void BakeryState::Resume() {
    auto ptr = shadowObj.lock();
    if(ptr) RemoveObject(ptr.get());

    GameData::backGroundMusic->Resume();

    if(floor == 2) {
        auto tuki = std::static_pointer_cast<TukiB>(objectArray[2]->GetComponent("TukiB").lock());
        Player::player = tuki.get();
        tuki->SetFloor(1);
        tuki->ResetSpeed();
        ChangeFloor(1);
        Camera::pos = 0;
    }
}

void BakeryState::ChangeFloor(int newFloor) {
        floor = newFloor;
        if (floor == 2) {
            OverworldState* overworld = new OverworldState();
            Game::GetInstance().Push(overworld);
        } else { 

        // gets rid of npcs from floor
        for (int i = 0; i < (int)objectArray.size(); i++)
            if (objectArray[i]->GetComponent("NPC").lock())
                objectArray[i]->RequestDelete();

        // objectArray[1]->RemoveComponent(objectArray[1]->GetComponent("Sprite").lock().get());
        auto sprite = std::static_pointer_cast<Sprite>(objectArray[1]->GetComponent("Sprite").lock());
        if (floor == 0){
            sprite->Open("resources/img/bedroom/bedroom.png");

            GameObject* dad = new GameObject();
            dad->AddComponent(new NPC(*dad, "resources/img/dad.png"));
            dad->box.SetCenter({520,280});
            AddObject(dad);
        }
        else if (floor == 1){
            sprite->Open("resources/img/bakery_test.png");
        }
        objectArray[1]->box.SetCenter({Game::GetInstance().GetWindowWidth() * 0.5F,Game::GetInstance().GetWindowHeight() * 0.5F});
    }
}