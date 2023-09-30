#ifndef Collider_h_
#define Collider_h_

#include <GameObject.h>
#include <string>

class Collider: public Component {
    private:
        Vec2 scale;
        Vec2 offset;
    
    public:
        Collider(GameObject& associated, Vec2 scale = {1,1},Vec2 offSet = {0,0});

        Rect box;

        void Update(float dt);
        void Render();
        bool Is(std::string type);

        void SetScale(Vec2 scale);
        void SetOffset(Vec2 offset);
};

#endif