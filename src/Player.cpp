#include "Player.h"

#include "Game.h"
#include "Vec2.h"
#include "enemies/Enemy.h"
#include "Obstacle.h"

Player* Player::player = nullptr;

Player::Player(GameObject& associated): Component(associated) {
    hp = 3;
    state = STANDING;
    speed = {0,0};

    player = this;

    Game& game = Game::GetInstance();
    associated.AddComponent(new Collider(associated));
    associated.box.SetCenter(Vec2(game.GetWindowWidth(),game.GetWindowHeight()) * 0.5F);
}

Player::~Player() {
}

void Player::Render() {

}

bool Player::Is(std::string type) {
    return type == "Player";
}

bool Player::IsInTile(int index, Vec2 pos, int tileSize) {
    return IsInTile(index) && IsInTile(pos,tileSize);
}

bool Player::IsInTile(int index) {
    /// @todo make it so is look for index in all tile maps below player on the object vector and all layers of those maps.
    return true;    
}

bool Player::IsInTile(Vec2 pos,int tileSize) {
    //Rect box = associated.box;
    /*Vec2 points[] = {
        Vec2(box.x,box.y), //  0 - top left
        Vec2(box.x + box.w, box.y), // 1 - top right
        Vec2(box.x,box.y + box.h), // 2 - bottom left
        Vec2(box.x + box.w,box.y + box.h) // 3 - bottom right
    };*/
    return true;
}

Player::PlayerState Player::GetPlayerState() {
    return state;
}

Vec2 Player::GetPlayerPos() {
    return GetPlayerCenterPos() - Vec2(Game::GetInstance().GetWindowWidth()*0.5,Game::GetInstance().GetWindowHeight()*0.5);
    return associated.box.GetPos();
}

Vec2 Player::GetPlayerBoxPos() {
    return associated.box.GetPos();
}

Vec2 Player::GetPlayerCenterPos() {
    return associated.box.GetCenter();
}

void Player::SetPlayerState(PlayerState state) {
    this->state = state;

    playerTimer.Restart();
}

void Player::ChangeSprite(std::string file, int frameCount, float frameTime, SDL_RendererFlip flip) {
    Vec2 center = associated.box.GetCenter();
    auto sprite = std::static_pointer_cast<Sprite>(associated.GetComponent("Sprite").lock());
    sprite->Open(file);
    sprite->SetFrameCount(frameCount);
    sprite->SetFrameTime(frameTime);
    sprite->SetFlip(flip);
    associated.box.SetCenter(center);
}

void Player::SetCollider(SDL_Color color, bool active) {
    std::shared_ptr<Collider> collider = std::static_pointer_cast<Collider>(associated.GetComponent("Collider").lock());
    if (collider != nullptr) {
        collider->SetColor(color);
        collider->active = active;
    }
}

int Player::GetPlayerHp() {
    return this->hp;
}

void Player::NotifyCollision(GameObject& other) {
    if(other.GetComponent("Enemy").lock() && state != DAMAGED && state != DODGING) {
        auto enemy = std::static_pointer_cast<Enemy>(other.GetComponent("Enemy").lock());
        if(enemy->GetState() == Enemy::EnemyState::ATTACKING) {
            enemy->SetCollider(COLOR_GREEN,false);
            SetPlayerState(DAMAGED);
        }
    } else if(other.GetComponent("Obstacle").lock() && state != ATTACKING) {
        auto obstacle = std::static_pointer_cast<Obstacle>(other.GetComponent("Obstacle").lock());
        Rect box = obstacle->GetColliderBox();

        switch (obstacle->GetFace(associated.box)) {
            case Obstacle::Face::TOP:
                if(associated.box.y + associated.box.h > box.y) {
                    associated.box.y = box.y - associated.box.h;
                }
                break;
            case Obstacle::Face::RIGHT:
                if(associated.box.x < box.x + box.w) {
                    associated.box.x = box.x + box.w;
                }
                break;
            case Obstacle::Face::BOTTOM:
                if(associated.box.y < box.y + box.h) {
                    associated.box.y = box.y + box.h;
                }
                break;
            case Obstacle::Face::LEFT:
                if(associated.box.x + associated.box.w > box.x) {
                    associated.box.x = box.x - associated.box.w;
                }
                break;
            default:
                break;
        }
    }
}