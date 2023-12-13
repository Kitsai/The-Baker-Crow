#include "Camera.h"

#include "Game.h"
#include "InputManager.h"

GameObject* Camera::focus = nullptr;
Vec2 Camera::pos;
Vec2 Camera::speed;

void Camera::Follow(GameObject* newFocus) {
    focus = newFocus;
}

void Camera::Unfollow() {   
    focus = nullptr;
}

void Camera::Update(float dt) { 
    if(focus != nullptr) {
        Game& game = Game::GetInstance();
        pos = focus->box.GetCenter() - (Vec2(game.GetWindowWidth(),game.GetWindowHeight())*0.5F);

        if(pos.x < 0) pos.x = 0;
        else if(pos.x > 3840) pos.x = 3840;
        if(pos.y < 0) pos.y = 0;
        else if(pos.y > 2160) pos.y = 2160;

    } else {

    }
}