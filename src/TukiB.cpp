#include "TukiB.h"

TukiB::TukiB(GameObject& associated): Player(associated) {
    associated.AddComponent(new Sprite(associated, "resources/img/try.png"));
    Player::player = this;
    floor = 0;
}

TukiB::~TukiB() {

}

void TukiB::Update(float dt) {
    InputManager& iM = InputManager::GetInstance();
    State& currState = Game::GetInstance().GetCurrentState();

    if(hp <= 0) {
        associated.RequestDelete();
        GameData::playerAlive = false;
    }

    if(iM.KeyPress(Z_KEY) && state != PlayerState::DODGING && state != PlayerState::ATTACKING) {
        //Sets the state to dodging sets the speed and deactivates the hitbox.
        state = PlayerState::DODGING;

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

        Collider* hitbox = (Collider*)associated.GetComponent("Collider");
        hitbox->active = false;
        hitbox->SetColor(COLOR_BLUE);
    }

    // simulating the calculation of the speed integral by separating the calculation in two steps.
    Move(dt);

    if(state == PlayerState::DODGING) {
        //playerTimer.Update(dt);

        if(speed.magSquare() < TOW_SPEED_LIM*TOW_SPEED_LIM) {
            speed = speed.normalized()*TOW_SPEED_LIM;
            state = WALKING;
            //playerTimer.Restart();

            Collider* hitbox = (Collider*)associated.GetComponent("Collider");
            hitbox->active = true;
            hitbox->SetColor(COLOR_RED);
        }
    }
    else {
        // Switches from Walking to Standing.
        if(speed.magnitude() < 50) {
            state = STANDING;
            speed = {0,0};
        }
        else state = WALKING;
    }
} 

void TukiB::Move(float dt) {
    CalcSpeed(dt);
    if(state == PlayerState::STANDING) {
        speed = speed*TOW_DAMP_STATIC;
    } 
    //if(state == PlayerState::DODGING) {
    //    speed = speed * 
    //} 
    else {
        speed = speed*TOW_DAMP_MOVING;
    }
    associated.box += speed*dt*GLOBAL_SPEED_SCALER;
    CalcSpeed(dt);
}
 
void TukiB::CalcSpeed(float dt) {
    InputManager& iM = InputManager::GetInstance();

    if(state == PlayerState::DODGING)
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
    if(speed.magSquare() > TOW_SPEED_LIM*TOW_SPEED_LIM) 
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