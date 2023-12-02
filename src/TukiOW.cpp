#include "TukiOW.h"
#include "Sprite.h"

TukiOW::TukiOW(GameObject& associated): Player(associated) {
    Sprite*  sprite = new Sprite(associated, "resources/img/try.png");
    sprite->SetScale(2,2);
    associated.AddComponent(sprite);
}

TukiOW::~TukiOW() {

}

void TukiOW::Update(float dt) {
    InputManager& iM = InputManager::GetInstance();
    State& currState = Game::GetInstance().GetCurrentState();

    if(hp <= 0) {
        associated.RequestDelete();
        GameData::playerAlive = false;
    }

    if(iM.KeyPress(X_KEY) && state != PlayerState::DODGING && state != PlayerState::ATTACKING) {
        
        GameObject* attk = new GameObject();
        attk->AddComponent(new Attack(*attk,currState.GetObjectPtr(&associated),50,true,1.0F,0));
        attk->angleDeg = speed.incl();
        attk->box = associated.box;
        attk->box.w += 50;
        attk->box.h += 50;
        state = ATTACKING;
        attack = currState.AddObject(attk);
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

        Collider* hitbox = (Collider*)associated.GetComponent("Collider").lock().get();
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

            Collider* hitbox = (Collider*)associated.GetComponent("Collider").lock().get();
            hitbox->active = true;
            hitbox->SetColor(COLOR_RED);
        }
    }
    else if(PlayerState::ATTACKING == state) {
        if(attack.expired()) {
            state = WALKING;
        }
    }
    else {
        // Switches from Walking to Standing.
        if(speed.magnitude() < 1) {
            state = STANDING;
            speed = {0,0};
        }
        else state = WALKING;
    }
} 

void TukiOW::Move(float dt) {
    CalcSpeed(dt);
    // std::cout << speed.magnitude() << std::endl;
    if(state == PlayerState::STANDING) {
        speed = speed*DAMP_STATIC;
    } else {
        speed = speed*DAMP_MOVING;
    }
    associated.box += speed*dt;
    CalcSpeed(dt);
}
 
void TukiOW::CalcSpeed(float dt) {
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
    if( state != PlayerState::DODGING && speed.magnitude() > TOW_SPEED_LIM) 
        speed = norm * TOW_SPEED_LIM;
}

bool TukiOW::Is(std::string type) {
    return type == "TukiOW" || Player::Is(type);
}