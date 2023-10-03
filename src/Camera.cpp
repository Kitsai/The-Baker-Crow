#include <Camera.h>

#include <Game.h>
#include <InputManager.h>

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
        pos = focus->box.GetCenter() - (Vec2(game.GetWindowWidth(),game.GetWindowHeight())*0.5);

    } else {

        float dSpeed = dt*CAMERA_A;

        InputManager& iM = InputManager::GetInstance();

        bool keyPressed = false;

        if(iM.IsKeyDown(RIGHT_ARROW_KEY)){
            speed.x += dSpeed;
            keyPressed = true;
        }
        if(iM.IsKeyDown(LEFT_ARROW_KEY)) {
            speed.x -= dSpeed;
            keyPressed = true;
        }

        if(iM.IsKeyDown(UP_ARROW_KEY)) {
            speed.y -= dSpeed;
            keyPressed = true;
        }
        if(iM.IsKeyDown(DOWN_ARROW_KEY)) {
            speed.y += dSpeed;
            keyPressed = true;
        }
        if(keyPressed) {

            if(speed.x > CAMERA_SPEED_LIM) speed.x = CAMERA_SPEED_LIM;

            if(speed.x < -CAMERA_SPEED_LIM) speed.x = -CAMERA_SPEED_LIM;

            if(speed.y > CAMERA_SPEED_LIM) speed.y = CAMERA_SPEED_LIM;

            if(speed.y < -CAMERA_SPEED_LIM) speed.y = -CAMERA_SPEED_LIM;
            

        } else {
            if(speed.x>0) {
                speed.x -= CAMERA_RESET_A;
                if(speed.x<0) speed.x = 0;
            }
            if(speed.x<0) {
                speed.x += CAMERA_RESET_A;
                if(speed.x>0) speed.x = 0;
            }
            if(speed.y>0) {
                speed.y -= CAMERA_RESET_A;
                if(speed.y<0) speed.y = 0;
            }
            if(speed.y<0) {
                speed.y += CAMERA_RESET_A;
                if(speed.y>0) speed.y = 0;
            }

        }
        pos = pos+speed;


        pos.x = (pos.x<0)? 0:pos.x; 
        pos.y = (pos.y<0)? 0:pos.y;

        pos.x = (pos.x>574)? 574:pos.x;
        pos.y = (pos.y>1000)? 1000:pos.y; 
    }
}