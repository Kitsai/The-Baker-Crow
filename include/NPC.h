#ifndef NPC_h_
#define NPC_h_

#include "GameObject.h"
#include "Sprite.h"
#include "defines/DefineMovement.h"
#include  "InputManager.h"
#include "GameData.h"

class NPC : public Component {
    public:
        NPC(GameObject& associated, std::string file, int type = 0);
        ~NPC();

        void Update(float dt);
        void Render();
        bool Is(std::string type);

        void Text(std::string text);
        void WalkIn();
        void WalkOut();

        enum NPCState {MOVING, IDLE};
        NPCState GetState();
    private:
        std::string file;
        int type;

        NPCState state;

        Vec2 moveTarget;
        float speed;
        float moveAngle;

        void Move(float dt);  
        void CalcSpeed(float dt);

        void SetState(NPCState state);
        void ChangeSprite(std::string file, int frameCount = 1, float frameTime = 1);

        enum faceDirectionEnum {UP, DOWN, LEFT, RIGHT};
        faceDirectionEnum faceDirection;

        void Request();
};

#endif