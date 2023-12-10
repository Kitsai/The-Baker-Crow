#include "selectors/MenuSelector.h"


MenuSelector::MenuSelector() : Selector(){
    
    Button* buttonNewGame = new Button(Vec2(500, 200),"resources/img/MenuButton.png", "NEW GAME",36);
    Button* buttonLoadGame = new Button(Vec2(500, 400),"resources/img/MenuButton.png", "LOAD GAME",36);
    Button* buttonExitGame = new Button(Vec2(500, 600),"resources/img/MenuButton.png", "EXIT GAME",36);

    buttons.push_back((std::shared_ptr<Button>) buttonNewGame);
    buttons.push_back((std::shared_ptr<Button>) buttonLoadGame);
    buttons.push_back((std::shared_ptr<Button>) buttonExitGame);

    selectedButton = buttons[0];
    selectedButton->Choose();
}

MenuSelector::~MenuSelector() {
    buttons.clear();
}