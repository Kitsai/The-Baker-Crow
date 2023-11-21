#include "FoodItem.h"
#include "FoodPiece.h"
#include "Game.h"
#include "InputManager.h"
#include <iostream>

FoodPiece::FoodPiece(GameObject& associated, class FoodItem& foodItem) 
    : Component(associated), locked(false), foodItem(&foodItem), type(foodItem.GetType()) {
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

    if (iM.KeyPress(LEFT_ARROW_KEY)) {
        for (int i = 0; i < (int)pieces.size(); i++)
            if (pieces[i].lock()->box.x < 450) return; // se uma das peças estiver no limite, nenhuma delas pode se mover
        for (int i = 0; i < (int)pieces.size(); i++) 
            pieces[i].lock()->box.x -= 67;
    }
    if (iM.KeyPress(RIGHT_ARROW_KEY)) {
        for (int i = 0; i < (int)pieces.size(); i++)
            if (pieces[i].lock()->box.x > 700) return; 
        for (int i = 0; i < (int)pieces.size(); i++) 
            pieces[i].lock()->box.x += 67;
    }
    if(iM.KeyPress(UP_ARROW_KEY)) {
        for (int i = 0; i < (int)pieces.size(); i++)
            if (pieces[i].lock()->box.y < 200) return;
        for (int i = 0; i < (int)pieces.size(); i++) 
            pieces[i].lock()->box.y -= 67;
    }
    if(iM.KeyPress(DOWN_ARROW_KEY)) {
        for (int i = 0; i < (int)pieces.size(); i++)
            if (pieces[i].lock()->box.y > 500) return;
        for (int i = 0; i < (int)pieces.size(); i++) 
            pieces[i].lock()->box.y += 67;
    }

    if (iM.KeyPress(ENTER_KEY)) associated.RequestDelete();
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
    return type == "FoodPiece";
}

std::vector<std::vector<int>> FoodPiece::GetForm() {
    return form;
}

std::vector<std::weak_ptr<GameObject>> FoodPiece::GetPieces(){
    return pieces;
}

void FoodPiece::evaluateForm(){ 
    if (type == "ovo")
        form = {{1, 1, 1, 1}};
    
    else if (type == "morango")
        form = {{1, 0},{1, 0},{1, 1}};

    else if (type == "chocolate") 
        form = {{1, 0},{1, 1},{0, 1}};

    else if (type == "trigo") 
        form = {{1, 1},{1, 1}};

    else if (type == "manteiga") 
        form = {{1, 1, 1},{0, 1, 0}};
     
    else if (type == "mel") 
        form = {{1, 1}};
     
    else if (type == "acucar") 
        form = {{1}};
     
    else if (type == "leite") 
        form = {{1, 0},{1, 1}};
}

void FoodPiece::RenderPieces(){
    int x = 0;
    int y = 0;
    for (int i = 0; i < (int)form.size(); i++){
        for (int j = 0; j < (int)form[i].size(); j++){
            if (form[i][j] == 1){
                GameObject* go = new GameObject();
                go->box.x = associated.box.x + x;
                go->box.y = associated.box.y + y;
                go->AddComponent(std::shared_ptr<Sprite>(new Sprite(*go,"resources/img/puzzlePiece_ph.png")));
                Game::GetInstance().GetCurrentState().AddObject(go);
                pieces.push_back(Game::GetInstance().GetCurrentState().GetObjectPtr(go));
            }
            x += 67;
        }
        x = 0;
        y += 67;
    }
}