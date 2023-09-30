#include <Sprite.h>

#include <Game.h>
#include <Resources.h>

#include <iostream>
#include <algorithm>

/// @brief 
/// Basic constructor for sprite.
/// Initializes texture as nullptr.
Sprite::Sprite(GameObject& assoc, int frameCount, float frameTime,float secondsToSelfDestruct): Component(assoc)  {
    texture = nullptr;
    scale = {1,1};
    this->frameCount = frameCount;
    currentFrame = 0;
    timeElapsed = 0;
    this->frameTime = frameTime;
    this->secondsToSelfDestruct = secondsToSelfDestruct;
}

/// @brief 
/// Parametrized constructor for Sprite.
/// Links the basic constructor and opens the given file.
/// @param file 
/// Path to sprite file.
Sprite::Sprite(GameObject& assoc, std::string file, int frameCount, float frameTime, float secondsToSelfDestruct): Sprite(assoc,frameCount,frameTime,secondsToSelfDestruct) {
    Open(file);
}

Sprite::~Sprite() {

}

/// @brief Opens the given file with the Resource Manager and gets its width and height.
/// @param file Path to image file.
void Sprite::Open(std::string file) {

    texture = Resources::GetImage(file);

    if(!IsOpen()) {
        std::cout << "Error Sprite:24 -  " << SDL_GetError() << std::endl;
        exit(-1);
    }
    if(SDL_QueryTexture(texture.get(), nullptr, nullptr, &width, &height) != 0) {
        std::cout << "Error Sprite:29 - " << SDL_GetError() << std::endl;
        exit(-1);
    }
    SetClip(0,0,width/frameCount,height);
    associated.box.w = width/frameCount;
    associated.box.h = height;
}

/// @brief Sets the sprite clip with custom values.
/// @param x Position on x axis.
/// @param y Position on y axis.
/// @param w Image width.
/// @param h Image height.
void Sprite::SetClip(int x, int y, int w, int h) {
    clipRect.x = x;
    clipRect.y = y;
    clipRect.w = w;
    clipRect.h = h;
}

/// @brief Renders the image with the position on the asociated game object.
void Sprite::Render() {
    Render(associated.box.x-Camera::pos.x, associated.box.y-Camera::pos.y);
}

/// @brief Renders the image with the full width and height and in a custom position.
/// @param x Position on the x axis.
/// @param y Position on the y axis.
void Sprite::Render(int x, int y) {
    Render(x,y,(width*scale.x)/frameCount,height*scale.y);
}

/// @brief Renders the image with custom positions and custom size.
/// @param x Position on x axis.
/// @param y Position on y axis.
/// @param w Render width.
/// @param h Render height.
void Sprite::Render(int x, int y, int w, int h) {
    SDL_Rect dstrect;
    dstrect.x = x;
    dstrect.y = y;
    dstrect.w = w;
    dstrect.h = h;

    if(IsOpen()) {
        if(SDL_RenderCopyEx(Game::GetInstance().GetRenderer(),texture.get(),&clipRect,&dstrect,associated.angleDeg*(180/M_PI),nullptr,SDL_FLIP_NONE) != 0) {
            std::cout << "Error Sprite:54 - " << SDL_GetError() << std::endl;
            exit(-1);
        }
    }
    else {
        std::cout << "Error Sprite:57 -  " << SDL_GetError() << std::endl;
        exit(-1);
    }
}

/// @brief Getter for width.
/// @return int corresponding to image width.
int Sprite::GetWidth() {
    return (width*scale.x)/frameCount;
}

/// @brief Getter for height.
/// @return int corresponding to image height.
int Sprite::GetHeight() {
    return height*scale.y;
}

/// @brief Checks if the imaage file has been opened.
/// @return true if the file is already open.
bool Sprite::IsOpen() {
    if(texture == nullptr) 
        return false;
    return true;
}

void Sprite::Update(float dt) {
    timeElapsed += dt;
    if(timeElapsed > frameTime) {
        currentFrame = (currentFrame+1 == frameCount)? 0:(currentFrame+1); 
        timeElapsed -= frameTime;
    }

    clipRect.x = currentFrame * (width/frameCount);

    if(secondsToSelfDestruct > 0 ) {
        selfDestructCount.Update(dt);
        if(selfDestructCount.Get() > secondsToSelfDestruct) 
            associated.RequestDelete();
    }
    
}

/// @brief 
/// Returns whether the object is of a certain type.
/// @param type 
/// Type to be checked.
/// @return 
/// True if type matches with the passed argument.
bool Sprite::Is(std::string type) {
    if(type == "Sprite") 
        return true;
    else
        return false; 
}

void Sprite::SetScale(Vec2 scale) {
    SetScale(scale.x,scale.y);
}

void Sprite::SetScale(float scaleX, float scaleY) {
    scale.x = (scaleX==0)? scale.x:scaleX;
    scale.y = (scaleY==0)? scale.y:scaleY;
    Vec2 center = associated.box.GetCenter();
    associated.box.w *= scale.x;
    associated.box.h *= scale.y;
    associated.box.SetCenter(center);
}

Vec2 Sprite::GetScale() {
    return scale;
}

void Sprite::SetFrame(int frame) {
    currentFrame = frame;
    clipRect.x = frame*(width/frameCount);
}

void Sprite::SetFrameCount(int frame) {
    frameCount = frame;
    currentFrame = 0;
    associated.box.w = width/frameCount; 
}

void Sprite::SetFrameTime(float frameTime) {
    this->frameTime = frameTime;
}