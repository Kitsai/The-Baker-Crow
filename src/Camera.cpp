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

    } else {

    }
}