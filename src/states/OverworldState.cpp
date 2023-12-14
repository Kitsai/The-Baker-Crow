#include "HeartBar.h"

#include "Player.h"
#include "enemies/enemies.h"

#include "Tree.h"
#include "House.h"
#include "Bush.h"
#include "Wall.h"

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

    GameObject* wall = new GameObject();
    wall->AddComponent(new Wall(*wall));
    wall->box.x = 2286;
    wall->box.y = 0;
    AddObject(wall);
    
    LoadHouses();

    GameObject* tuki = new GameObject();
    TukiOW* tukiC = new TukiOW(*tuki);
    tuki->AddComponent(tukiC);
    AddObject(tuki);
    tuki->box.SetCenter(Vec2(817,2316));

    Player::player = tukiC;
    Camera::Follow(tuki);
    GameData::playerAlive = true;

    
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
    penguin->AddComponent(new Penguin(*penguin,50));
    penguin->box.SetCenter(Vec2(4797,884));
    AddObject(penguin);


    LoadObstacles();
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

        if(iM.KeyPress(SPACE_KEY)
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

void OverworldState::LoadHouses() {
    GameObject* bakery = new GameObject();
    bakery->AddComponent(new House(*bakery,"resources/img/overworld/confeitaria.png"));
    bakery->box.x = 440;
    bakery->box.y = 1816;
    AddObject(bakery);

    GameObject* house1 = new GameObject();
    house1 -> AddComponent(new House(*house1,"resources/img/overworld/casa_azul.png"));
    house1 -> box.x = 384;
    house1 -> box.y = 68;
    AddObject(house1);

    GameObject* house2 = new GameObject();
    house2 -> AddComponent(new House(*house2,"resources/img/overworld/casa_verde.png"));
    house2 -> box.x = 416;
    house2 -> box.y = 724;
    AddObject(house2);

    GameObject* house3 = new GameObject();
    house3 -> AddComponent(new House(*house3,"resources/img/overworld/casa_laranja.png"));
    house3 -> box.x = 1108;
    house3 -> box.y = 56;
    AddObject(house3);

    GameObject* house4 = new GameObject();
    house4 -> AddComponent(new House(*house4,"resources/img/overworld/casa_azul.png"));
    house4 -> box.x = 1612;
    house4 -> box.y = 716;
    AddObject(house4);
}

void OverworldState::LoadObstacles() {

    GameObject* bush1 = new GameObject();
    bush1->AddComponent(new Bush(*bush1));
    bush1->box.x = -48;
    bush1->box.y = 1816;
    AddObject(bush1);

    GameObject* bush2 = new GameObject();
    bush2->AddComponent(new Bush(*bush2));
    bush2->box.x = 24;
    bush2->box.y = 1768;
    AddObject(bush2);

    GameObject* bush3 = new GameObject();
    bush3->AddComponent(new Bush(*bush3));
    bush3->box.x = -36;
    bush3->box.y = 1732;
    AddObject(bush3);

    GameObject* bush4 = new GameObject();
    bush4->AddComponent(new Bush(*bush4));
    bush4->box.x = 40;
    bush4->box.y = 1688;
    AddObject(bush4);

    GameObject* bush5 = new GameObject();
    bush5->AddComponent(new Bush(*bush5));
    bush5->box.x = -32;
    bush5->box.y = 1652;
    AddObject(bush5);

    GameObject* bush6 = new GameObject();
    bush6->AddComponent(new Bush(*bush6));
    bush6->box.x = 52;
    bush6->box.y = 1596;
    AddObject(bush6);

    GameObject* bush7 = new GameObject();
    bush7->AddComponent(new Bush(*bush7));
    bush7->box.x = -44;
    bush7->box.y = 1576;
    AddObject(bush7);

    GameObject* bush8 = new GameObject();
    bush8->AddComponent(new Bush(*bush8));
    bush8->box.x = 16;
    bush8->box.y = 1524;
    AddObject(bush8);

    GameObject* bush9 = new GameObject();
    bush9->AddComponent(new Bush(*bush9));
    bush9->box.x = -40;
    bush9->box.y = 1492;
    AddObject(bush9);

    GameObject* bush10 = new GameObject();
    bush10->AddComponent(new Bush(*bush10));
    bush10->box.x = -28;
    bush10->box.y = 684;
    AddObject(bush10);

    GameObject* bush11 = new GameObject();
    bush11->AddComponent(new Bush(*bush11));
    bush11->box.x = 20;
    bush11->box.y = 756;
    AddObject(bush11);

    GameObject* bush12 = new GameObject();
    bush12->AddComponent(new Bush(*bush12));
    bush12->box.x = -52;
    bush12->box.y = 780;
    AddObject(bush12);

    GameObject* bush13 = new GameObject();
    bush13->AddComponent(new Bush(*bush13));
    bush13->box.x = 12;
    bush13->box.y = 844;
    AddObject(bush13);

    GameObject* bush14 = new GameObject();
    bush14->AddComponent(new Bush(*bush14));
    bush14->box.x = -48;
    bush14->box.y = 880;
    AddObject(bush14);

    GameObject* bush15 = new GameObject();
    bush15->AddComponent(new Bush(*bush15));
    bush15->box.x = -24;
    bush15->box.y = -16;
    AddObject(bush15);

    GameObject* bush16 = new GameObject();
    bush16->AddComponent(new Bush(*bush16));
    bush16->box.x = -52;
    bush16->box.y = 60;
    AddObject(bush16);

    GameObject* bush17 = new GameObject();
    bush17->AddComponent(new Bush(*bush17));
    bush17->box.x = -44;
    bush17->box.y = 136;
    AddObject(bush17);

    GameObject* bush18 = new GameObject();
    bush18->AddComponent(new Bush(*bush18));
    bush18->box.x = 40;
    bush18->box.y = 40;
    AddObject(bush18);

    GameObject* tree1 = new GameObject();
    tree1->AddComponent(new Tree(*tree1));
    tree1->box.x = 2816;
    tree1->box.y = 556;
    AddObject(tree1);

    GameObject* tree2 = new GameObject();
    tree2->AddComponent(new Tree(*tree2));
    tree2->box.x = 3664;
    tree2->box.y = 612;
    AddObject(tree2);

    GameObject* tree3 = new GameObject();
    tree3->AddComponent(new Tree(*tree3));
    tree3->box.x = 3948;
    tree3->box.y = 600;
    AddObject(tree3);

    GameObject* tree4 = new GameObject();
    tree4->AddComponent(new Tree(*tree4));
    tree4->box.x = 3796;
    tree4->box.y = 676;
    AddObject(tree4);

    GameObject* tree5 = new GameObject();
    tree5->AddComponent(new Tree(*tree5));
    tree5->box.x = 3656;
    tree5->box.y = 776;
    AddObject(tree5);

    GameObject* tree6 = new GameObject();
    tree6->AddComponent(new Tree(*tree6));
    tree6->box.x = 3920;
    tree6->box.y = 816;
    AddObject(tree6);

    GameObject* tree7 = new GameObject();
    tree7->AddComponent(new Tree(*tree7));
    tree7->box.x = 3808;
    tree7->box.y = 872;
    AddObject(tree7);

    GameObject* tree8 = new GameObject();
    tree8->AddComponent(new Tree(*tree8));
    tree8->box.x = 4364;
    tree8->box.y = 1304;
    AddObject(tree8);

    GameObject* tree9 = new GameObject();
    tree9->AddComponent(new Tree(*tree9));
    tree9->box.x = 2508;
    tree9->box.y = 1004;
    AddObject(tree9);

    GameObject* tree10 = new GameObject();
    tree10->AddComponent(new Tree(*tree10));
    tree10->box.x = 2352;
    tree10->box.y = 1100;
    AddObject(tree10);

    GameObject* tree11 = new GameObject();
    tree11->AddComponent(new Tree(*tree11));
    tree11->box.x = 2676;
    tree11->box.y = 1124;
    AddObject(tree11);

    GameObject* tree12 = new GameObject();
    tree12->AddComponent(new Tree(*tree12));
    tree12->box.x = 2544;
    tree12->box.y = 1184;
    AddObject(tree12);

    GameObject* tree13 = new GameObject();
    tree13->AddComponent(new Tree(*tree13));
    tree13->box.x = 2716;
    tree13->box.y = 1244;
    AddObject(tree13);

    GameObject* tree14 = new GameObject();
    tree14->AddComponent(new Tree(*tree14));
    tree14->box.x = 2292;
    tree14->box.y = 1212;
    AddObject(tree14);

    GameObject* tree15 = new GameObject();
    tree15->AddComponent(new Tree(*tree15));
    tree15->box.x = 2484;
    tree15->box.y = 1308;
    AddObject(tree15);

    GameObject* tree16 = new GameObject();
    tree16->AddComponent(new Tree(*tree16));
    tree16->box.x = 2660;
    tree16->box.y = 1344;
    AddObject(tree16);

    GameObject* tree17 = new GameObject();
    tree17->AddComponent(new Tree(*tree17));
    tree17->box.x = 2316;
    tree17->box.y = 1408;
    AddObject(tree17);

    GameObject* tree18 = new GameObject();
    tree18->AddComponent(new Tree(*tree18));
    tree18->box.x = 2176;
    tree18->box.y = 1384;
    AddObject(tree18);

    GameObject* tree19 = new GameObject();
    tree19->AddComponent(new Tree(*tree19));
    tree19->box.x = 2496;
    tree19->box.y = 1500;
    AddObject(tree19);

    GameObject* tree20 = new GameObject();
    tree20->AddComponent(new Tree(*tree20));
    tree20->box.x = 2300;
    tree20->box.y = 1540;
    AddObject(tree20);

    GameObject* tree21 = new GameObject();
    tree21->AddComponent(new Tree(*tree21));
    tree21->box.x = 3540;
    tree21->box.y = 4;
    AddObject(tree21);

    GameObject* tree22 = new GameObject();
    tree22->AddComponent(new Tree(*tree22));
    tree22->box.x = 3204;
    tree22->box.y = -4;
    AddObject(tree22);

    GameObject* tree23 = new GameObject();
    tree23->AddComponent(new Tree(*tree23));
    tree23->box.x = 3388;
    tree23->box.y = 12;
    AddObject(tree23);

    GameObject* tree24 = new GameObject();
    tree24->AddComponent(new Tree(*tree24));
    tree24->box.x = 3668;
    tree24->box.y = 32;
    AddObject(tree24);

    GameObject* tree25 = new GameObject();
    tree25->AddComponent(new Tree(*tree25));
    tree25->box.x = 3888;
    tree25->box.y = 16;
    AddObject(tree25);

    GameObject* tree26 = new GameObject();
    tree26->AddComponent(new Tree(*tree26));
    tree26->box.x = 4188;
    tree26->box.y = -20;
    AddObject(tree26);

    GameObject* tree27 = new GameObject();
    tree27->AddComponent(new Tree(*tree27));
    tree27->box.x = 4052;
    tree27->box.y = 48;
    AddObject(tree27);
}