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
    Vec2 points[4] = {
        Vec2(playerBox.x, playerBox.y),
        Vec2(playerBox.x + playerBox.w, playerBox.y),
        Vec2(playerBox.x + playerBox.w, playerBox.y + playerBox.h),
        Vec2(playerBox.x, playerBox.y + playerBox.h)
    };

    Vec2 colliderPoints[4] = {
        Vec2(colliderBox.x, colliderBox.y),
        Vec2(colliderBox.x + colliderBox.w, colliderBox.y),
        Vec2(colliderBox.x + colliderBox.w, colliderBox.y + colliderBox.h),
        Vec2(colliderBox.x, colliderBox.y + colliderBox.h)
    };

    bool inside[4] = {false, false, false, false};

    for(int i=0;i<4;i++) inside[i] = colliderBox.isInside(points[i]);

    // bool faces[4] = {false, false, false, false}; // top, right, bottom, left

    for(int i=0;i<4;i++) 
        if(inside[i] && inside[(i+1)%4]) 
            return (Face)((i+2)%4); 
    
    for(int i=0;i<4;i++) 
        if(inside[i]) {
            Vec2 aux;
            if(i == 0) {
                aux = (colliderPoints[2] - points[0]).Abs();
                if(aux.x > aux.y) return BOTTOM;
                else return RIGHT;
            } 
            if(i == 1) {
                aux = (colliderPoints[3] - points[1]).Abs();
                if(aux.x > aux.y) return BOTTOM;
                else return LEFT;
            } 
            if(i == 2) {
                aux = (colliderPoints[0] - points[2]).Abs();
                if(aux.x > aux.y) return TOP;
                else return LEFT;
            }
            if(i == 3) {
                aux = (colliderPoints[1] - points[3]).Abs();
                if(aux.x > aux.y) return TOP;
                else return RIGHT;
            }
        }
            



    Vec2 aux = (playerBox.GetCenter() - colliderBox.GetCenter()).normalized();

    if(aux.x > 0.5) return RIGHT;
    else if(aux.x < -0.5) return LEFT;
    else if(aux.y > 0.5) return BOTTOM;
    else if(aux.y < -0.5) return TOP;
    else return NONE;
}