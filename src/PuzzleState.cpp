#include "PuzzleState.h"
#include "InputManager.h"
#include "Selector.h"
#include "FoodItem.h"
#include "FoodPiece.h"

#include "Game.h"

PuzzleState::PuzzleState(int puzzleNumber) : State(){
    GameObject* ui = new GameObject();
    ui->AddComponent((std::shared_ptr<Sprite>)new Sprite(*ui,"resources/img/ui_puzzle.png"));
    ui->box.SetCenter({Game::GetInstance().GetWindowWidth() * 0.5F,Game::GetInstance().GetWindowHeight() * 0.5F});
    AddObject(ui);
    
    puzzle = new FoodPuzzle("resources/map/puzzleMap"+std::to_string(puzzleNumber)+".txt");
    LoadMap();

    // load music

    CreateSelector();
}

PuzzleState::~PuzzleState(){
    objectArray.clear();
}

void PuzzleState::LoadAssets(){}

void PuzzleState::Render(){
    RenderArray();
}

void PuzzleState::Update(float dt){
    InputManager& iM = InputManager::GetInstance();

    if(iM.QuitRequested()) quitRequested = true;

    UpdateArray(dt);

    // checks whether puzzle has been complete 
    if (puzzle->IsCompleted()) quitRequested = true;

    for(std::vector<int>::size_type i=0;i<objectArray.size();i++) {
        // deletes selector if ESCAPE_KEY has been pressed, creates selector
        if(iM.KeyPress(ESCAPE_KEY) && objectArray[i]->GetComponent("FoodPiece") != nullptr){
            FoodPiece* foodPiece = (FoodPiece*)(objectArray[i]->GetComponent("FoodPiece").get());
            if (foodPiece->IsLocked()) continue;
            
            objectArray[i]->RequestDelete();
            std::vector<std::weak_ptr<GameObject>> pieces = foodPiece->GetPieces();        
            for (int i = 0; i < (int)pieces.size(); i++){
                pieces[i].lock()->RequestDelete();
            }

            CreateSelector();
        }

        if(objectArray[i]->IsDead()){
            // deletes selector, creates puzzle piece
            if(objectArray[i]->GetComponent("Selector") != nullptr){
                GameObject* pieces = new GameObject();
                pieces->box.x = 415;
                pieces->box.y = 170;

                // substituir por pegar do inventário depois
                std::shared_ptr<FoodItem> item;
                if (objectArray[i].get()->box.y == 32) item = (std::shared_ptr<FoodItem>) new FoodItem(*pieces, "morango");
                else if (objectArray[i].get()->box.y == 187) item = (std::shared_ptr<FoodItem>) new FoodItem(*pieces, "mel");
                else if (objectArray[i].get()->box.y == 342) item = (std::shared_ptr<FoodItem>) new FoodItem(*pieces, "acucar");
                else if (objectArray[i].get()->box.y == 505) item = (std::shared_ptr<FoodItem>) new FoodItem(*pieces, "chocolate");
                pieces->AddComponent(item);
                AddObject(pieces);
            }

            // checks whether piece can be locked; if so, creates a selector
            if(objectArray[i]->GetComponent("FoodPiece") != nullptr){
                FoodPiece* foodPiece = (FoodPiece*)(objectArray[i]->GetComponent("FoodPiece").get());
                if (foodPiece->GetStatus()){ // only checks if piece is waiting to be evaluated
                    bool locked = puzzle->AddFoodPiece(*(FoodPiece*)objectArray[i]->GetComponent("FoodPiece").get());
                    objectArray[i]->UnrequestDelete();
                    if (!locked) continue;
                    
                    foodPiece->Lock();

                    CreateSelector();
                    continue;
                }
            }
            
            objectArray.erase(objectArray.begin()+i);
        }
    }
}


void PuzzleState::Start(){
    LoadAssets();
    StartArray();
    started = true;
}

void PuzzleState::Pause(){}

void PuzzleState::Resume(){}

void PuzzleState::LoadMap(){
    std::vector<std::string> map = puzzle->GetMap();
    for(int i = 2; i < (int)map.size(); i++){
        for(int j = 0; j < (int)map[i].size(); j++){
            GameObject* go = new GameObject();
            go->box.x = 415+(67*j);
            go->box.y = 170+(67*(i-2));
            if (map[i][j] == '1') go->AddComponent((std::shared_ptr<Sprite>)new Sprite(*go,"resources/img/puzzleTile_ph.png"));
            else if (map[i][j] == '0') go->AddComponent((std::shared_ptr<Sprite>)new Sprite(*go,"resources/img/puzzleTilec_ph.png"));
            AddObject(go);
        }
    }
}

void PuzzleState::CreateSelector(){
    GameObject* selector = new GameObject();
    selector->AddComponent((std::shared_ptr<Selector>)new Selector(*selector));
    selector->box.x = 15;
    selector->box.y = 32;
    AddObject(selector);
}