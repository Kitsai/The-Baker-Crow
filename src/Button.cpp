#include "Game.h"
#include "Text.h"
#include "Button.h"
#include "Sprite.h"
#include "Vec2.h"
#include <memory>

Button::Button(Vec2 vetor, std::string buttonPath, std::string name, int size) : blinkingText(false), name(name), size(size){
    
    this->imageObj = new GameObject();
    this->buttonImage = new Sprite(*imageObj, buttonPath);
    this->imageObj->AddComponent(buttonImage);
    this->imageObj->box.x = vetor.x;
    this->imageObj->box.y = vetor.y;

    this->textObj = new GameObject();
    LoadTextSize();
    
    this->text = new Text(*textObj, std::string("resources/font/Base.ttf"), size, TextStyle::BLENDED, std::string(name), SDL_Color{255, 255, 255, 255}, SDL_Color{0, 0, 0, 0}, blinkingText);
    this->textObj->AddComponent(this->text);
    
    Game::GetInstance().GetCurrentState().AddObject(imageObj);
    Game::GetInstance().GetCurrentState().AddObject(textObj);
}

void Button::LoadTextSize(){
    this->textObj->box.x = this->imageObj->box.x + (imageObj->box.w)/6;
    this->textObj->box.y = this->imageObj->box.y + (imageObj->box.h)/8;
}

void Button::UnChoose(){
    buttonImage->UnSetFocus();
    text->blinking = false;
    LoadTextSize();
    text->SetColarandTextSize({255, 255, 255, 255}, size);
}
void Button::Choose(){
    buttonImage->SetFocus(1.125f, 1.125f);
    text->blinking = true;
    LoadTextSize();
    text->SetColarandTextSize({255, 255, 0, 255}, (int)(size*1.25));
}

Button::~Button() = default;