#include "Obstacle.h"
#include "Vec2.h"
#include <memory>
#include <vector>
#include <iostream>

Obstacle::Obstacle(GameObject& associated): Component(associated) {

}

Obstacle::~Obstacle() {

}

void Obstacle::Update(float dt) {

}

void Obstacle::Render() {

}

bool Obstacle::Is(std::string type) {
    return type == "Obstacle";
}

Rect Obstacle::GetColliderBox() {
    auto collider = std::static_pointer_cast<Collider>(associated.GetComponent("Collider").lock());
    if (collider) return Rect(collider->box);
    else return Rect();
}

Obstacle::Face Obstacle::GetFace(Rect playerBox) {
    Rect colliderBox = GetColliderBox();
    // Vec2 points[4] = {
    //     Vec2(colliderBox.x, colliderBox.y),
    //     Vec2(colliderBox.x + colliderBox.w, colliderBox.y),
    //     Vec2(colliderBox.x + colliderBox.w, colliderBox.y + colliderBox.h),
    //     Vec2(colliderBox.x, colliderBox.y + colliderBox.h)
    // };

    // bool inside[4] = {false, false, false, false};

    // for(int i=0;i<4;i++) inside[i] = colliderBox.isInside(points[i]);
    

    Vec2 aux = (playerBox.GetCenter() - colliderBox.GetCenter()).normalized();

    if(aux.x > 0.5) return RIGHT;
    else if(aux.x < -0.5) return LEFT;
    else if(aux.y > 0.5) return BOTTOM;
    else if(aux.y < -0.5) return TOP;
    else return NONE;
}