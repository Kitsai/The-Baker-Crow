#ifndef Camera_h_
#define Camera_h_

#include <GameObject.h>
#include <defines/DefineMovement.h>
#include <defines/DefineInput.h>

class Camera {
    private:
        static GameObject* focus;

    public:
        static Vec2 pos;
        static Vec2 speed;

        static void Follow(GameObject* newFocus);
        static void Unfollow();
        static void Update(float dt);
};

#endif