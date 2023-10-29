#ifndef Attack_h_
#define Attack_h_

#include <GameObject.h>

class Attack: public Component {
    public:
        Attack(GameObject& associated,int damage,bool friendly = false, float duration = 0,float speed = 0 );
        Attack(GameObject& associated,int damage,std::string file,bool friendly = false, float speed = 0, float duration = 0,int frameCount = 1, float frameTime = 0);

        ~Attack();

        void Update(float dt);
        void Render();
        bool Is(std::string type);

        int GetDamage();
        bool IsFriendly();
    private:
        int damage;
        Vec2 speed;
        bool friendly;

        Timer attackTimer;
        float duration;
};
#endif