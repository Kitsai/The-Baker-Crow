#include "enemies/Enemy.h"
#include "Game.h"

Enemy::Enemy(GameObject& associated,int hp): 
Component(associated),
hp(hp), 
state(IDLE),
idleTime((rand()%7001)*0.001F)
{
    associated.box.SetCenter(moveTarget);
    associated.AddComponent(new Collider(associated));
    moveTarget = 200;
}

Enemy::~Enemy() {

}

void Enemy::Update(float dt) {
    if(hp<=0) {
        Defeated();
    }

    timer.Update(dt);
}

void Enemy::Render() {

}

void Enemy::Defeated() {
    associated.RequestDelete();
    DeathAnimation();
    DropItems();
}

void Enemy::Attk() {
    if (Player::player == nullptr) return;

    State& currState = Game::GetInstance().GetCurrentState();

    Vec2 playerPos = Player::player->GetPlayerPos();

    float playerDist = playerPos.distVec2(associated.box.GetCenter());

    if (playerDist < ENEMY_ATACK_DIST) {
        GameObject* ao = new GameObject();
        float playerInc = playerPos.inclVec2(associated.box.GetCenter());
        ao->box.SetCenter(Vec2(60,0).GetRotated(playerInc) + associated.box.GetCenter());
        ao->AddComponent(new Attack(*ao,currState.GetObjectPtr(&associated),10));
        attack = currState.AddObject(ao);
    }
}

bool Enemy::Is(std::string type) {
    if(type == "Enemy") 
        return true;
    else
        return false; 
}