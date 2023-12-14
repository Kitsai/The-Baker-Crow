#include "states/BakeryState.h"
#include "states/CutsceneState.h"
#include <cstdlib>

BakeryState::BakeryState() : State() {
    GameObject* tuki = new GameObject();
    TukiB* tukiB = new TukiB(*tuki);

    GameObject* dad = new GameObject();
    dad->AddComponent(new NPC(*dad, "resources/img/npc/dad.png"));
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

    GameData::playerAlive = true;
}

BakeryState::~BakeryState() {
    objectArray.clear();
    backGroundMusic->Stop(0);
}

void BakeryState::LoadAssets() {
    // Load assets
}

void BakeryState::Update(float dt) {
    InputManager& iM = InputManager::GetInstance();

    // changes floor if Tuki goes down/up stairs
    int newFloor = ((TukiB*)Player::player)->GetFloor();

    if (newFloor != floor) 
        ChangeFloor(newFloor);

    // manages entrance/outings of clients
    if (floor == 1) {
        clientTimer.Update(dt);
        ManageClients();
    }

    if(iM.QuitRequested()) quitRequested = true;

    if (GameData::intro || (GameData::completed && floor == 0)) 
        LoadNewState(new CutsceneState());

    if (iM.KeyPress(ESCAPE_KEY) || iM.KeyPress(P_KEY))
        LoadNewState(new ResumeState());
    else if (iM.KeyPress(I_KEY))
        LoadNewState(new InventoryState());

    if(GameData::quitOWState){
        popRequested = true; 
        GameData::quitOWState = false;
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
    GameData::backGroundMusic = std::make_unique<Music>("resources/music/OWGame.flac");
    GameData::backGroundMusic->Play();
}

void BakeryState::Pause() {
    backGroundMusic->Pause();
}

void BakeryState::Resume() {
    auto ptr = shadowObj.lock();
    if(ptr) RemoveObject(ptr.get());

    backGroundMusic->Resume();

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
            backGroundMusic->Stop(0);
        } else { 
        // gets rid of npcs from floor
        for (int i = 0; i < (int)objectArray.size(); i++)
            if (objectArray[i]->GetComponent("NPC").lock())
                objectArray[i]->RequestDelete();

        auto sprite = std::static_pointer_cast<Sprite>(objectArray[1]->GetComponent("Sprite").lock());
        if (floor == 0){
            sprite->Open("resources/img/bedroom/bedroom.png");

            GameObject* dad = new GameObject();
            dad->AddComponent(new NPC(*dad, "resources/img/npc/dad.png"));
            dad->box.SetCenter({520,280});
            AddObject(dad);
        }
        else if (floor == 1){
            sprite->Open("resources/img/bakery_test.png");

            if (GameData::hasNPC) {
                GameObject* npc = new GameObject();
                std::string file = "resources/img/npc/Keru.png";
                if (GameData::clients.size() > 0) file = GameData::clients[GameData::clients.size()-1]; // if there is NPC in the room, it is the last one in the vector
                npc->AddComponent(new NPC(*npc, file, 1));
                AddObject(npc);
            }
            
        }
        objectArray[1]->box.SetCenter({Game::GetInstance().GetWindowWidth() * 0.5F,Game::GetInstance().GetWindowHeight() * 0.5F});
    }
}

void BakeryState::ManageClients(){
    bool regulations = false;
    // doesn't spawn clients if there are more than 5 requests
    // if (GameData::requests.size() < 5 && (GameData::recipes.size() != 1 || GameData::requests.size() != 1)) regulations = true;
    if (GameData::requests.size() < 5) regulations = true;
    if ((GameData::recipes.size() == 0 || (clientTimer.Get() > 8 && regulations)) && GameData::hasNPC == false) {
        clientTimer.Restart();

        GameObject* client = new GameObject();

        int chosen = rand() % 9;
        std::string file = "resources/img/npc/Keru.png";
        switch (chosen) {
            case 0:
                file = "resources/img/npc/Keru.png";
                break;
            case 1:
                file = "resources/img/npc/Gary.png";
                break;
            case 2:
                file = "resources/img/npc/Lili.png";
                break;
            case 3:
                file = "resources/img/npc/Lysis.png";
                break;
            case 4:
                file = "resources/img/npc/Niki.png";
                break;
            case 5:
                file = "resources/img/npc/Osha.png";
                break;
            case 6:
                file = "resources/img/npc/River.png";
                break;
            case 7:
                file = "resources/img/npc/Saxon.png";
                break;
            case 8:
                file = "resources/img/npc/Stul.png";
                break;
            default:
                break;
        }

        NPC* npc = new NPC(*client, file, 1);
        client->AddComponent(npc);
        AddObject(client);

        npc->WalkIn();
        GameData::clients.emplace_back(file);
        // if (GameData::requests.size() < 2) nextTime = (rand()%7001)*0.001F;
        // else nextTime = rand() % 6 + 6;
    }
}