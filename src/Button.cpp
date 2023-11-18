#include "Game.h"
#include "Text.h"
#include "Button.h"
#include "Sprite.h"
#include "Vec2.h"
#include <memory>

Button::Button(Vec2 vetor, std::string buttonPath, std::string name) : blinkingText(false), name(name){
    
    GameObject *imageObj = new GameObject();
    this->buttonImage = std::make_shared<Sprite>(*imageObj, "resources/img/MenuButton.png");
    imageObj->AddComponent(buttonImage);
    imageObj->box.x = vetor.x;
    imageObj->box.y = vetor.y;

    GameObject *textObj = new GameObject();
    this->text = std::make_shared<Text>(*textObj, std::string("resources/font/Base.ttf"), 32, TextStyle::BLENDED, std::string(name), SDL_Color{200, 200, 200}, SDL_Color{0, 0, 0}, blinkingText);

    textObj->AddComponent(this->text);
    textObj->box.x = vetor.x + (imageObj->box.w)/4;
    textObj->box.y = vetor.y + (imageObj->box.h)/8;
    Game::GetInstance().GetCurrentState().AddObject(imageObj);
    Game::GetInstance().GetCurrentState().AddObject(textObj);
}

void Button::UnChoose(){
    buttonImage->UnSetFocus();
    text->blinking = false;
    text->SetColorA({255, 255, 255});
}
void Button::Choose(){
    buttonImage->SetFocus(1.125f, 1.25f);
    text->blinking = true;
    text->SetColorA({255, 255, 0});
}

Button::~Button() = default;