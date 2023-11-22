#include "Component.h"
#include "Game.h"
#include "MenuButton.h"
#include <memory>


MenuButton::MenuButton(Vec2 vetor, std::string buttonPath, std::string name) : blinkingText(false), name(name){
    
    GameObject* tempImageObj = new GameObject();
    buttonImage = new Sprite(*tempImageObj, buttonPath);
    tempImageObj->AddComponent(buttonImage);
    tempImageObj->box = vetor;

    GameObject* tempTextObj = new GameObject();
    text = new Text(*tempTextObj, "resources/font/Base.ttf", 32, TextStyle::BLENDED, name, COLOR_WHITE, COLOR_BLACK, blinkingText);
    tempTextObj->AddComponent(text);

    tempTextObj->box.x = vetor.x + (tempImageObj->box.w)*0.25F;
    tempTextObj->box.y = vetor.y + (tempImageObj->box.h)*0.125F;
    imageObj = Game::GetInstance().GetCurrentState().AddObject(tempImageObj);
    textObj = Game::GetInstance().GetCurrentState().AddObject(tempTextObj);
}

void MenuButton::UnChoose(){
    if(textObj.expired() || imageObj.expired()){
        return;
    }

    std::shared_ptr<GameObject> textObjPtr = textObj.lock();
    std::shared_ptr<GameObject> imageObjPtr = imageObj.lock();
    buttonImage->UnSetFocus();
    textObjPtr->box.x = imageObjPtr->box.x + (imageObjPtr->box.w)*0.25F;
    textObjPtr->box.y = imageObjPtr->box.y + (imageObjPtr->box.h)*0.125F;
    
    text->blinking = false;
    text->SetColarandTextSize({255, 255, 255, 255}, 32);
}
void MenuButton::Choose(){
    if(textObj.expired() || imageObj.expired()){
        return;
    }
    std::shared_ptr<GameObject> textObjPtr = textObj.lock();
    std::shared_ptr<GameObject> imageObjPtr = imageObj.lock();

    buttonImage->SetFocus(1.125f, 1.25f);
    textObjPtr->box.x = imageObjPtr->box.x + (imageObjPtr->box.w)/4;
    textObjPtr->box.y = imageObjPtr->box.y;
    
    text->blinking = true;
    text->SetColarandTextSize({255, 255, 0, 255}, 48);
}

MenuButton::~MenuButton() = default;