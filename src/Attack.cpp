#include <Attack.h>

Attack::Attack(GameObject& associated, int damage, bool friendly, Vec2 speed, float duration): Component(associated) {
    this->speed = speed;
    this->damage = damage;
    this->friendly = friendly;
    this->duration = duration;    

    associated.AddComponent(new Collider(associated,{1,1},{0,0},COLOR_GREEN));
}

Attack::Attack(GameObject& associated, int damage, bool friendly, Vec2 speed, std::string file,float duration, int frameCount,float frameTime): Component(associated) {
    this->speed = speed;
    this->damage = damage;
    this->friendly = friendly;
    this->duration = duration;

    associated.AddComponent(new Sprite(associated,file,frameCount,frameTime));

    associated.AddComponent(new Collider(associated,{1,1},{0,0},COLOR_GREEN));
}

Attack::~Attack() {

}

void Attack::Update(float dt) {
    attackTimer.Update(dt);
    if(attackTimer.Get() >= duration) {
        associated.RequestDelete();
        return;
    }
    associated.box += speed*dt;
}

void Attack::Render() {

}

bool Attack::Is(std::string type) {
    return type == "Attack";
}

int Attack::GetDamage() {
    return damage;
}

bool Attack::IsFriendly() {
    return friendly;
}