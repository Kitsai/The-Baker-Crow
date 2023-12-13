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

//std::pair<Vec2,Vec2> Obstacle::GetColliderLimits() {

//}

Rect Obstacle::GetColliderBox() {
    auto collider = std::static_pointer_cast<Collider>(associated.GetComponent("Collider").lock());
    if (collider) return collider->box;
    else return Rect();
}

Vec2 Obstacle::GetNormalSpeed(Vec2 speed, Rect playerBox) {
    Vec2 normalSpeed;
    Rect colliderBox = GetColliderBox();
    std::vector<Vec2> pointsPlayerBox = {
        {playerBox.x, playerBox.y},
        {playerBox.x + playerBox.w, playerBox.y},
        {playerBox.x + playerBox.w, playerBox.y + playerBox.h},
        {playerBox.x, playerBox.y + playerBox.h}
    };

    std::vector<Vec2> pointsCollider = {
        {colliderBox.x, colliderBox.y},
        {colliderBox.x + colliderBox.w, colliderBox.y},
        {colliderBox.x + colliderBox.w, colliderBox.y + colliderBox.h},
        {colliderBox.x, colliderBox.y + colliderBox.h}
    };

    bool points[4] = {false, false, false, false}; // 0 = tl, 1 = tr, 2 = br, 3 = bl
    bool isolatedPoints[4] = {false, false, false, false}; // 0 = tl, 1 = tr, 2 = br, 3 = bl
    bool faces[4] = {false, false, false, false}; // 0 = top, 1 = right, 2 = bottom, 3 = left

    for(int i=0;i<4;i++) points[i] = colliderBox.isInside(pointsPlayerBox[i]);

    for(int i=0;i<4;i++) isolatedPoints[i] = points[i] && !points[(i+1)%4] && !points[(i+3)%4];

    for(int i=0;i<4;i++) faces[i] = points[i] && points[(i+1)%4];

    //TODO - isolated points

    if(faces[0] || faces[2]) normalSpeed.y = -speed.y;
    if(faces[1] || faces[3]) normalSpeed.x = -speed.x;

    return normalSpeed;
}