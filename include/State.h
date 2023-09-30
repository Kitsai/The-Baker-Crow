#ifndef State_h_
#define State_h_

#include <memory>
#include <vector>
#include <Sprite.h>
#include <GameObject.h>
#include <Music.h>
#include <Sound.h>
#include <TileMap.h>
#include <CameraFollower.h>
#include <Text.h>



class State {
    protected:
        bool popRequested;
        bool quitRequested;
        bool started;

        std::vector<std::shared_ptr<GameObject>> objectArray;

        void StartArray();
        virtual void UpdateArray(float dt);
        virtual void RenderArray();

        public:
            State();
            ~State();

            virtual void LoadAssets() = 0;
            virtual void Update(float dt) = 0;
            virtual void Render() = 0;

            virtual void Start() = 0;
            virtual void Pause() = 0;
            virtual void Resume() = 0;

            virtual std::weak_ptr<GameObject> AddObject(GameObject* go);
            virtual std::weak_ptr<GameObject> GetObjectPtr(GameObject* go);

            bool PopRequested();
            bool QuitRequested();
};

#endif