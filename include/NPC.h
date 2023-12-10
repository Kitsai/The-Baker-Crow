#ifndef NPC_h_
#define NPC_h_

#include "GameObject.h"
#include "Sprite.h"

class NPC : public Component {
    public:
        NPC(GameObject& associated, std::string file);
        ~NPC();

        void Update(float dt);
        void Render();
        bool Is(std::string type);

        void Text(std::string text);
    private:
        std::string file;
};

#endif