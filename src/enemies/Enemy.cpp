#include "enemies/Enemy.h"

Enemy::Enemy(GameObject& associated,int hp): 
Component(associated),
hp(hp), 
speed(),
moveTarget(200,200),
idleTime(0)
{
    associated.box.SetCenter(moveTarget);
    associated.AddComponent(new Collider(associated));
    //precisa verificar onde pode spawnar
    SetState(IDLE);
}

Enemy::~Enemy() {

}

void Enemy::Update(float dt) {
    if(hp<=0) {
        Defeated();
    }

    timer.Update(dt);

    switch (state)
    {
    case IDLE:
        if(timer.Get() > idleTime) {
            SetState(MOVING);
        }
        break;
    case MOVING:
        Move(dt);
        break;

    case ATTACKING:
        Attack();
        break;
    default:
        break;
    }
}

void Enemy::Render() {

}

void Enemy::Defeated() {
    associated.RequestDelete();
    DeathAnimation();
}


void Enemy::Move(float dt) {
    CalcSpeed(dt);
    associated.box += speed*dt;
    CalcSpeed(dt);
}

void Enemy::CalcSpeed(float dt) {
    speed = Vec2(0,0);
}

void Enemy::Attack() {
    if (Player::player == nullptr) return;

    Vec2 playerPos = Player::player->GetPlayerPos();

    // float limit = associated.box

    // if()
}

bool Enemy::Is(std::string type) {
    if(type == "Enemy") 
        return true;
    else
        return false; 
}