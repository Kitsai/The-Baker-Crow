#include "Enemy.h"

Enemy::Enemy(GameObject& associated,int hp): Component(associated) {
    this->hp = hp;
}

void Enemy::Update(float dt) {
    if(hp<=0) {
        associated.RequestDelete();
    }
}

bool Enemy::Is(std::string type) {
    if(type == "Enemy") 
        return true;
    else
        return false; 
}