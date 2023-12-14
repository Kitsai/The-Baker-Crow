#include "enemies/Enemy.h"
#include "Game.h"

Enemy::Enemy(GameObject& associated, bool attacker, int hp): 
Component(associated),
hp(hp), 
state(IDLE),
attacker(attacker),
idleTime((rand()%7001)*0.001F)
{
    associated.AddComponent(new Collider(associated));
    moveTarget = associated.box.GetCenter();
    //precisa verificar onde pode spawnar
}

Enemy::~Enemy() {

}

void Enemy::Update(float dt) {
    if(hp<=0) {
        Defeated();
    }

    timer.Update(dt);

    switch (state) {
        case MOVING:
            Move(dt);
            break;
        case ATTACKING:
            if(timer.Get() > .9F) {
                SetCollider(COLOR_RED);
                if(rand()%10 < 7) SetState(IDLE);
                else SetState(MOVING);
            }
            break;
        case IDLE:
            idleTime -= dt;
            if (idleTime <= 0) {
                if(!Attk()) SetState(MOVING);       
            }
            break;
        case DAMAGED:
            if (timer.Get() > 0.5F) {
                SetCollider(COLOR_RED, true);
                SetState(IDLE);
            }
            break;

        default:
            break;
    }
}

void Enemy::Render() {

}

Enemy::EnemyState Enemy::GetState() {
    return state;
}

void Enemy::Defeated() {
    associated.RequestDelete();
    DeathAnimation();
    DropItems();
}

bool Enemy::Attk() {
    if (!attacker || !Player::player) return false;

    Vec2 playerPos = Player::player->GetPlayerCenterPos();

    float playerDist = playerPos.distVec2(associated.box.GetCenter());

    if(playerDist > ENEMY_ATACK_DIST) return false;

    SetState(ATTACKING);
    return true;
}

void Enemy::SetState(EnemyState state) {
    this->state = state;
    timer.Restart();
}

void Enemy::ChangeSprite(std::string file, int frameCount, float frameTime) {
    Vec2 center = associated.box.GetCenter();
    std::shared_ptr<Sprite> sprite = std::static_pointer_cast<Sprite>(associated.GetComponent("Sprite").lock());
    if (sprite != nullptr) {
        sprite->Open(file);
        sprite->SetFrameCount(frameCount);
        sprite->SetFrameTime(frameTime);
        associated.box.SetCenter(center);
    }

    if(moveTarget.x > center.x) sprite->SetFlip(SDL_FLIP_HORIZONTAL);
    else if(moveTarget.x < center.x) sprite->SetFlip(SDL_FLIP_NONE);
    
}

void Enemy::ChangeSprite(std::string file, SDL_RendererFlip flip, int frameCount, float frameTime) {
    Vec2 center = associated.box.GetCenter();
    std::shared_ptr<Sprite> sprite = std::static_pointer_cast<Sprite>(associated.GetComponent("Sprite").lock());
    if (sprite != nullptr) {
        sprite->Open(file);
        sprite->SetFrameCount(frameCount);
        sprite->SetFrameTime(frameTime);
        sprite->SetFlip(flip);
        associated.box.SetCenter(center);
    }
}

void Enemy::DropItem(FoodItemType itemType) {
    GameObject* item = new GameObject();
    item->box.SetCenter(associated.box.GetCenter() + Vec2(rand()%201 - 100,rand()%201 - 100)) ;
    item->AddComponent(new DroppedItem(*item, itemType));
    Game::GetInstance().GetCurrentState().AddObject(item);
}

void Enemy::SetCollider(SDL_Color color, bool active) {
    std::shared_ptr<Collider> collider = std::static_pointer_cast<Collider>(associated.GetComponent("Collider").lock());
    if (collider) {
        collider->SetColor(color);
        collider->active = active;
    }
}

void Enemy::Move(float dt) {
    if (moveTarget.distVec2(associated.box.GetCenter()) < 5) {
        associated.box.SetCenter(moveTarget);
        SetState(IDLE);
    } else {
        CalcSpeed(dt);
        speed = speed*DAMP_MOVING;
        associated.box.SetCenter(associated.box.GetCenter() + Vec2(cos(moveAngle),sin(moveAngle))*dt*speed);
        CalcSpeed(dt);
    }
}


bool Enemy::Is(std::string type) {
    if(type == "Enemy") 
        return true;
    else
        return false; 
}


void Enemy::NotifyCollision(GameObject& other) {
    if(other.GetComponent("TukiOW").lock()) {
        auto tuki = Player::player;
        auto tstate = tuki->GetPlayerState();
        if(tstate == Player::PlayerState::ATTACKING && Player::PlayerState::DODGING != tstate && Player::PlayerState::DAMAGED != tstate) {
            hp -= 50;
            SetState(DAMAGED);
        }
    } else if(other.GetComponent("Obstacle").lock()) {
        moveTarget = associated.box.GetCenter();
    }
}