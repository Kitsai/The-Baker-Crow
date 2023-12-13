#ifndef Tree_h_
#define Tree_h_

#include "Obstacle.h"

class Tree: public Obstacle {
    public: 
        Tree(GameObject& associated);
        ~Tree();

        bool Is(std::string type);

    private:
        void SetCollider();
};

#endif