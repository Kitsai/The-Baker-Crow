#ifndef Enemy_h_
#define Enemy_h_

#include "GameObject.h"

#include "Sprite.h"

/// @brief Abstract class that identifies an Enemy.
class Enemy: public Component {
    public:
        /// @brief Constructor for Enemy.
        /// @param associated Object the component is part of.
        /// @param hp the enemy hp.
        Enemy(GameObject& associated,std::string file, int hp = 100);

        /// @brief Updates the component. If hp <= 0 request deletion.
        /// @param dt Delta Time.
        void virtual Update(float dt);
        /// @brief renders the component.
        void virtual Render();
        /// @brief Returns whether the object is of a certain type.
        /// @param type Type to be checked.
        /// @return True if type matches with the passed argument.
        virtual bool Is(std::string type);

        enum EnemyState {IDLE, MOVING, ATTACKING};

    protected:
        int hp;
        void virtual Defeated();
        void UpdateSprite(std::string file, int frameCount = 1, float frameTime = 1, float secondsToSelfDestruct = 0);
        
};

#endif