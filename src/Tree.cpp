#include "Tree.h"
#include "defines/DefineColor.h"

Tree::Tree(GameObject& associated): Obstacle(associated) {

}

Tree::~Tree() {

}

bool Tree::Is(std::string type) {
    return type == "Tree" || Obstacle::Is(type);
}

void Tree::SetCollider() {
    Collider* collider = new Collider(associated,{1,1},{0,0}, COLOR_WHITE);
    associated.AddComponent(collider);

    
}