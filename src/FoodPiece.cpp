#include "FoodItem.h"
#include "FoodPiece.h"
#include "Game.h"
#include "InputManager.h"
#include <iostream>

FoodPiece::FoodPiece(GameObject& associated, class FoodItem& foodItem) 
    : Component(associated), locked(false), waiting(false), foodItem(&foodItem), type(foodItem.GetType()) {
    evaluateForm();
    RenderPieces();
}

FoodPiece::~FoodPiece() {
    pieces.clear();
}

void FoodPiece::Render() {
}

void FoodPiece::Update(float dt) {
    InputManager& iM = InputManager::GetInstance();

    if (locked) return;

    for (int i = 0; i < (int)pieces.size(); i++) {
        auto lockedPiece = pieces[i].lock();

        if (!lockedPiece) {
            printf("exception 1");
            pieces.erase(pieces.begin() + i);
            continue;
        }
    }

    if (iM.KeyPress(LEFT_ARROW_KEY)) {
        for (int i = 0; i < (int)pieces.size(); i++)
            if (pieces[i].lock()->box.x < 450) return; // se uma das peças estiver no limite, nenhuma delas pode se mover
        associated.box.x -= 60;
        for (int i = 0; i < (int)pieces.size(); i++){
            pieces[i].lock()->box.x -= 60;
        }
    }
    if (iM.KeyPress(RIGHT_ARROW_KEY)) {
        for (int i = 0; i < (int)pieces.size(); i++)
            if (pieces[i].lock()->box.x > 700) return; 
        associated.box.x += 60;
        for (int i = 0; i < (int)pieces.size(); i++){
            pieces[i].lock()->box.x += 60;
        }
    }
    if(iM.KeyPress(UP_ARROW_KEY)) {
        for (int i = 0; i < (int)pieces.size(); i++)
            if (pieces[i].lock()->box.y < 200) return;
        associated.box.y -= 60;
        for (int i = 0; i < (int)pieces.size(); i++){
            pieces[i].lock()->box.y -= 60;
        }
    }
    if(iM.KeyPress(DOWN_ARROW_KEY)) {
        for (int i = 0; i < (int)pieces.size(); i++)
            if (pieces[i].lock()->box.y > 450) return;
        associated.box.y += 60;
        for (int i = 0; i < (int)pieces.size(); i++){
            pieces[i].lock()->box.y += 60;
        }
    }

    if (iM.KeyPress(Z_KEY)) {
        associated.RequestDelete();
        Wait();
    } 
}

FoodItemType FoodPiece::GetType() {
    return type;
}

// waits to see whether piece can be locked
void FoodPiece::Wait() {
    waiting = true;
}

bool FoodPiece::GetStatus() {
    return waiting;
}

bool FoodPiece::IsLocked() {
    return locked;
}

bool FoodPiece::Lock() {
    locked = true;
    waiting = false;
    return locked;
}

bool FoodPiece::UnLock() {
    locked = false;
    waiting = false;
    return !locked;
}

bool FoodPiece::Is(std::string type) {
    return type == "FoodPiece";
}

std::vector<std::vector<int>> FoodPiece::GetForm() {
    return form;
}


std::vector<std::weak_ptr<GameObject>> FoodPiece::GetPieces(){
    return pieces;
}

void FoodPiece::evaluateForm(){ 
    if (type == FoodItemType::eggs)
        form = {{1, 1, 1, 1}};
    
    else if (type == FoodItemType::straw)
        form = {{1, 0},{1, 0},{1, 1}};

    else if (type == FoodItemType::chocolate) 
        form = {{1, 0},{1, 1},{0, 1}};

    else if (type == FoodItemType::wheat) 
        form = {{1, 1},{1, 1}};

    else if (type == FoodItemType::butter) 
        form = {{1, 1, 1},{0, 1, 0}};
     
    else if (type == FoodItemType::honey) 
        form = {{1, 1}};
     
    else if (type == FoodItemType::sugar) 
        form = {{1}};
     
    else if (type == FoodItemType::milk) 
        form = {{1, 0},{1, 1}};
}

void FoodPiece::RenderPieces(){
    int x = 0;
    int y = 0;
    for (int i = 0; i < (int)form.size(); i++){
        for (int j = 0; j < (int)form[i].size(); j++){
            if (form[i][j] == 1){
                GameObject* go = new GameObject();
                Sprite* sprite = new Sprite(*go,"resources/img/puzzle/pieces/"+foodItemTypeToString[type]+".png");
                sprite->SetScale(2,2);

                go->AddComponent(sprite);
                go->box.x = associated.box.x + x;
                go->box.y = associated.box.y + y;
                Game::GetInstance().GetCurrentState().AddObject(go);
                pieces.push_back(Game::GetInstance().GetCurrentState().GetObjectPtr(go));
            }
            x += 60;
        }
        x = 0;
        y += 60;
    }
}
