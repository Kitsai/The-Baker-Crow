#include "Player.h"

#include "Game.h"

Player* Player::player = nullptr;

Player::Player(GameObject& associated): Component(associated) {
    hp = 100;
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
}

bool Player::IsInTile(Vec2 pos,int tileSize) {
    Rect box = associated.box;
    Vec2 points[] = {
        Vec2(box.x,box.y), //  0 - top left
        Vec2(box.x + box.w, box.y), // 1 - top right
        Vec2(box.x,box.y + box.h), // 2 - bottom left
        Vec2(box.x + box.w,box.y + box.h) // 3 - bottom right
    };

}

Player::PlayerState Player::GetPlayerState() {
    return state;
}