#ifndef Sprite_h_
#define Sprite_h_

#include "SDL2/SDL_image.h"
#include <Rect.h>
#include <string>
#include <GameObject.h>
#include <Timer.h>

/// @brief An image component.
class Sprite: public Component {
    private:
        std::shared_ptr<SDL_Texture> texture;

        int width;
        int height;
        SDL_Rect clipRect;

        int frameCount;
        int currentFrame;
        float timeElapsed;
        float frameTime;

        Vec2 scale;

        Timer selfDestructCount;
        float secondsToSelfDestruct;
    public:
        Sprite(GameObject& assoc, int frameCount = 1, float frameTime = 1, float secondsToSelfDestruct = 0);
        Sprite(GameObject& assoc, std::string file, int frameCount = 1, float frameTime = 1, float secondsToSelfDestruct = 0);
        ~Sprite();

        void SetFrame(int frame);
        void SetFrameCount(int frame);
        void SetFrameTime(float frameTime);

        void Open(std::string file);
        void SetClip(int x, int y, int w, int h);

        void Render();
        void Render(int x, int y);
        void Render(int x, int y, int w, int h);

        int GetWidth();
        int GetHeight();

        void SetScale(Vec2 scale);
        void SetScale(float scaleX, float scaleY);
        Vec2 GetScale();

        bool IsOpen(); 
        void Update(float dt);   
        bool Is(std::string type);  
};

#endif