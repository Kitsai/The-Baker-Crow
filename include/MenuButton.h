#ifndef MenuButton_H
#define MenuButton_H

#include "GameObject.h"
#include "Sprite.h"
#include "Text.h"
#include "Component.h"
#include <string>
#include <memory>
#include "Vec2.h"
#include "defines/DefineColor.h"

class MenuButton {
    public:
        MenuButton(Vec2 vec, std::string buttonPath, std::string name);
        ~MenuButton();
        void Update(float dt);
        void Render();
        
        void Choose();
        void UnChoose();

        bool blinkingText;
        std::string name;
    
    private:
        std::weak_ptr<GameObject> textObj;
        Text* text;

        std::weak_ptr<GameObject> imageObj;
        Sprite* buttonImage;
};
#endif