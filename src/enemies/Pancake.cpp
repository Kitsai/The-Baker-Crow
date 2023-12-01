#include "enemies/Pancake.h"

Pancake::Pancake(GameObject& assoc, int hp): Enemy(assoc,hp) {
    assoc.AddComponent(new Sprite(assoc, "resources/img/pancake_idle.png"));

}

Pancake::~Pancake() {

}

void Pancake::Update(float dt) {
    Enemy::Update(dt);

    switch (state) {
        case MOVING:
            Move(dt);
            break;
        case ATTACKING:
            if (attack.expired()) {
                SetState(IDLE);
            }
            break;
        case IDLE:
            idleTime -= dt;
            if (idleTime <= 0) {
                SetState(MOVING);
            }
            break;
        default:
            break;
    }
}

bool Pancake::Is(std::string type) {
    return type == "Pancake" || Enemy::Is(type);
}

void Pancake::Move (float dt) {
    if (moveTarget.distVec2(associated.box.GetCenter()) < 5) {
        associated.box.SetCenter(moveTarget);
        SetState(IDLE);
    } else {
        CalcSpeed(dt);
        speed = speed*DAMP_MOVING;
        associated.box += Vec2(cos(moveAngle),sin(moveAngle))*dt*speed;
        CalcSpeed(dt);
    }
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
            ChangeSprite("resources/img/pancake_anim.png",8,.15F);
            break;
        case ATTACKING:
            Attk();
            break;
        case IDLE:
            idleTime = rand()%5001*0.001F + 2;
            speed = 0;
            ChangeSprite("resources/img/pancake_idle.png");
            break;
        default:
            break;
    }
}

void Pancake::DeathAnimation() {
    GameObject* go = new GameObject();
    go->box = associated.box;
}

void Pancake::DropItems() {

}