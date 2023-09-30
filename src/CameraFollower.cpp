#include <CameraFollower.h>
#include <algorithm>

CameraFollower::CameraFollower(GameObject& go): Component(go) {

}

void CameraFollower::Update(float dt) {
    associated.box.x = Camera::pos.x;
    associated.box.y = Camera::pos.y;
}

void CameraFollower::Render() {

}

bool CameraFollower::Is(std::string type) {
    if(type == "CameraFollower") 
        return true;
    else
        return false; 
}