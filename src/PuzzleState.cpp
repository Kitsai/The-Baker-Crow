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

    GameObject* selector = new GameObject();
    selector->AddComponent((std::shared_ptr<Selector>)new Selector(*selector));
    selector->box.x = 15;
    selector->box.y = 32;
    AddObject(selector);
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

    if(iM.KeyPress(ESCAPE_KEY) || iM.QuitRequested()) quitRequested = true;

    UpdateArray(dt);

    for(std::vector<int>::size_type i=0;i<objectArray.size();i++) {
        if(objectArray[i]->IsDead()){
            if(objectArray[i]->GetComponent("Selector") != nullptr){
                // coloca no puzzle as peças a serem encaixadas conforme selecionado pelo selector
                GameObject* pieces = new GameObject();
                pieces->box.x = 415;
                pieces->box.y = 170;
                // substituir por pegar do inventário depois
                std::shared_ptr<FoodItem> item = (std::shared_ptr<FoodItem>) new FoodItem(*pieces, "morango");
                pieces->AddComponent(item);
                AddObject(pieces);
            }

            bool locked = false;
            if(objectArray[i]->GetComponent("FoodPiece") != nullptr){
                locked = puzzle->AddFoodPiece(*(FoodPiece*)objectArray[i]->GetComponent("FoodPiece").get());
                if (!locked) {
                    objectArray[i]->UnrequestDelete();
                    continue; // if unable to add piece to puzzle, doesn't delete piece
                }
                // if puzzle isn't complete, goes back to selector
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