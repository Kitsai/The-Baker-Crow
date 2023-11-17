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
        
        void Choose();
        void UnChoose();

        bool blinkingText;
        std::string name;
    
    private:
        std::shared_ptr<Text> text;
        std::shared_ptr<Sprite> buttonImage;
};
#endif