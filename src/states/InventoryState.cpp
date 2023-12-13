#include "states/InventoryState.h"

InventoryState::InventoryState(): State(), selector(nullptr){

    GameObject* titleObj = new GameObject();
    titleObj->box.x = 350;
    titleObj->box.y = 10;
    Sprite* titleImage = new Sprite(*titleObj, "resources/img/IngredientsBook.png");
    titleObj->AddComponent(titleImage);
    AddObject(titleObj);
}

InventoryState::~InventoryState(){
    objectArray.clear();
}

void InventoryState::Update(float dt){
    InputManager& iM = InputManager::GetInstance();

    if(iM.QuitRequested()) quitRequested = true;

    if (iM.KeyPress(ESCAPE_KEY)){
        popRequested = true;
    }
    else if(iM.KeyPress(ENTER_KEY)){
        popRequested = true;
    }
    
    for (int i = 0; i < (int) objectArray.size(); i++) {
        objectArray[i]->Update(dt);
    }
    if(selector){
        selector->Update(dt);
    }
    
}

void InventoryState::LoadAssets(){
}

void InventoryState::Render() {
    for (std::vector<int>::size_type i = 0; i < objectArray.size(); i++){
        objectArray[i]->Render();
    }
}

void InventoryState::Start(){
    Camera::pos.x = 0;
    Camera::pos.y = 0;
    LoadIngredients();
    for (int i = 0; i < (int)objectArray.size(); i++){
        objectArray[i]->Start();
    }
    started = true;
}

void InventoryState::Pause(){}

void InventoryState::Resume(){
}

void InventoryState::LoadIngredients() {

    std::stack<Vec2> positions;
    std::vector<std::shared_ptr<Button>> buttons;

    positions.push( Vec2(478, 190));
    positions.push( Vec2(605, 202));
    positions.push(Vec2(725, 202));
    positions.push(Vec2(478, 328));
    positions.push( Vec2(605, 324));
    positions.push(Vec2(728, 323));
    positions.push(Vec2(500, 471));
    positions.push(Vec2(703, 456));

    for(std::pair<bool, FoodItemType> item : GameData::ingredients ){
        if(item.first){
            Button* butter      = new Button(positions.top(), "resources/img/ingredients/"+foodItemTypeToString[item.second]+".png", false);
            buttons.push_back((std::shared_ptr<Button>) butter);
            positions.pop();
        }
    }
    if(buttons.size()){
        selector = std::make_unique<Selector>(buttons);
    }
}