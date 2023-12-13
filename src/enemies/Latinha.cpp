#include "enemies/Latinha.h"
#include "GameObject.h"
#include "Game.h"

Latinha::Latinha(GameObject& assoc, int hp): Enemy(assoc,false,hp) {
    Sprite* sprite = new Sprite(assoc, "resources/img/enemies/latinha_idle.png");
    sprite->SetScale(2,2);
    assoc.AddComponent(sprite);
}

Latinha::~Latinha() {

}

bool Latinha::Is(std::string type) {
    return type == "Latinha" || Enemy::Is(type);
}

void Latinha::CalcSpeed(float dt) {
    speed += LATINHA_A*dt;
    if(speed > LATINHA_SPEED_LIM) speed = LATINHA_SPEED_LIM;
}

void Latinha::SetState(EnemyState state) {
    Enemy::SetState(state);

    switch (state) {
        case MOVING:
            moveTarget = associated.box.GetCenter() + Vec2(rand()%601 - 300,rand()%601 - 300);
            moveAngle = moveTarget.inclVec2(associated.box.GetCenter());
            ChangeSprite("resources/img/enemies/latinha_anim(200).png",6,.2F);
            break;
        case IDLE:
            idleTime = rand()%5001*0.001F + 2;
            speed = 0;
            ChangeSprite("resources/img/enemies/latinha_idle.png");
            break;
        case DAMAGED:
            speed = 0;
            SetCollider(COLOR_BLUE, false);
            break;
        default:
            break;
    }
}

void Latinha::DeathAnimation() {
    GameObject* go = new GameObject();
    Sprite* sprite = new Sprite(*go, "resources/img/enemies/latinha_anim_morRENDO.png",8,.2F,1.6F);
    sprite->SetScale(2,2);
    go->AddComponent(sprite);
    go->box = associated.box;
    Game::GetInstance().GetCurrentState().AddObject(go);
}

void Latinha::DropItems() {

}