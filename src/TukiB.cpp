#include "TukiB.h"
#include "Sprite.h"
#include "states/BakeryState.h"
#include "states/ChoiceState.h"

TukiB::TukiB(GameObject& associated): Player(associated) {
    Sprite*  sprite = new Sprite(associated, "resources/img/Tuki_idle_front.png");
    sprite->SetScale(2.0f,2.0f);
    associated.AddComponent(sprite);
    faceDirection = DOWN;

    Talk("resources/img/menu_button.png", 1.0f);
}

TukiB::~TukiB() {

}

void TukiB::Update(float dt) {
    InputManager& iM = InputManager::GetInstance();

    // simulating the calculation of the speed integral by separating the calculation in two steps.
    Move(dt);

    if (iM.KeyPress(Z_KEY) && floor == 1) {
        int posX = associated.box.x;
        int posY = associated.box.y;


        if (faceDirection == DOWN && posX < 300 && posX > 250 && posY > 450) {
            Game::GetInstance().Push(new ChoiceState());
        }
    }
    
     // Switches from Walking to Standing.
    if(speed.magnitude() < 1) {
        if(GetPlayerState() == WALKING) SetPlayerState(STANDING);
        speed = {0,0};
        }
        else if(GetPlayerState() == STANDING) SetPlayerState(WALKING);
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
        if (floor == 1 && associated.box.x < 300 && associated.box.x > 90 && associated.box.y < 0) {
            floor = 0;
            associated.box.x = 240;
            associated.box.y = 530;
        }
    }
    if(iM.IsKeyDown(DOWN_ARROW_KEY)) {
        speed.y += TOW_A*dt;
        if(GetPlayerState() == WALKING && faceDirection == UP) {
            ChangeSprite("resources/img/Tuki_anim2.png",8,.2F);
            faceDirection = DOWN;
        }
        if (floor == 0 && associated.box.x < 260 && associated.box.x > 70 && associated.box.y > 530) {
            floor = 1;
            associated.box.x = 240;
            associated.box.y = 0;
        } else if (floor == 1  && associated.box.x < 600 && associated.box.x > 500 && associated.box.y > 530) {
            floor = 2;
        }
    }
    Vec2 norm = speed.normalized();
    if( speed.magnitude() > TOW_SPEED_LIM) 
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

void TukiB::SetPlayerState(PlayerState state) {

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
    default:
        break;
    }

    Player::SetPlayerState(state);
}

void TukiB::Talk(std::string file, float time){
    SetPlayerState(STANDING);

    GameObject* speakBalloon = new GameObject();
    Sprite* sprite = new Sprite(*speakBalloon, "resources/img/MenuButton.png");
    speakBalloon->AddComponent(sprite);
    speakBalloon->box.x = 0;
    speakBalloon->box.y = 0;
}

void TukiB::ResetSpeed() {
    speed = 0;
}   