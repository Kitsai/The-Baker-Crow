#include "Sprite.h"

#include "Game.h"
#include "Resources.h"

#include <iostream>
#include <algorithm>

Sprite::Sprite(GameObject& assoc, int frameCount, float frameTime,float secondsToSelfDestruct): Component(assoc), alpha(255)  {
    texture = nullptr;
    scale = {1,1};
    this->frameCount = frameCount;
    currentFrame = 0;
    timeElapsed = 0;
    this->frameTime = frameTime;
    this->secondsToSelfDestruct = secondsToSelfDestruct;
    flip = SDL_FLIP_NONE;
}

Sprite::Sprite(GameObject& assoc, std::string file, int frameCount, float frameTime, float secondsToSelfDestruct): Sprite(assoc,frameCount,frameTime,secondsToSelfDestruct) {
    Open(file);
}

Sprite::~Sprite() {

}

void Sprite::SetFrame(int frame) {
    currentFrame = frame;
    clipRect.x = frame*(width/frameCount);
}

void Sprite::SetFrameCount(int frame) {
    frameCount = frame;
    currentFrame = 0;
    associated.box.w = ((double)width)/frameCount * scale.x;
    SetClip(0,0,width/frameCount,height); 
}

void Sprite::SetFrameTime(float frameTime) {
    this->frameTime = frameTime;
    timeElapsed = 0;
}

void Sprite::Open(std::string file) {

    texture = Resources::GetImage(file);

    if(!IsOpen()) {
        std::cout << "Error Sprite:24 -  " << SDL_GetError() << std::endl;
    }
    if(SDL_QueryTexture(texture.get(), nullptr, nullptr, &width, &height) != 0) {
        std::cout << "Error Sprite:29 - " << SDL_GetError() << std::endl;
    }
    SetClip(0,0,width/frameCount,height);
    associated.box.w = (((double)width)/frameCount) * scale.x;
    associated.box.h = height * scale.y;
}

void Sprite::SetClip(int x, int y, int w, int h) {
    clipRect.x = x;
    clipRect.y = y;
    clipRect.w = w;
    clipRect.h = h;
}

void Sprite::Render() {
    Render(associated.box.x-Camera::pos.x, associated.box.y-Camera::pos.y);
}

void Sprite::Render(int x, int y) {
    Render(x,y,(width*scale.x)/frameCount,height*scale.y);
}

void Sprite::Render(int x, int y, int w, int h) {
    SDL_Rect dstrect;
    dstrect.x = x;
    dstrect.y = y;
    dstrect.w = w;
    dstrect.h = h;

   if (IsOpen()) {

        SDL_SetTextureAlphaMod(texture.get(), alpha);

        if (SDL_RenderCopyEx(Game::GetInstance().GetRenderer(), texture.get(), &clipRect, &dstrect, associated.angleDeg * (180 / M_PI), nullptr, flip) != 0) {
            std::cout << "Error Sprite:54 - " << SDL_GetError() << std::endl;
        }
        SDL_SetTextureAlphaMod(texture.get(), 255);
    } else {
        std::cout << "Error Sprite:57 -  " << SDL_GetError() << std::endl;
    }
}


int Sprite::GetWidth() {
    return (width*scale.x)/frameCount;
}

int Sprite::GetHeight() {
    return height*scale.y;
}

void Sprite::SetFlip(SDL_RendererFlip flip) {
    this->flip = flip;
}

void Sprite::SetScale(Vec2 scale) {
    SetScale(scale.x,scale.y);
}

void Sprite::SetAlpha(Uint8 alpha){
    this->alpha = alpha;
}

void Sprite::SetScale(float scaleX, float scaleY){
    if (scaleX > 0){
        this->scale.x = scaleX;
        associated.box.w = (double)width/frameCount * scale.x;
    }
    if (scaleY > 0){
        this->scale.y = scaleY;
        associated.box.h = height * scale.y;
    }
}

void Sprite::SetFocus(float escalarX, float escalarY) {
    if (escalarX > 0 && escalarY > 0) {
        float difX = (associated.box.w - associated.box.w * escalarX) / 2.0f;
        float difY = (associated.box.h - associated.box.h * escalarY) / 2.0f;
        
        this->scale.x = escalarX;
        this->scale.y = escalarY;
        
        associated.box.w *= scale.x;
        associated.box.h *= scale.y;

        associated.box.x +=  difX;
        associated.box.y +=  difY;
    }
}

void Sprite::UnSetFocus() {
    if(scale.x != 0 && scale.y != 0){
    float originalW = associated.box.w / scale.x;
    float originalH = associated.box.h / scale.y;

    float difX = (originalW - associated.box.w) / 2.0f;
    float difY = (originalH - associated.box.h) / 2.0f;

    associated.box.w = originalW;
    associated.box.h = originalH;

    associated.box.x -= difX;
    associated.box.y -= difY;
    }
    this->scale.x = 1.0f;
    this->scale.y = 1.0f;
}

Vec2 Sprite::GetScale() {
    return scale;
}

bool Sprite::IsOpen() {
    if(!texture) 
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

bool Sprite::Is(std::string type) {
    if(type == "Sprite") 
        return true;
    else
        return false; 
}