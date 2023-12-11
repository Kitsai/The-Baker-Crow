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

        enum PlayerState {STANDING, WALKING, ATTACKING, DODGING, DAMAGED};

        static Player* player;

        bool IsInTile(int index,Vec2 pos, int tileSize = 64);
        bool IsInTile(Vec2 pos,int tileSize = 64);
        bool IsInTile(int index);

        Vec2 GetPlayerPos();
        Vec2 GetPlayerCenterPos();
        int GetPlayerHp();
        PlayerState GetPlayerState(); 

        void virtual NotifyCollision(GameObject& other);
    protected:
        int hp;
        Timer playerTimer;
        Vec2 speed;


        void virtual SetPlayerState(PlayerState state);
        void ChangeSprite(std::string file, float frameCount, float frameTime, SDL_RendererFlip flip = SDL_FLIP_NONE);
        void SetCollider(SDL_Color color = COLOR_RED, bool active = true);

    private:
        PlayerState state;
}; 

#endif