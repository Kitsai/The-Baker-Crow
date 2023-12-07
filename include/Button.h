#ifndef Button_H
#define Button_H

#include "GameObject.h"
#include "Sprite.h"
#include "Text.h"
#include "Component.h"
#include <string>

class Button {
    public:
        Button(Vec2 vec, std::string buttonPath, std::string name, int size);
        ~Button();
        
        void Choose();
        void UnChoose();

        bool blinkingText;
        std::string name;
    
    private:
        GameObject* textObj;
        Text* text;

        GameObject* imageObj;
        Sprite* buttonImage;
        int size;
};
#endif