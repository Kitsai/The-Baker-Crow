#include "enemies/Pancake.h"

#include "Game.h"
#include "defines/DefineColor.h"

Pancake::Pancake(GameObject& assoc, int hp): Enemy(assoc,hp) {
    Sprite* sprite = new Sprite(assoc, "resources/img/enemies/pancake_idle.png");
    sprite->SetScale(2,2);
    assoc.AddComponent(sprite);
}

Pancake::~Pancake() {

}

void Pancake::Update(float dt) {
    Enemy::Update(dt);

    switch (state) {
        case MOVING:
            Move(dt);
            break;
        case IDLE:
            idleTime -= dt;
            if (idleTime <= 0) {
                SetState(MOVING);
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

bool Pancake::Is(std::string type) {
    return type == "Pancake" || Enemy::Is(type);
}


void Pancake::CalcSpeed(float dt) {
    speed += PANCAKE_A*dt;
    if(speed > PANCAKE_SPEED_LIM) speed = PANCAKE_SPEED_LIM;
}

void Pancake::SetState(EnemyState state) {

    this->state = state;

    switch (state) {
        case MOVING:
            moveTarget = associated.box.GetCenter() + Vec2(rand()%601 - 300,rand()%601 - 300);
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

}