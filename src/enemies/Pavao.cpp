#include "enemies/Pavao.h"
#include "GameObject.h"
#include "Game.h"

Pavao::Pavao(GameObject& assoc, int hp): Enemy(assoc,hp) {
    Sprite* sprite = new Sprite(assoc, "resources/img/enemies/pavao_idle.png");
    sprite->SetScale(2,2);
    assoc.AddComponent(sprite);
}

Pavao::~Pavao() {

}

void Pavao::Update(float dt) {
    Enemy::Update(dt);

    switch (state) {
        case MOVING:
            Move(dt);
            break;
        case ATTACKING:
            if(timer.Get() > .9F) {
                SetState(IDLE);
            }
            break;
        case IDLE:
            idleTime -= dt;
            if (idleTime <= 0) {
            
                
            }
            break;
        case DAMAGED:
            if (timer.Get() > 0.5F) {
                SetCollider(COLOR_RED, true);
                SetState(IDLE);
            }
            break;

        default:
            break;
    }
}

bool Pavao::Is(std::string type) {
    return type == "Pavao" || Enemy::Is(type);
}

void Pavao::CalcSpeed(float dt) {
    speed += PAVAO_A*dt;
    if(speed > PAVAO_SPEED_LIM) speed = PAVAO_SPEED_LIM;
}

void Pavao::SetState(EnemyState state) {
    this->state = state;

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
            ChangeSprite("resources/enemies/pavao_attac(150).png",6,.15F);
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

void Pavao::DeathAnimation() {
    GameObject* go = new GameObject();
    Sprite* sprite = new Sprite(*go, "resources/img/enemies/pancake_anim_morRENDO.png",8,.15F,1.2F);
    sprite->SetScale(2,2);
    go->AddComponent(sprite);
    go->box = associated.box;
    Game::GetInstance().GetCurrentState().AddObject(go);
}

void Pavao::DropItems() {

}