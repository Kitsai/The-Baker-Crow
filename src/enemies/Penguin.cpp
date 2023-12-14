#include "enemies/Penguin.h"
#include "GameObject.h"
#include "Game.h"

Penguin::Penguin(GameObject& assoc, int hp): Enemy(assoc,false,hp) {
    Sprite* sprite = new Sprite(assoc, "resources/img/enemies/penguim_idle.png");
    sprite->SetScale(2,2);
    assoc.AddComponent(sprite);

    auto collider = std::static_pointer_cast<Collider>(associated.GetComponent("Collider").lock());
    if(collider) collider->SetScale({0.5,0.5});
}

Penguin::~Penguin() {

}

bool Penguin::Is(std::string type) {
    return type == "Penguin" || Enemy::Is(type);
}

void Penguin::CalcSpeed(float dt) {
    speed += PENGUIN_A*dt;
    if(speed > PENGUIN_SPEED_LIM) speed = PENGUIN_SPEED_LIM;
}

void Penguin::SetState(EnemyState state) {
    Enemy::SetState(state);

    switch (state) {
        case MOVING:
            moveTarget = associated.box.GetCenter() + Vec2(rand()%601 - 300,rand()%601 - 300);
            CheckBorders();
            moveAngle = moveTarget.inclVec2(associated.box.GetCenter());
            ChangeSprite("resources/img/enemies/penguim_anim(200).png",5,.2F);
            break;
        case IDLE:
            idleTime = rand()%5001*0.001F + 2;
            speed = 0;
            ChangeSprite("resources/img/enemies/penguim_idle.png");
            break;
        case DAMAGED:
            speed = 0;
            SetCollider(COLOR_BLUE, false);
            break;
        default:
            break;
    }
}

void Penguin::DeathAnimation() {
    GameObject* go = new GameObject();
    Sprite* sprite = new Sprite(*go, "resources/img/enemies/pegum_anim_morRENDO.png",8,.2F,1.6F);
    sprite->SetScale(2,2);
    go->AddComponent(sprite);
    go->box = associated.box;
    Game::GetInstance().GetCurrentState().AddObject(go);
}

void Penguin::DropItems() {
    DropItem(acucar);
}