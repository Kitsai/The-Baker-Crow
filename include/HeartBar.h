#ifndef HEART_BAR_H
#define HEART_BAR_H

#include <vector>
#include "GameObject.h"
#include "Sprite.h"
#include "Vec2.h"

class HeartBar : public Component {
public:
    HeartBar(GameObject& associated);

    void Render();
    void Update(float dt);
    bool Is(std::string type);

private:
    
    class Heart {
    public:
        Heart(GameObject& associated, Sprite* sprite, Vec2 pos, bool visible, HeartBar* bar);
        void Update(int i);
        
        GameObject* GoHeart;
        Sprite* spriteHeart;
        bool visible;

    private:
        HeartBar* bar;
    };

    Sprite* sprite;
    GameObject* associated;
    std::vector<Heart*> hearts;
    void CreateHearts(int initialHealth, const std::string& heartSpriteFile);
};

#endif
