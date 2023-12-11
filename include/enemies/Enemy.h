#ifndef Enemy_h_
#define Enemy_h_

#include "Component.h"

#include "Attack.h"
#include "Player.h"

#include "defines/DefinesInclude.h"

/// @brief Abstract class that identifies an Enemy.
class Enemy: public Component {
    public:
        /// @brief Constructor for Enemy.
        /// @param associated Object the component is part of.
        /// @param hp the enemy hp.
        Enemy(GameObject& associated, bool attacker, int hp = 100);

        /// @brief Destructor for Enemy.
        virtual ~Enemy();

        /// @brief Updates the component. If hp <= 0 request deletion.
        /// @param dt Delta Time.
        void virtual Update(float dt);
        /// @brief renders the component.
        void virtual Render();
        /// @brief Returns whether the object is of a certain type.
        /// @param type Type to be checked.
        /// @return True if type matches with the passed argument.
        bool virtual Is(std::string type);

        enum EnemyState {MOVING, ATTACKING, IDLE, DAMAGED};
        EnemyState GetState();
        
        void virtual NotifyCollision(GameObject& other);
        void virtual SetCollider(SDL_Color color, bool active = true);
    protected:

        int hp;
        EnemyState state;
        bool attacker;

        Vec2 moveTarget;
        float speed;
        float moveAngle;
                                                                                                                    
        Timer timer;
        float idleTime;

        void virtual Defeated();

        void virtual Move(float dt);  
        void virtual CalcSpeed(float dt) = 0;

        bool virtual Attk();
        
        void virtual SetState(EnemyState state);
        void virtual ChangeSprite(std::string file, int frameCount = 1, float frameTime = 1);
        void virtual ChangeSprite(std::string file, SDL_RendererFlip flip, int frameCount = 1, float frameTime = 1);


        void virtual DeathAnimation() = 0;

        void virtual DropItems() = 0;

};

#endif