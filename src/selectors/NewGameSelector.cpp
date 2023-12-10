#include "selectors/NewGameSelector.h"

NewGameSelector::NewGameSelector() : Selector(){
    
    Button* buttonGame1 = new Button(Vec2(0, 300),"resources/img/MenuButton.png", "NEW GAME 1", 36);
    Button* buttonGame2 = new Button(Vec2(400, 300),"resources/img/MenuButton.png", "NEW GAME 2", 36);
    Button* buttonGame3 = new Button(Vec2(800, 300),"resources/img/MenuButton.png", "NEW GAME 3", 36);

    buttons.push_back((std::shared_ptr<Button>) buttonGame1);
    buttons.push_back((std::shared_ptr<Button>) buttonGame2);
    buttons.push_back((std::shared_ptr<Button>) buttonGame3);

    selectedButton = buttons[0];
    selectedButton->Choose();
}

NewGameSelector::~NewGameSelector() {
    buttons.clear();
}