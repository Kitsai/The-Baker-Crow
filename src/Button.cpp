#include "Game.h"
#include "Button.h"
#include "Vec2.h"

Button::Button(Vec2 vetor, std::string buttonPath, std::string name) : blinkingText(false), name(name){
    
    GameObject *imageObj = new GameObject();
    this->buttonImage = new Sprite(*imageObj, "resources/img/MenuButton.png");
    imageObj->AddComponent((std::shared_ptr<Sprite>)  buttonImage);
    imageObj->box.x = vetor.x;
    imageObj->box.y = vetor.y;

    GameObject *textObj = new GameObject();
    this->texto = new Text(*textObj, "resources/font/Base.ttf", 32, TextStyle::BLENDED,name, {200, 200, 200},{0, 0, 0},  blinkingText);
    
    textObj->AddComponent((std::shared_ptr<Text>) this->texto);
    textObj->box.x = vetor.x;
    textObj->box.y = vetor.y;
    Game::GetInstance().GetCurrentState().AddObject(imageObj);
    Game::GetInstance().GetCurrentState().AddObject(textObj);
}

void Button::Choosed(){
    buttonImage->SetScale(1.5F);
}

Button::~Button() {
    
}