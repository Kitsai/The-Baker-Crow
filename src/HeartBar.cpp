#include "Game.h"
#include "Player.h"
#include "HeartBar.h"

HeartBar::Heart::Heart(GameObject& associated, Sprite* sprite, Vec2 pos, bool visible, HeartBar* bar) : 
                       GoHeart(&associated), spriteHeart(sprite), visible(visible), bar(bar) {
    
    GoHeart->box.x = pos.x;
    GoHeart->box.y = pos.y;
}


void HeartBar::Heart::Update(int i) {
    if(!visible){
        spriteHeart = nullptr;
    }else{
        spriteHeart = new Sprite(*this->GoHeart, "resources/img/HEART.png");
    }
    this->GoHeart->box.x = bar->associated->box.x + 125 + 55*i;
    this->GoHeart->box.y = bar->associated->box.y + 60;
}

HeartBar::HeartBar(GameObject& associated) : Component(associated), sprite(nullptr), associated(&associated) {
    sprite = new Sprite(associated, "resources/img/HEALTH_BAR.png");
    associated.AddComponent(sprite);
    CreateHearts(3, "resources/img/HEART.png");
}

void HeartBar::CreateHearts(int initialHealth, const std::string& heartSpriteFile) {
    Vec2 startPos = Player::player->GetPlayerPos();
    
    for (int i = 0; i < initialHealth; ++i) {
        GameObject* heartObj = new GameObject();

        Sprite* heartSprite   = new Sprite(*heartObj, heartSpriteFile);
        heartObj->AddComponent(heartSprite);

        Heart* heart = new Heart(*heartObj, heartSprite, startPos, true, this);
        
        startPos.x += 50;
        
        hearts.push_back(heart);
        Game::GetInstance().GetCurrentState().AddObject(heartObj);
    }
}

bool HeartBar::Is(std::string type){
    return type =="HeartBar";
}

void HeartBar::Update(float dt) {
    int playerLife = Player::player->GetPlayerHp();
    Vec2 playerPos = Player::player->GetPlayerPos();
    
    this->associated->box.x = playerPos.x;
    this->associated->box.y = playerPos.y;

    for (std::vector<int>::size_type i = 0; i < hearts.size(); ++i) {
        hearts[i]->visible = ((int) i < playerLife);
    }

    for (std::vector<int>::size_type i = 0; i < hearts.size(); i++) {
        hearts[i]->Update(i);
    }
}

void HeartBar::Render(){

}