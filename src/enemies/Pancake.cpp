#include "enemies/Pancake.h"

#include "Button.h"
#include "Game.h"
#include "defines/DefineColor.h"
#include "items.h"

Pancake::Pancake(GameObject& assoc, int hp): Enemy(assoc, false, hp) {
    Sprite* sprite = new Sprite(assoc, "resources/img/enemies/pancake_idle.png");
    sprite->SetScale(2,2);
    assoc.AddComponent(sprite);

    auto collider = std::static_pointer_cast<Collider>(associated.GetComponent("Collider").lock());
    if(collider) collider->SetScale({0.8,0.8});
}

Pancake::~Pancake() {

}

bool Pancake::Is(std::string type) {
    return type == "Pancake" || Enemy::Is(type);
}


void Pancake::CalcSpeed(float dt) {
    speed += PANCAKE_A*dt;
    if(speed > PANCAKE_SPEED_LIM) speed = PANCAKE_SPEED_LIM;
}

void Pancake::SetState(EnemyState state) {
    Enemy::SetState(state);

    switch (state) {
        case MOVING:
            moveTarget = associated.box.GetCenter() + Vec2(rand()%601 - 300,rand()%601 - 300);
            CheckBorders();
            moveAngle = moveTarget.inclVec2(associated.box.GetCenter());
            ChangeSprite("resources/img/enemies/pancake_anim(200).png",8,.15F);
            break;
        case IDLE:
            idleTime = rand()%5001*0.001F + 2;
            speed = 0;
            ChangeSprite("resources/img/enemies/pancake_idle.png");
            break;
        case DAMAGED:
            speed = 0;
            SetCollider(COLOR_BLUE, false);
            timer.Restart();
            break;
        default:
            break;
    }
}

void Pancake::DeathAnimation() {
    GameObject* go = new GameObject();
    Sprite* sprite = new Sprite(*go, "resources/img/enemies/pancake_anim_morRENDO.png",8,.15F,1.2F);
    sprite->SetScale(2,2);
    go->AddComponent(sprite);
    go->box = associated.box;
    Game::GetInstance().GetCurrentState().AddObject(go);
}

void Pancake::DropItems() {
    int chance = 50;
    if(GameData::hasItem[butter].first) chance -= 30;
    if(GameData::hasItem[honey].first) chance += 30;

    if(rand()%100 < chance)
        DropItem(butter);
    else
        DropItem(honey);
}