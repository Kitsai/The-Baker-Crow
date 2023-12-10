#include "selectors/ResumeSelector.h"


ResumeSelector::ResumeSelector() : Selector(){
    Button* buttonResumeGame = new Button(Vec2(500, 180),"resources/img/ResumeButton.png", "Resume",36);
    Button* buttonSaveGame = new Button(Vec2(500, 290),"resources/img/ResumeButton.png", "Save Game", 36);
    Button* buttonExitsGame = new Button(Vec2(500, 400),"resources/img/ResumeButton.png", "Exit Game", 36);

    buttons.push_back((std::shared_ptr<Button>) buttonResumeGame);
    buttons.push_back((std::shared_ptr<Button>) buttonSaveGame);
    buttons.push_back((std::shared_ptr<Button>) buttonExitsGame);
    selectedButton = buttons[0];
    selectedButton->Choose();
}

ResumeSelector::~ResumeSelector() {
    buttons.clear();
}