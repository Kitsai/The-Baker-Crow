#ifndef UIButton_H
#define UIButton_H

#include "GameObject.h"
#include "Sprite.h"
#include "Text.h"
#include "Component.h"
#include <string>
#include <memory>
#include "Vec2.h"
#include "defines/DefineColor.h"

class UIButton {
    public:
        UIButton(Vec2 vec, std::string buttonPath, std::string name);
        ~UIButton();
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