#include "HealthBar.h"
#include "CameraFollower.h"
#include "Component.h"
#include "GameObject.h"
#include "Game.h"
#include "Player.h"


HealthBar::HealthBar(GameObject& associated): Component(associated) {
    associated.AddComponent(new Sprite(associated, "resources/img/HEALTH_BAR.png"));
    associated.AddComponent(new CameraFollower(associated));
}

HealthBar::~HealthBar() {
    while(hearts.size()) hearts.pop();
}

void HealthBar::Update(float dt) {
    const int hp = (Player::player)? Player::player->GetPlayerHp():0;
    std::cout << "HP: " << hp << std::endl;
    std::cout << "Size: " << hearts.size() << std::endl;

    while(hp < (int)hearts.size() && hearts.size() > 0) {
        Game::GetInstance().GetCurrentState().RemoveObject(hearts.top().lock().get());
        hearts.pop();
    }
    while(hp > (int)hearts.size()) 
        AddHeart(hearts.size());
}

void HealthBar::Render() {
}

void HealthBar::Start() {
    for(int i=0;i<3;i++) {
        AddHeart(i);
    }
}

bool HealthBar::Is(std::string type) {
    return type == "HealthBar";
}

void HealthBar::AddHeart(int id) {
    State& state = Game::GetInstance().GetCurrentState();

    GameObject* go = new GameObject();
    go->box = Vec2(125 + 55*(id%3),60);
    go->AddComponent(new Sprite(*go, "resources/img/HEART.png"));
    go->AddComponent(new CameraFollower(*go));
    hearts.push(state.AddObject(go));
}