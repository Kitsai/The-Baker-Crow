#include "Player.h"

#include "Game.h"

std::weak_ptr<GameObject> Player::player;

Player::Player(GameObject& associated): Component(associated) {
    hp = 100;
    state = STANDING;
    speed = {0,0};

    player = std::shared_ptr<GameObject>(&associated);

    Game& game = Game::GetInstance();
    associated.AddComponent(new Collider(associated));
}

Player::~Player() {

}

void Player::Render() {

}

bool Player::Is(std::string type) {
    return type == "Player";
}

// Vec2 Player::GetPlayerPos() {
//     return associated.box.GetCenter();
// }

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