#include "Attack.h"

Attack::Attack(GameObject& associated, 
    std::weak_ptr<GameObject> origin, 
    int damage,
    bool friendly, 
    float duration, 
    float speed
): Component(associated) {
    this->origin = origin;
    this->speed = Vec2(1,0).GetRotated(associated.angleDeg)*speed;
    this->damage = damage;
    this->friendly = friendly;
    this->duration = duration;    

    associated.box.w = 32;
    associated.box.h = 32;

    associated.AddComponent((std::shared_ptr<Collider>)new Collider(associated,{1,1},{0,0},COLOR_GREEN));
}

Attack::Attack(GameObject& associated, 
    std::weak_ptr<GameObject> origin,
    int damage, 
    std::string file, 
    bool friendly, 
    float speed,
    float duration, 
    int frameCount,
    float frameTime
): Component(associated) {
    this->origin = origin;
    this->speed = speed;
    this->damage = damage;
    this->friendly = friendly;
    this->duration = duration;

    associated.AddComponent((std::shared_ptr<Sprite>)new Sprite(associated,file,frameCount,frameTime));

    associated.AddComponent((std::shared_ptr<Collider>)new Collider(associated,{1,1},{0,0},COLOR_GREEN));
}

Attack::~Attack() {

}

void Attack::Update(float dt) {
    if(duration > 0) {
        attackTimer.Update(dt);
        if(attackTimer.Get() > duration) {
            associated.RequestDelete();
        }
    }


    if(speed != 0)
        associated.box += speed;
    else {
        std::shared_ptr<GameObject> ptr = origin.lock();
        if(ptr == nullptr) 
            associated.RequestDelete();
        else
            associated.box.SetCenter(Vec2(32,0).GetRotated(speed.incl()) + ptr->box.GetCenter());
    }
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