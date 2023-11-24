#include <memory>

#include "Game.h"
#include "FoodItem.h"
#include "Component.h"
#include "GameObject.h"
#include "FoodPiece.h"

FoodItem::FoodItem(GameObject& associated, FoodItemType type) : Component(associated), amount(1), type(type) {


        GameObject* object_foodPiece = new GameObject();
        object_foodPiece->box.x = associated.box.x;
        object_foodPiece->box.y = associated.box.y;
        FoodPiece* foodPieceComponent = new FoodPiece(*object_foodPiece, *this);
        object_foodPiece->AddComponent((std::shared_ptr<FoodPiece>)foodPieceComponent);
        this->foodPiece = foodPieceComponent;  
        
        Game::GetInstance().GetCurrentState().AddObject(object_foodPiece);

}

void FoodItem::Increase() {
    amount++;
}

void FoodItem::Decrease() {
    if (amount > 0)
        amount--;
}

FoodPiece* FoodItem::GetFoodPiece() {
    return foodPiece;
}

FoodItemType FoodItem::GetType(){
    return this->type;
}

void FoodItem::Update(float dt){
    
}
void FoodItem::Render(){

}

bool FoodItem::Is(std::string type) {
    return type == "FoodItem";
}