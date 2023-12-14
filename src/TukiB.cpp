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

    int posX = associated.box.x;
    int posY = associated.box.y;

    if (iM.KeyPress(X_KEY))
        std::cout << "x: " << posX << " y: " << posY << std::endl;

    if (iM.KeyPress(Z_KEY) && floor == 1) {
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
    Rect oldBox = associated.box;
    associated.box += speed*dt;
    CheckCollisions(oldBox);
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
            faceDirection = UP;
            ChangeSprite("resources/img/Tuki_anim_costas.png",8,.2F);
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
            faceDirection = DOWN;
            ChangeSprite("resources/img/Tuki_anim2.png",8,.2F);
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

void TukiB::CheckCollisions(Rect oldBox) {
    if (floor == 0){
        // flower pot
        if (associated.box.x < 164 && associated.box.y < 156) {
            if (oldBox.x < 164) associated.box.y = 156;
            else if (oldBox.y < 156) associated.box.x = 164;
            else associated.box = oldBox;
        };
        // small locker
        if (associated.box.x > 538 && associated.box.x < 685 && associated.box.y < 200) {
            if (oldBox.x > 538 && oldBox.x < 685) associated.box.y = 200;
            else if (oldBox.y < 200 && oldBox.x < 600) associated.box.x = 538;
            else if (oldBox.y < 200 && oldBox.x > 600) associated.box.x = 685;
            else associated.box = oldBox;
        }
        // big drawer
        if (associated.box.x > 873 && associated.box.y < 200) {
            if (oldBox.x > 873) associated.box.y = 200;
            else if (oldBox.y < 200) associated.box.x = 873;
            else associated.box = oldBox;
        }

        // room collision
        if (associated.box.y < 125) associated.box.y = 125;
        if (associated.box.y > 582) associated.box.y = 582;
        if (associated.box.x > 1060) associated.box.x = 1060;
        if (associated.box.x < 107) associated.box.x = 107;
    }
    else if (floor == 1) {
        // in stairs
        if (associated.box.y < 135 && associated.box.x < 335){
            if (associated.box.x < 214) associated.box.x = 214;
            if (associated.box.x > 250) {
                if (oldBox.y < 135 && oldBox.x < 300) associated.box.x = 250;
                else if (oldBox.y < 135 && oldBox.x > 300) associated.box.x = 335;
                else if (oldBox.x > 250) associated.box.y = 135;
                else associated.box = oldBox;
                if (oldBox.y < 135 && oldBox.x > 300 && associated.box.y < 60) associated.box.y = 60;
            } 
        } else {
            // table //
            // down piece
            if (associated.box.x < 490 && associated.box.y > 470){
                if (oldBox.x < 490) associated.box.y = 470;
                else if (oldBox.y > 470) associated.box.x = 490;
            }
            // left piece
            if (associated.box.x > 340 && associated.box.x < 490 && associated.box.y > 220) {
                if (oldBox.x > 340 && oldBox.x < 490) associated.box.y = 220;
                else if (oldBox.y > 220 && oldBox.x < 400) associated.box.x = 340;
                else if (oldBox.y > 220 && oldBox.x > 400) associated.box.x = 490;
                else associated.box = oldBox;
            }

            // tables //
            if (associated.box.x > 780 && associated.box.x < 940 && associated.box.y < 253 && associated.box.y > 148){
                if (oldBox.x > 780 && oldBox.x < 940 && oldBox.y > 200) associated.box.y = 253;
                else if (oldBox.x > 780 && oldBox.x < 940 && oldBox.y < 200) associated.box.y = 148;
                else if (oldBox.y < 253 && oldBox.x < 860) associated.box.x = 780;
                else if (oldBox.y < 253 && oldBox.x > 860) associated.box.x = 940;
                else associated.box = oldBox;
            }

            if (associated.box.x > 780 && associated.box.x < 940 && associated.box.y < 545 && associated.box.y > 440){
                if (oldBox.x > 780 && oldBox.x < 940 && oldBox.y > 500) associated.box.y = 545;
                else if (oldBox.x > 780 && oldBox.x < 940 && oldBox.y < 500) associated.box.y = 440;
                else if (oldBox.y < 253 && oldBox.x < 860) associated.box.x = 780;
                else if (oldBox.y < 253 && oldBox.x > 860) associated.box.x = 940;
                else associated.box = oldBox;
            }

            // room collision
            if (associated.box.x < 209) associated.box.x = 209;
            if (associated.box.x > 960) associated.box.x = 960;
            if (associated.box.y < 60) associated.box.y = 60;
            if (associated.box.y > 590) associated.box.y = 590;
        }
    }
}