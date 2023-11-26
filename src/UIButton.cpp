#include "Component.h"
#include "Game.h"
#include "UIButton.h"
#include <memory>


UIButton::UIButton(Vec2 vetor, std::string buttonPath, std::string name) : blinkingText(false), name(name){
    
    GameObject* tempImageObj = new GameObject();
    tempImageObj->AddComponent(new Sprite(*tempImageObj, buttonPath));
    tempImageObj->box = vetor;

    GameObject* tempTextObj = new GameObject();
    tempTextObj->AddComponent(new Text(*tempTextObj, "resources/font/Base.ttf", 32, TextStyle::BLENDED, name, COLOR_WHITE, COLOR_BLACK, blinkingText));

    tempTextObj->box.x = vetor.x + (tempImageObj->box.w)*0.25F;
    tempTextObj->box.y = vetor.y + (tempImageObj->box.h)*0.125F;
    imageObj = Game::GetInstance().GetCurrentState().AddObject(tempImageObj);
    textObj = Game::GetInstance().GetCurrentState().AddObject(tempTextObj);
}

void UIButton::UnChoose(){
    if(textObj.expired() || imageObj.expired()){
        return;
    }

    std::shared_ptr<GameObject> textObjPtr = textObj.lock();
    std::shared_ptr<GameObject> imageObjPtr = imageObj.lock();

    ((Sprite*)imageObjPtr->GetComponent("Sprite"))->UnSetFocus();

    textObjPtr->box.x = imageObjPtr->box.x + (imageObjPtr->box.w)*0.25F;
    textObjPtr->box.y = imageObjPtr->box.y + (imageObjPtr->box.h)*0.125F;
    
    Text* text = (Text*)textObjPtr->GetComponent("Text");
    text->blinking = false;
    text->SetColarandTextSize({255, 255, 255, 255}, 32);
}
void UIButton::Choose(){
    if(textObj.expired() || imageObj.expired()){
        return;
    }
    std::shared_ptr<GameObject> textObjPtr = textObj.lock();
    std::shared_ptr<GameObject> imageObjPtr = imageObj.lock();

    ((Sprite*)imageObjPtr->GetComponent("Sprite"))->SetFocus(1.125F, 1.25F);
    textObjPtr->box.x = imageObjPtr->box.x + (imageObjPtr->box.w)/4;
    textObjPtr->box.y = imageObjPtr->box.y;
    
        
    Text* text = (Text*)textObjPtr->GetComponent("Text");
    text->blinking = true;
    text->SetColarandTextSize({255, 255, 0, 255}, 48);
}

UIButton::~UIButton() = default;