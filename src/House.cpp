#include "House.h"
#include "defines/DefineColor.h"

House::House(GameObject& associated, std::string file): Obstacle(associated) {
    associated.AddComponent(new Sprite(associated, file));
    SetCollider();
}

House::~House() {

}

bool House::Is(std::string type) {
    return type == "House" || Obstacle::Is(type);
}

void House::SetCollider() {
    Collider* collider = new Collider(associated,{1,.8},{0,-48.8}, COLOR_WHITE);
    associated.AddComponent(collider); 
}