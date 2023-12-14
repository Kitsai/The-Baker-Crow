#include "Game.h"
#include "Text.h"
#include "Button.h"
#include "Sprite.h"
#include "Vec2.h"
#include <memory>


Button::Button(Vec2 vetor, std::string buttonPath) : blinkingText(false){
    
    this->imageObj = new GameObject();
    this->buttonImage = new Sprite(*imageObj, buttonPath);
    this->imageObj->AddComponent(buttonImage);
    this->imageObj->box.x = vetor.x;
    this->imageObj->box.y = vetor.y;

    Game::GetInstance().GetCurrentState().AddObject(imageObj);
}

Button::Button(Vec2 vetor, std::string buttonPath, std::string name, bool hasText) : Button(vetor, buttonPath){
    this->name = name;
    this->text      =nullptr;
    this->textObj   = nullptr;
}

Button::Button(Vec2 vetor, std::string buttonPath, std::string name, int size) : Button(vetor, buttonPath){
    this->name= name;
    this->size = size;
    
    this->textObj = new GameObject();
    LoadTextSize();
    
    this->text = new Text(*textObj, std::string("resources/font/Base.ttf"), size, TextStyle::BLENDED, std::string(name), SDL_Color{255, 255, 255, 255}, SDL_Color{0, 0, 0, 0}, blinkingText);
    this->textObj->AddComponent(this->text);
    
    Game::GetInstance().GetCurrentState().AddObject(textObj);
}

void Button::LoadTextSize(){
    this->textObj->box.x = this->imageObj->box.x + (imageObj->box.w)*0.16;
    this->textObj->box.y = this->imageObj->box.y + (imageObj->box.h)*0.125;
}

void Button::UnChoose(){
    buttonImage->UnSetFocus();
    if(text){
        text->blinking = false;
        LoadTextSize();
        text->SetColarandTextSize({255, 255, 255, 255}, size);
    }
}
void Button::Choose(){
    buttonImage->SetFocus(1.125f, 1.125f);
    if(text){
        text->blinking = true;
        LoadTextSize();
        text->SetColarandTextSize({255, 255, 0, 255}, (int)(size*1.25));
    }
}