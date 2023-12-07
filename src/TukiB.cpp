#include "TukiB.h"

TukiB::TukiB(GameObject& associated): Player(associated) {
    associated.AddComponent(new Sprite(associated, "resources/img/try.png"));
    floor = 0;
}

TukiB::~TukiB() {

}

void TukiB::Update(float dt) {
    InputManager& iM = InputManager::GetInstance();

    if(hp <= 0) {
        associated.RequestDelete();
        GameData::playerAlive = false;
    }

    if(iM.KeyPress(Z_KEY) && Player::GetPlayerState() != PlayerState::DODGING) {
        //Sets the state to dodging sets the speed and deactivates the hitbox.
        Player::SetPlayerState(PlayerState::DODGING);

        Vec2 direction;
        if(iM.IsKeyDown(UP_ARROW_KEY) || iM.IsKeyDown(DOWN_ARROW_KEY) || iM.IsKeyDown(LEFT_ARROW_KEY) || iM.IsKeyDown(RIGHT_ARROW_KEY)) {
            if(iM.IsKeyDown(UP_ARROW_KEY)) direction.y -= 1;
            if(iM.IsKeyDown(DOWN_ARROW_KEY)) direction.y += 1;
            if(iM.IsKeyDown(LEFT_ARROW_KEY)) direction.x -= 1;
            if(iM.IsKeyDown(RIGHT_ARROW_KEY)) direction.x += 1;   
        } 
        else
            direction = speed;

        speed = direction.normalized() * TOW_DASH_SPEED;

        Collider* hitbox = (Collider*)associated.GetComponent("Collider").lock().get();
        hitbox->active = false;
        hitbox->SetColor(COLOR_BLUE);
    }

    // simulating the calculation of the speed integral by separating the calculation in two steps.
    Move(dt);
    
    if(Player::GetPlayerState() == PlayerState::DODGING) {
        //playerTimer.Update(dt);
        if(speed.magSquare() < TOW_SPEED_LIM*TOW_SPEED_LIM) {
            speed = speed.normalized()*TOW_SPEED_LIM;
            Player::SetPlayerState(PlayerState::WALKING);
            //playerTimer.Restart();

            Collider* hitbox = (Collider*)associated.GetComponent("Collider").lock().get();
            hitbox->active = true;
            hitbox->SetColor(COLOR_RED);
        }
    }
    else {
        // Switches from Walking to Standing.
        if(speed.magnitude() < 1) {
            Player::SetPlayerState(PlayerState::STANDING);
            speed = {0,0};
        }
        else Player::SetPlayerState(PlayerState::WALKING);
    }
} 

void TukiB::Move(float dt) {
    CalcSpeed(dt);
    // std::cout << speed.magnitude() << std::endl;
    if(Player::GetPlayerState() == PlayerState::STANDING) {
        speed = speed*TOW_DAMP_STATIC;
    } else {
        speed = speed*TOW_DAMP_MOVING;
    }
    associated.box += speed*dt;
    CalcSpeed(dt);
}
 
void TukiB::CalcSpeed(float dt) {
    InputManager& iM = InputManager::GetInstance();

    if(Player::GetPlayerState() == PlayerState::DODGING)
        return;

    if(iM.IsKeyDown(LEFT_ARROW_KEY)) {
        speed.x -= TOW_A*dt;
    } 
    if(iM.IsKeyDown(RIGHT_ARROW_KEY)) { 
        speed.x += TOW_A*dt;     
    }
    if(iM.IsKeyDown(UP_ARROW_KEY)) {
        speed.y -= TOW_A*dt;
    }
    if(iM.IsKeyDown(DOWN_ARROW_KEY)) {
        speed.y += TOW_A*dt;
    }
    Vec2 norm = speed.normalized();
    if( Player::GetPlayerState() != PlayerState::DODGING && speed.magnitude() > TOW_SPEED_LIM) 
        speed = norm * TOW_SPEED_LIM;
}

bool TukiB::Is(std::string type) {
    return type == "TukiB" || Player::Is(type);
}

void TukiB::SetFloor(int floor) {
    this->floor = floor;
}

int TukiB::GetFloor() {
    return floor;
}