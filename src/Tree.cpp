#include "Tree.h"
#include "defines/DefineColor.h"

Tree::Tree(GameObject& associated): Obstacle(associated) {
    associated.AddComponent(new Sprite(associated, "resources/img/overworld/arvore.png"));
    SetCollider();
}

Tree::~Tree() {

}

bool Tree::Is(std::string type) {
    return type == "Tree" || Obstacle::Is(type);
}

void Tree::SetCollider() {
    Collider* collider = new Collider(associated,{.3,.2},{0,90}, COLOR_WHITE);
    associated.AddComponent(collider); 
}