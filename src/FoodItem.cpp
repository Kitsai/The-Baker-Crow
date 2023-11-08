#include <memory>

#include "Game.h"
#include "FoodItem.h"
#include "Component.h"
#include "GameObject.h"
#include "FoodPiece.h"

FoodItem::FoodItem(GameObject& associated, std::string type) : Component(associated), amount(1), type(type) {

        GameObject* object_foodPiece = new GameObject();
        FoodPiece* foodPieceComponent = new FoodPiece(*object_foodPiece, *this);
        object_foodPiece->AddComponent((std::shared_ptr<FoodPiece>)foodPieceComponent);
        
        // Adiciona o FoodPiece ao estado do jogo
        //Game::GetInstance().GetState().AddObject(object_foodPiece);
}

void FoodItem::Increase() {
    amount++;
}

void FoodItem::Decrease() {
    if (amount > 0)
        amount--;
}

FoodPiece* FoodItem::GetFoodPiece() const {
    return foodPiece;
}

std::string FoodItem::GetType(){
    return this->type;
}

void FoodItem::Update(float dt){
    
}
void FoodItem::Render(){

}

bool FoodPiece::Is(std::string type) {
    return type == "FoodItem";
}