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
    if (Player::player.expired()) return;

    State& currState = Game::GetInstance().GetCurrentState();

    Vec2 playerPos = Player::player.lock()->box.GetCenter();

    float playerDist = playerPos.distVec2(associated.box.GetCenter());

    if (playerDist < ENEMY_ATACK_DIST) {
        GameObject* ao = new GameObject();
        float playerInc = playerPos.inclVec2(associated.box.GetCenter());
        ao->box.SetCenter(Vec2(60,0).GetRotated(playerInc) + associated.box.GetCenter());
        ao->AddComponent(new Attack(*ao,currState.GetObjectPtr(&associated),10));
        attack = currState.AddObject(ao);
    }
}

void Enemy::ChangeSprite(std::string file, int frameCount, float frameTime) {
    std::shared_ptr<Sprite> sprite = std::static_pointer_cast<Sprite>(associated.GetComponent("Sprite").lock());
    if (sprite != nullptr) {
        sprite->Open(file);
        sprite->SetFrameCount(frameCount);
        sprite->SetFrameTime(frameTime);
    }
}

bool Enemy::Is(std::string type) {
    if(type == "Enemy") 
        return true;
    else
        return false; 
}