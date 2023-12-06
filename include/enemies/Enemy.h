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
        Enemy(GameObject& associated,int hp = 100);

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
    protected:
        enum EnemyState {MOVING, ATTACKING, IDLE, DAMAGED};

        int hp;
        EnemyState state;

        Vec2 moveTarget;
        float speed;
        float moveAngle;
                                                                                                                    
        Timer timer;
        float idleTime;

        std::weak_ptr<GameObject> attack;

        void virtual Defeated();

        void virtual Move(float dt) = 0;  
        void virtual CalcSpeed(float dt) = 0;

        void virtual Attk();
        
        void virtual SetState(EnemyState state) = 0;
        void virtual ChangeSprite(std::string file, int frameCount = 1, float frameTime = 1);
        // void virtual FlipSprite(SDL_RendererFlip flip);

        void virtual DeathAnimation() = 0;

        void virtual DropItems() = 0;
};

#endif