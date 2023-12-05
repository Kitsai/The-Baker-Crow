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
    this->text = new Text(*textObj, std::string("resources/font/Base.ttf"), size, TextStyle::BLENDED, std::string(name), SDL_Color{255, 255, 255, 255}, SDL_Color{0, 0, 0, 0}, blinkingText);

    this->textObj->AddComponent(this->text);
    this->textObj->box.x = vetor.x + (imageObj->box.w)/4;
    this->textObj->box.y = vetor.y + (imageObj->box.h)/8;
    Game::GetInstance().GetCurrentState().AddObject(imageObj);
    Game::GetInstance().GetCurrentState().AddObject(textObj);
}

void Button::UnChoose(){
    buttonImage->UnSetFocus();
    this->textObj->box.x = this->imageObj->box.x + (this->imageObj->box.w)/4;
    this->textObj->box.y = this->imageObj->box.y + (this->imageObj->box.h)/8;
    
    text->blinking = false;
    text->SetColarandTextSize({255, 255, 255, 255}, 32);
}
void Button::Choose(){
    buttonImage->SetFocus(1.125f, 1.25f);
    this->textObj->box.x = this->imageObj->box.x + (this->imageObj->box.w)/4;
    this->textObj->box.y = this->imageObj->box.y;
    
    text->blinking = true;
    text->SetColarandTextSize({255, 255, 0, 255}, 48);
}

Button::~Button() = default;