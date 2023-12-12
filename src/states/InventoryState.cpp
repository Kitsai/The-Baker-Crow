#include "states/InventoryState.h"

InventoryState::InventoryState(): State(){

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
    
    std::vector <std::tuple<bool, std::string, Vec2>> ingredients = {
        {GameData::hasButter, "resources/img/ingredients/manteiga.png", Vec2(478, 190)},
        {GameData::hasChoco, "resources/img/ingredients/chocolate.png", Vec2(605, 202)},
        {GameData::hasEggs, "resources/img/ingredients/ovo.png", Vec2(725, 202)},
        {GameData::hasHoney, "resources/img/ingredients/mel.png", Vec2(478, 328)},
        {GameData::hasMilk, "resources/img/ingredients/leite.png", Vec2(605, 324)},
        {GameData::hasSugar, "resources/img/ingredients/acucar.png", Vec2(728, 323)},
        {GameData::hasWheat, "resources/img/ingredients/trigo.png", Vec2(500, 471)},
        {GameData::hasStraw, "resources/img/ingredients/morango.png", Vec2(703, 456)}
    };

    for (std::vector<int>::size_type i = 0; i < ingredients.size(); i++) {
        if (std::get<0>(ingredients[i])) {
            
            GameObject* obj = new GameObject();
            obj->AddComponent(new Sprite(*obj, std::get<1>(ingredients[i])));
            obj->box = std::get<2>(ingredients[i]);;
            
            AddObject(obj);
        }
    }
}