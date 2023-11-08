#include "Item.h"
#include "FoodPiece.h"

Item::Item(std::string type) : amount(0), type(type), foodPiece(nullptr) {}

void Item::Increase() {
    amount++;
}

void Item::Decrease() {
    if (amount > 0)
        amount--;
}

void Item::SetFoodPiece(FoodPiece* foodPiece) {
    this->foodPiece = foodPiece;
}

FoodPiece* Item::GetFoodPiece() const {
    return foodPiece;
}
