#include "Game.h"
#include "Player.h"
#include "HeartBar.h"

HeartBar::Heart::Heart(GameObject& associated, Sprite* sprite, Vec2 pos, bool visible, HeartBar* bar) : 
                       GoHeart(&associated), spriteHeart(sprite), visible(visible), bar(bar) {
    
    GoHeart->box.x = pos.x;
    GoHeart->box.y = pos.y;
}

HeartBar::Heart::~Heart() {
    delete GoHeart;
}

void HeartBar::Heart::Update(int i) {
    if(!visible){
        spriteHeart = nullptr;
    }else{
        spriteHeart = new Sprite(*this->GoHeart, "resources/img/HEART.png");
    }
    this->GoHeart->box.x = bar->associated->box.x + 50*i;
    this->GoHeart->box.y = bar->associated->box.y;
}

HeartBar::HeartBar(GameObject& associated) : Component(associated), associated(&associated), sprite(nullptr) {
    sprite = new Sprite(associated, "resources/img/HEALTH_BAR.png");
    CreateHearts(3, "resources/img/HEART.png");
}

HeartBar::~HeartBar() {
    delete sprite;
    for (auto& heart : hearts) {
        delete heart;
    }
}

void HeartBar::CreateHearts(int initialHealth, const std::string& heartSpriteFile) {
    Vec2 startPos = Player::player->GetPlayerPos();
    
    for (int i = 0; i < initialHealth; ++i) {
        GameObject* heartObj = new GameObject();
        Sprite* heartSprite   = new Sprite(*heartObj, heartSpriteFile);

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

    for (int i = 0; i < hearts.size(); ++i) {
        hearts[i]->visible = (i < playerLife);
    }

    for (int i; i < hearts.size(); i++) {
        hearts[i]->Update(i);
    }
}

void HeartBar::Render(){

}