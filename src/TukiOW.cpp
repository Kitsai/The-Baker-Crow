#include "TukiOW.h"
#include "Sprite.h"
#include "defines/DefineInput.h"
#include <SDL2/SDL_render.h>

TukiOW::TukiOW(GameObject& associated): Player(associated) {
    Sprite*  sprite = new Sprite(associated, "resources/img/Tuki_idle_front.png");
    sprite->SetScale(2,2);
    associated.AddComponent(sprite);
    faceDirection = DOWN;
}

TukiOW::~TukiOW() {

}

std::string e2s[5] = {"STANDING","WALKING","ATTACKING","DODGING","DAMAGED"};

void TukiOW::Update(float dt) {
    InputManager& iM = InputManager::GetInstance();

    playerTimer.Update(dt);

    if(hp <= 0) {
        associated.RequestDelete();
        GameData::playerAlive = false;
    }

    if(iM.KeyPress(X_KEY) && GetPlayerState() != DODGING && GetPlayerState() != ATTACKING) {
        SetPlayerState(ATTACKING);
    }

    if(iM.KeyPress(Z_KEY) && GetPlayerState() != DODGING && GetPlayerState() != ATTACKING) {
        //Sets the state to dodging sets the speed and deactivates the hitbox.
        SetPlayerState(DODGING);

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

        SetCollider(COLOR_BLUE);
    }

    // simulating the calculation of the speed integral by separating the calculation in two steps.
    Move(dt);
    
    if(GetPlayerState() == DODGING) {
        //playerTimer.Update(dt);
        if(speed.magSquare() < TOW_SPEED_LIM*TOW_SPEED_LIM) {
            speed = speed.normalized()*TOW_SPEED_LIM;
            SetPlayerState(WALKING);

            SetCollider(COLOR_RED);
        }
    }
    else if(ATTACKING == GetPlayerState()) {
        if(playerTimer.Get() > TOW_ATTACK_TIME) {
            SetPlayerState(STANDING);
            SetCollider(COLOR_RED);
        }

    } else if(DAMAGED == GetPlayerState()) {
        if(playerTimer.Get() > TOW_DAMAGED_TIME) {
            SetPlayerState(STANDING);
            SetCollider(COLOR_RED);
        }
    }
    else {
        // Switches from Walking to Standing.
        if(speed.magnitude() < 1) {
            if(GetPlayerState() == WALKING) 
                SetPlayerState(STANDING);
            speed = {0,0};
        }
        else if(GetPlayerState() == STANDING) SetPlayerState(WALKING);
    }

    if(iM.KeyPress(K_KEY)) SetPlayerState(DAMAGED);

    // if(attackCooldown > 0) attackCooldown -= dt;
    
} 

void TukiOW::Move(float dt) {
    CalcSpeed(dt);
    // std::cout << speed.magnitude() << std::endl;
    if(GetPlayerState() == STANDING) {
        speed = speed*DAMP_STATIC;
    } else {
        speed = speed*DAMP_MOVING;
    }
    associated.box += speed*dt;
    CalcSpeed(dt);
}
 
void TukiOW::CalcSpeed(float dt) {
    InputManager& iM = InputManager::GetInstance();

    if(GetPlayerState() == DODGING)
        return;

    if(iM.IsKeyDown(LEFT_ARROW_KEY)) {
        speed.x -= TOW_A*dt;
    } 
    if(iM.IsKeyDown(RIGHT_ARROW_KEY)) { 
        speed.x += TOW_A*dt;     
    }
    if(iM.IsKeyDown(UP_ARROW_KEY)) {
        speed.y -= TOW_A*dt;
        if(GetPlayerState() == WALKING && faceDirection == DOWN) {
            ChangeSprite("resources/img/Tuki_anim_costas.png",8,.2F);
            faceDirection = UP;
        }
    }
    if(iM.IsKeyDown(DOWN_ARROW_KEY)) {
        speed.y += TOW_A*dt;
        if(GetPlayerState() == WALKING && faceDirection == UP) {
            ChangeSprite("resources/img/Tuki_anim2.png",8,.2F);
            faceDirection = DOWN;
        }
    }
    Vec2 norm = speed.normalized();
    if( GetPlayerState() != DODGING && speed.magnitude() > TOW_SPEED_LIM) 
        speed = norm * TOW_SPEED_LIM;
}

bool TukiOW::Is(std::string type) {
    return type == "TukiOW" || Player::Is(type);
}

void TukiOW::SetPlayerState(PlayerState state) {

    switch (state)
    {
    case STANDING:
        if(faceDirection == DOWN)
            ChangeSprite("resources/img/Tuki_idle_front.png",1,1);
        else if(faceDirection == UP)
            ChangeSprite("resources/img/Tuki_idle_costas.png",1,1);
        break;
    case WALKING:
        if(faceDirection == DOWN)
            ChangeSprite("resources/img/Tuki_anim2.png",8,.2F);
        else if(faceDirection == UP)
            ChangeSprite("resources/img/Tuki_anim_costas.png",8,.2F);
        break;
    case ATTACKING:
        ChangeSprite("resources/img/tuki_anim_attac.png",4,.1F);
        speed = 0;
        SetCollider(COLOR_GREEN);
        break;
    case DODGING:
        ChangeSprite("resources/img/try.png",1,1);
        break;
    case DAMAGED:
        if(this->GetPlayerState() == DAMAGED) break;
        speed = 0;
        hp--;
        ChangeSprite("resources/img/tuki_anim_dano.png",4,.15F);
        SetCollider(COLOR_BLUE);
        break;
    default:
        break;
    }

    Player::SetPlayerState(state);

    // std::cout << "Player state: " << e2s[state] << std::endl;
}