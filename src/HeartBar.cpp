#include "Game.h"
#include "Player.h"
#include "HeartBar.h"
#include "CameraFollower.h"

HeartBar::Heart::Heart(GameObject& associated, Sprite* sprite, bool visible, HeartBar* bar) : 
                       GoHeart(&associated), visible(visible), bar(bar) {
    GoHeart->AddComponent(new CameraFollower(*GoHeart));
    GoHeart->AddComponent(new Sprite(*this->GoHeart, "resources/img/HEART_DEAD.png"));

    GameObject* inventory = new GameObject();
    inventory->box = Vec2(1180, -25);
    inventory->AddComponent(new CameraFollower(*inventory));
    inventory->AddComponent(new Sprite(*inventory,"resources/img/inventory_icon.png"));

    Game::GetInstance().GetCurrentState().AddObject(inventory);
}
HeartBar::Heart::~Heart(){
    this->GoHeart = nullptr;
}

void HeartBar::Heart::Update(int i) {
    if (Player::player->GetPlayerHp() <= i) {
        std::weak_ptr<Component> weakSpriteComponent = GoHeart->GetComponent("Sprite");
        std::shared_ptr<Component> sharedSpriteComponent = weakSpriteComponent.lock();
        if (sharedSpriteComponent) {
            GoHeart->RemoveComponent(sharedSpriteComponent.get());
        }
        GoHeart->AddComponent(new Sprite(*this->GoHeart, "resources/img/HEART_DEAD.png"));
        this->visible = true;

    } else {
        if (visible) {
            std::weak_ptr<Component> weakSpriteComponent = GoHeart->GetComponent("Sprite");
            std::shared_ptr<Component> sharedSpriteComponent = weakSpriteComponent.lock();

            if (sharedSpriteComponent) {
                GoHeart->RemoveComponent(sharedSpriteComponent.get());
            }
            GoHeart->AddComponent(new Sprite(*this->GoHeart, "resources/img/HEART.png"));

            this->visible = false;
        }
    }
}
HeartBar::HeartBar(GameObject& associated) : Component(associated), associated(&associated) {
    associated.AddComponent(new Sprite(associated, "resources/img/HEALTH_BAR.png"));
    associated.AddComponent(new CameraFollower(associated));
    CreateHearts(3, "resources/img/HEART.png");
}

HeartBar::~HeartBar() {
    this->associated = nullptr;
    hearts.clear();
}

void HeartBar::CreateHearts(int initialHealth, const std::string& heartSpriteFile) {
    for (int i = 0; i < initialHealth; ++i) {
        GameObject* heartObj = new GameObject();
        heartObj->box = Vec2(125+ i*55, 60);
        Sprite* heartSprite   = new Sprite(*heartObj, heartSpriteFile);

        Heart* heart = new Heart(*heartObj, heartSprite, true, this);
        
        hearts.push_back(heart);
        Game::GetInstance().GetCurrentState().AddObject(heartObj);
    }
}

void HeartBar::Update(float dt) {
    if(Player::player){
        for (std::vector<int>::size_type i = 0; i < hearts.size(); i++) {
            hearts[i]->Update(i);
        }
    }
}

bool HeartBar::Is(std::string type){
    return type =="HeartBar";
}

void HeartBar::Render(){}