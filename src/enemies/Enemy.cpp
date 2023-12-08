#include "enemies/Enemy.h"
#include "Game.h"

Enemy::Enemy(GameObject& associated,int hp): 
Component(associated),
hp(hp), 
state(IDLE),
idleTime((rand()%7001)*0.001F)
{

    associated.AddComponent(new Collider(associated));
    moveTarget = associated.box.GetCenter();
    //precisa verificar onde pode spawnar
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
    if (!Player::player) return;

    State& currState = Game::GetInstance().GetCurrentState();

    Vec2 playerPos = Player::player->GetPlayerCenterPos();

    float playerDist = playerPos.distVec2(associated.box.GetCenter());

    if (playerDist < ENEMY_ATACK_DIST) {
        SetState(ATTACKING);
    }
}

void Enemy::ChangeSprite(std::string file, int frameCount, float frameTime) {
    std::shared_ptr<Sprite> sprite = std::static_pointer_cast<Sprite>(associated.GetComponent("Sprite").lock());
    if (sprite != nullptr) {
        sprite->Open(file);
        sprite->SetFrameCount(frameCount);
        sprite->SetFrameTime(frameTime);
    }

    Vec2 center = associated.box.GetCenter();
    if(moveTarget.x > center.x) sprite->SetFlip(SDL_FLIP_HORIZONTAL);
    else if(moveTarget.x < center.x) sprite->SetFlip(SDL_FLIP_NONE);
    
}

void Enemy::SetCollider(SDL_Color color, bool active) {
    std::shared_ptr<Collider> collider = std::static_pointer_cast<Collider>(associated.GetComponent("Collider").lock());
    if (collider != nullptr) {
        collider->SetColor(color);
        collider->active = active;
    }
}



bool Enemy::Is(std::string type) {
    if(type == "Enemy") 
        return true;
    else
        return false; 
}