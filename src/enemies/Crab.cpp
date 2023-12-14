#include "enemies/Crab.h"
#include "GameObject.h"
#include "Game.h"

Crab::Crab(GameObject& assoc, int hp): Enemy(assoc,true,hp) {
    Sprite* sprite = new Sprite(assoc, "resources/img/enemies/carang_idle.png");
    sprite->SetScale(2,2);
    assoc.AddComponent(sprite);
}

Crab::~Crab() {

}

bool Crab::Is(std::string type) {
    return type == "Crab" || Enemy::Is(type);
}

void Crab::CalcSpeed(float dt) {
    speed += CRAB_A*dt;
    if(speed > CRAB_SPEED_LIM) speed = CRAB_SPEED_LIM;
}

void Crab::SetState(EnemyState state) {
    Enemy::SetState(state);

    switch (state) {
        case MOVING:
            moveTarget = associated.box.GetCenter() + Vec2(rand()%601 - 300,rand()%601 - 300);
            CheckBorders();
            moveAngle = moveTarget.inclVec2(associated.box.GetCenter());
            ChangeSprite("resources/img/enemies/carang_anim(150).png",4,.15F);
            break;
        case IDLE:
            idleTime = rand()%3001*0.001F + 2;
            speed = 0;
            ChangeSprite("resources/img/enemies/carang_idle.png");
            break;
        case ATTACKING:
            speed = 0;
            ChangeSprite("resources/img/enemies/carang_anim_attac(100).png",6,.15F);
            SetCollider(COLOR_GREEN);
            break;
        case DAMAGED:
            speed = 0;
            SetCollider(COLOR_BLUE, false);
            break;
        default:
            break;
    }
}

void Crab::DeathAnimation() {
    GameObject* go = new GameObject();
    Sprite* sprite = new Sprite(*go, "resources/img/enemies/carang_anim_morEENDO(150).png",8,.15F,1.2F);
    sprite->SetScale(2,2);
    go->AddComponent(sprite);
    go->box = associated.box;
    Game::GetInstance().GetCurrentState().AddObject(go);
}

void Crab::DropItems() {
    int chance = 50;
    if(GameData::hasItem[chocolate].first) chance -= 30;
    if(GameData::hasItem[straw].first) chance += 30;

    if((std::rand()%100) < chance)
        DropItem(chocolate);
    else
        DropItem(straw);
}