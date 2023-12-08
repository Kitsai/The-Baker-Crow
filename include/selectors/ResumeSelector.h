#ifndef ResumeSelector_H
#define ResumeSelector_H

#include <vector>
#include "Button.h"
#include "Component.h"

class ResumeSelector{
public:
    ResumeSelector();
    ~ResumeSelector();

    int GetSelected();
    void Update(float dt);
    
    private:
        int selected;
        std::shared_ptr<Button> selectedButton;
        
        int nButtons;
        std::vector<std::shared_ptr<Button>> buttons;
};

#endif