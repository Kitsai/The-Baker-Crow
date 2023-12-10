#ifndef HEART_BAR_H
#define HEART_BAR_H

#include <vector>
#include "GameObject.h"
#include "Sprite.h"
#include "Vec2.h"

class HeartBar : public Component {
public:
    HeartBar(GameObject& associated);
    ~HeartBar();

    void Render();
    void Update(float dt);
    bool Is(std::string type);

private:
    
    class Heart {
    public:
        Heart(GameObject& associated, Sprite* sprite, bool visible, HeartBar* bar);
        ~Heart();
        void Update(int i);
        
        GameObject* GoHeart;
        bool visible;

    private:
        HeartBar* bar;
    };

    GameObject* associated;
    std::vector<Heart*> hearts;
    void CreateHearts(int initialHealth, const std::string& heartSpriteFile);
};

#endif
