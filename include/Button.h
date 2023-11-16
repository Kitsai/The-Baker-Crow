#ifndef Button_H
#define Button_H

#include "Sprite.h"
#include "Text.h"
#include "Component.h"
#include <string>

class Button {
    public:
        Button(Vec2 vec, std::string buttonPath, std::string name);
        ~Button();
        
        bool blinkingText;
        std::string name;
        
        void Choosed();
    
    private:
        Text* texto;
        Sprite*  buttonImage;
};
#endif