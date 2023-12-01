#ifndef Enemy_h_
#define Enemy_h_

#include "GameObject.h"

/// @brief Abstract class that identifies an Enemy.
class Enemy: public Component {
    public:
        /// @brief Constructor for Enemy.
        /// @param associated Object the component is part of.
        /// @param hp the enemy hp.
        Enemy(GameObject& associated,int hp = 100);

        /// @brief Updates the component. If hp <= 0 request deletion.
        /// @param dt Delta Time.
        void virtual Update(float dt);
        /// @brief renders the component.
        void virtual Render() = 0;
        /// @brief Returns whether the object is of a certain type.
        /// @param type Type to be checked.
        /// @return True if type matches with the passed argument.
        bool Is(std::string type);
    private:
        int hp;
};

#endif