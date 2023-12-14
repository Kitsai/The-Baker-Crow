#include "Obstacle.h"
#include "Vec2.h"
#include <memory>
#include <vector>

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
    // Vec2 pointsPlayerBox[4] = {
    //     {playerBox.x, playerBox.y},
    //     {playerBox.x + playerBox.w, playerBox.y},
    //     {playerBox.x + playerBox.w, playerBox.y + playerBox.h},
    //     {playerBox.x, playerBox.y + playerBox.h}
    // };

    // Vec2 pointsCollider[4] = {
    //     {colliderBox.x, colliderBox.y},
    //     {colliderBox.x + colliderBox.w, colliderBox.y},
    //     {colliderBox.x + colliderBox.w, colliderBox.y + colliderBox.h},
    //     {colliderBox.x, colliderBox.y + colliderBox.h}
    // };

    Vec2 aux = (playerBox.GetCenter() - colliderBox.GetCenter()).normalized();

    if(aux.x > 0.5) return RIGHT;
    else if(aux.x < -0.5) return LEFT;
    else if(aux.y > 0.5) return BOTTOM;
    else if(aux.y < -0.5) return TOP;
    else return NONE;
}