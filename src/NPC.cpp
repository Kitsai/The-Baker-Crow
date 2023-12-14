#include "NPC.h"
#include <iostream>

NPC::NPC(GameObject& associated, std::string file, int type) : Component(associated) {
    this->type = type;
    this->file = file;
    if (type == 0){
        Sprite* sprite = new Sprite(associated, file);
        sprite->SetScale(2.0f, 2.0f);
        associated.AddComponent(sprite);
    }
    if (type == 1 && GameData::hasNPC){
        Sprite* sprite = new Sprite(associated, file);
        sprite->SetScale(2.0f, 2.0f);
        associated.AddComponent(sprite);
        associated.box.SetCenter({540, 400});
    }
    state = IDLE; // standing
}

NPC::~NPC() {}

void NPC::Update(float dt) {
    if (state == MOVING) Move(dt);
    if (associated.box.GetCenter() == Vec2(540, 400)) {
        InputManager& iM = InputManager::GetInstance();
        if (iM.KeyPress(Z_KEY)) {
            Request();
            WalkOut();
        }
    }
    if (associated.box.GetCenter() == Vec2(615, 700)) {
        GameData::hasNPC = false;
        associated.RequestDelete();
    }
}

void NPC::Render() {}

bool NPC::Is(std::string type) {
    return (type == "NPC");
}

void NPC::WalkIn() {
    if (type == 1) {
        associated.box.SetCenter({540, 600});
        GameData::hasNPC = true;

        Sprite* sprite = new Sprite(associated, file);
        sprite->SetScale(2.0f, 2.0f);
        associated.AddComponent(sprite);

        moveTarget = {540, 400};
        SetState(MOVING);
    }
}

void NPC::WalkOut() {
    if (type == 1) {
        moveTarget = {615, 700};
        SetState(MOVING);
        
    }
}

void NPC::SetState(NPCState state) {
    this->state = state;

    switch (state) {
        case MOVING:
            moveAngle = moveTarget.inclVec2(associated.box.GetCenter());
            //ChangeSprite("resources/img/enemies/pancake_anim(200).png",8,.15F);
            break;
        case IDLE:
            speed = 0;
            //ChangeSprite("resources/img/enemies/pancake_idle.png");
            break;
        default:
            break;
    }
}

void NPC::CalcSpeed(float dt) {
    speed += TOW_A*dt;
    if(speed > TOW_SPEED_LIM) speed = TOW_SPEED_LIM;
}

void NPC::ChangeSprite(std::string file, int frameCount, float frameTime) {
    Vec2 center = associated.box.GetCenter();
    std::shared_ptr<Sprite> sprite = std::static_pointer_cast<Sprite>(associated.GetComponent("Sprite").lock());
    if (sprite != nullptr) {
        sprite->Open(file);
        sprite->SetFrameCount(frameCount);
        sprite->SetFrameTime(frameTime);
        associated.box.SetCenter(center);
    }

    if(moveTarget.x > center.x) sprite->SetFlip(SDL_FLIP_HORIZONTAL);
    else if(moveTarget.x < center.x) sprite->SetFlip(SDL_FLIP_NONE);
}

void NPC::Move(float dt) {
    if (moveTarget.distVec2(associated.box.GetCenter()) < 5) {
        associated.box.SetCenter(moveTarget);
        SetState(IDLE);
    } else {
        CalcSpeed(dt);
        speed = speed*DAMP_MOVING;
        associated.box.SetCenter(associated.box.GetCenter() + Vec2(cos(moveAngle),sin(moveAngle))*dt*speed);
        CalcSpeed(dt);
    }
}

void NPC::Request() {
    int size = GameData::recipes.size();
    int choice = 1;
    int oldItems = 0;

    if (size < 5) choice = rand() % 2; // chooses wheter it will be a new item or an old one
    if (size == 0) choice = 0;  // has to be a new item if there hasn't been any old ones
    if (size > 0) oldItems = rand() % GameData::recipes.size(); // chooses one between the old items

    if (choice == 0) {
        switch(size){
            case 0:
                GameData::requests.emplace_back("brigadeiro");
                GameData::recipes.emplace_back("brigadeiro");
                break;
            case 1:
                GameData::requests.emplace_back("pudding");
                GameData::recipes.emplace_back("pudding");
                break;
            case 2:
                GameData::requests.emplace_back("cake");
                GameData::recipes.emplace_back("cake");
                break;
            case 3:
                GameData::requests.emplace_back("macarons");
                GameData::recipes.emplace_back("macarons");
                break;
            case 4:
                GameData::requests.emplace_back("cheesebread");
                GameData::recipes.emplace_back("cheesebread");
                break;
        }
    } else if (size > 0) GameData::requests.emplace_back(GameData::recipes[oldItems]);
}
