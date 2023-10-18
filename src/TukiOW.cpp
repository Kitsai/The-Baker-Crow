#include <TukiOW.h>

TukiOW::TukiOW(GameObject& associated): Player(associated) {
    associated.AddComponent(new Sprite(associated, "resources/img/tuki_pre.png"));
}

TukiOW::~TukiOW() {

}

void TukiOW::Update(float dt) {
    if(hp <= 0) {
        associated.RequestDelete();
        GameData::playerAlive = false;
    }

    CalcSpeed(dt);
    associated.box += speed*dt;
    CalcSpeed(dt);
} 

void TukiOW::CalcSpeed(float dt) {
    InputManager& iM = InputManager::GetInstance();

    bool movementKey = false;

    if(iM.IsKeyDown(LEFT_ARROW_KEY)) {
        speed.x -= TOW_A*dt*0.5F;
    } 
    if(iM.IsKeyDown(RIGHT_ARROW_KEY)) { 
        speed.x += TOW_A*dt*0.5F;     
    }
    if(iM.IsKeyDown(UP_ARROW_KEY)) {
        speed.y -= TOW_A*dt*0.5F;
    }
    if(iM.IsKeyDown(DOWN_ARROW_KEY)) {
        speed.y += TOW_A*dt*0.5F;
    }
    Vec2 norm = speed.normalized();
    if(speed.magnitude() > TOW_SPEED_LIM) speed = norm * TOW_SPEED_LIM;

    if(!movementKey && state == WALKING) speed -= norm*TOW_FRICTION*-0.5F; 
}

bool TukiOW::Is(std::string type) {
    return type == "TukiOW" || Player::Is(type);
}