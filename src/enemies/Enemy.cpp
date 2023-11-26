#include "Enemy.h"

Enemy::Enemy(GameObject& associated,int hp): Component(associated), hp(hp) {
    associated.AddComponent(new Collider(associated));
}


void Enemy::Update(float dt) {
    if(hp<=0) {
        Defeated();
    }
}

void Enemy::Render() {

}

bool Enemy::Is(std::string type) {
    if(type == "Enemy") 
        return true;
    else
        return false; 
}