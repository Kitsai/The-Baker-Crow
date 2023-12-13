#include "enemies/Pavao.h"
#include "GameObject.h"
#include "Game.h"

Pavao::Pavao(GameObject& assoc, int hp): Enemy(assoc,true,hp) {
    Sprite* sprite = new Sprite(assoc, "resources/img/enemies/pavao_idle.png");
    sprite->SetScale(2,2);
    assoc.AddComponent(sprite);

    auto collider = std::static_pointer_cast<Collider>(associated.GetComponent("Collider").lock());
    if(collider) collider->SetScale({0.8,0.8});
}

Pavao::~Pavao() {

}

bool Pavao::Is(std::string type) {
    return type == "Pavao" || Enemy::Is(type);
}

void Pavao::CalcSpeed(float dt) {
    speed += PAVAO_A*dt;
    if(speed > PAVAO_SPEED_LIM) speed = PAVAO_SPEED_LIM;
}

void Pavao::SetState(EnemyState state) {
    Enemy::SetState(state);

    switch (state) {
        case MOVING:
            moveTarget = associated.box.GetCenter() + Vec2(rand()%601 - 300,rand()%601 - 300);
            moveAngle = moveTarget.inclVec2(associated.box.GetCenter());
            ChangeSprite("resources/img/enemies/pavao_anim(150).png",6,.15F);
            break;
        case IDLE:
            idleTime = rand()%5001*0.001F + 2;
            speed = 0;
            ChangeSprite("resources/img/enemies/pavao_idle.png");
            break;
        case ATTACKING:
            speed = 0;
            ChangeSprite("resources/img/enemies/pavao_anim_attac(150).png",6,.15F);
            SetCollider(COLOR_GREEN);
            break;
        case DAMAGED:
            speed = 0;
            SetCollider(COLOR_BLUE, false);
            break;
        default:
            break;
    }
}

void Pavao::DeathAnimation() {
    GameObject* go = new GameObject();
    Sprite* sprite = new Sprite(*go, "resources/img/enemies/pavao_anim_morRENDO.png",8,.2F,1.6F);
    sprite->SetScale(2,2);
    go->AddComponent(sprite);
    go->box = associated.box;
    Game::GetInstance().GetCurrentState().AddObject(go);
}

void Pavao::DropItems() {
    DropItem(trigo);
}