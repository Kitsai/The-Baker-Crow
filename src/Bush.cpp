#include "Bush.h"

#include "defines/DefineColor.h"

Bush::Bush(GameObject& associated): Obstacle(associated) {
    associated.AddComponent(new Sprite(associated, "resources/img/overworld/arbusto.png"));
    SetCollider();
}

Bush::~Bush() {

}

bool Bush::Is(std::string type) {
    return type == "Bush" || Obstacle::Is(type);
}

void Bush::SetCollider() {
    Collider* collider = new Collider(associated,{1,1},{0,0}, COLOR_WHITE);
    associated.AddComponent(collider); 
}