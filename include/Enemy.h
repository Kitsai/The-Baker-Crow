#ifndef Enemy_h_
#define Enemy_h_

#include <GameObject.h>

class Enemy: public Component {
    public:
        Enemy(GameObject& associated);

        void virtual Update(float dt) = 0;
        void virtual Render() = 0;
        bool Is(std::string type);
};

#endif