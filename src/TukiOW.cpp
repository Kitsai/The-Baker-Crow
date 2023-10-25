#include <TukiOW.h>

TukiOW::TukiOW(GameObject& associated): Player(associated) {
    associated.AddComponent(new Sprite(associated, "resources/img/try.png"));
}

TukiOW::~TukiOW() {

}

void TukiOW::Update(float dt) {
    InputManager& iM = InputManager::GetInstance();
    if(hp <= 0) {
        associated.RequestDelete();
        GameData::playerAlive = false;
    }

    if(iM.KeyPress(Z_KEY) && state != PlayerState::DODGING) {
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
    CalcSpeed(dt);
    associated.box += speed*dt;
    CalcSpeed(dt);

    if(state == PlayerState::DODGING) {
        dashTimer.Update(dt);

        if(speed.magSquare() < TOW_SPEED_LIM*TOW_SPEED_LIM ) {
            speed = speed.normalized()*TOW_SPEED_LIM;
            state = WALKING;
            dashTimer.Restart();

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

void TukiOW::CalcSpeed(float dt) {
    InputManager& iM = InputManager::GetInstance();
    std::cout << "x: " << speed.x << " y: " << speed.y << std::endl;

    if(state == PlayerState::DODGING) {
        speed -= speed.normalized()*dt*TOW_DASH_DECELERATION*0.5F;
        return;
    }

    bool movementKey = false;

    if(iM.IsKeyDown(LEFT_ARROW_KEY)) {
        speed.x -= TOW_A*dt*0.5F;
        movementKey = true;
    } 
    if(iM.IsKeyDown(RIGHT_ARROW_KEY)) { 
        speed.x += TOW_A*dt*0.5F;     
        movementKey = true;
    }
    if(iM.IsKeyDown(UP_ARROW_KEY)) {
        speed.y -= TOW_A*dt*0.5F;
        movementKey = true;
    }
    if(iM.IsKeyDown(DOWN_ARROW_KEY)) {
        speed.y += TOW_A*dt*0.5F;
        movementKey = true;
    }
    Vec2 norm = speed.normalized();
    if(speed.magSquare() > TOW_SPEED_LIM*TOW_SPEED_LIM) 
        speed = norm * TOW_SPEED_LIM;

    if(!movementKey && state == WALKING && speed.magSquare() > 0) 
        speed -= norm*TOW_FRICTION*0.5F*dt; 

}

bool TukiOW::Is(std::string type) {
    return type == "TukiOW" || Player::Is(type);
}