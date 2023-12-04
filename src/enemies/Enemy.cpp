#include "enemies/Enemy.h"
#include "Component.h"

Enemy::Enemy(GameObject& associated, std::string file, int hp): Component(associated), hp(hp) {
    associated.AddComponent(new Sprite(associated));
    UpdateSprite(file);
}

void Enemy::Update(float dt) {

}

void Enemy::Render() {

}

bool Enemy::Is(std::string type) {
    return type == "Enemy";
}

void Enemy::Defeated() {
    associated.RequestDelete();
}

void Enemy::UpdateSprite(std::string file, int frameCount, float frameTime, float secondsToSelfDestruct) {
    associated.GetComponent("Sprite");
}