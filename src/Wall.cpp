#include "Wall.h"

#include "defines/DefineColor.h"

Wall::Wall(GameObject& associated): Obstacle(associated) {
    associated.AddComponent(new Sprite(associated, "resources/img/overworld/parede.png"));
    SetCollider();
}

Wall::~Wall() {

}

bool Wall::Is(std::string type) {
    return type == "Wall" || Obstacle::Is(type);
}

void Wall::SetCollider() {
    Collider* collider = new Collider(associated,{1,1},{0,0}, COLOR_WHITE);
    associated.AddComponent(collider); 
}