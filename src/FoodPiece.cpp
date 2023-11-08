#include "FoodPiece.h"
#include "Item.h"

FoodPiece::FoodPiece(GameObject& associated, std::string type) 
    : Component(associated), item(nullptr), locked(false), type(type) {
    evaluateForm();
}

FoodPiece::~FoodPiece() {
}

void FoodPiece::Render() {
}

void FoodPiece::Update(float dt) {
}

void FoodPiece::SetItem(Item* item) {
    this->item = item;
}

Item* FoodPiece::GetItem() {
    return item;
}

std::string FoodPiece::GetType() {
    return type;
}

bool FoodPiece::Lock() {
    locked = true;
    return locked;
}

bool FoodPiece::UnLock() {
    locked = false;
    return !locked;
}

bool FoodPiece::Is(std::string type) {
    return this->type == type;
}

std::vector<std::vector<int>> FoodPiece::GetForm() {
    return form;
}

void FoodPiece::evaluateForm(){    
    if (type == "ovo")
        form = {{1, 1, 1, 1}};
    
    else if (type == "morango")
        form = {{1, 0},{1, 0},{1, 1}};

    else if (type == "c4oc") 
        form = {{1, 0},{1, 1},{0, 1}};

    else if (type == "trigo") 
        form = {{1, 1},{1, 1}};

    else if (type == "manteiga") 
        form = {{1, 1, 1},{0, 1, 0}};
     
    else if (type == "mel") 
        form = {{1, 1}};
     
    else if (type == "açu") 
        form = {{1}};
     
    else if (type == "leite") 
        form = {{1, 0},{1, 1}};
}