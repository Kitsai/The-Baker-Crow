#ifndef Player_h_
#define Player_h_

#include "GameObject.h"
#include "Collider.h"

class Player: public Component {
    public:
        Player(GameObject& associated);
        ~Player();

        virtual void Render();
        virtual bool Is(std::string type);

        enum PlayerState {STANDING, WALKING, ATTACKING, DODGING};

        static Player* player;

        bool IsInTile(int index,Vec2 pos, int tileSize = 64);
        bool IsInTile(Vec2 pos,int tileSize = 64);
        bool IsInTile(int index);

    protected:
        PlayerState state;
        char hp;
        Timer playerTimer;
        Vec2 speed;

        PlayerState GetPlayerState();
}; 

#endif