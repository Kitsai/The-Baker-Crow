#include "CameraFollower.h"
#include <algorithm>

CameraFollower::CameraFollower(GameObject& go): Component(go) {
    startPos = associated.box.GetPos();
}

void CameraFollower::Update(float dt) {
    associated.box = startPos + Camera::pos;
}

void CameraFollower::Render() {

}

bool CameraFollower::Is(std::string type) {
    if(type == "CameraFollower") 
        return true;
    else
        return false; 
}