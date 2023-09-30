#ifndef CameraFollower_h_
#define CameraFollower_h_

#include <GameObject.h>
#include <Camera.h>

class CameraFollower: public Component {
    public:
        CameraFollower(GameObject& go);

        void Update(float dt);
        void Render();
        bool Is(std::string type);
};

#endif