#include "Game.h"
#include "selectors/PuzzleSelector.h"
#include "FoodItem.h"
#include "FoodPiece.h"
#include "InputManager.h"
#include "states/PuzzleState.h"
#include "defines/DefineInput.h"

PuzzleState::PuzzleState(int puzzleNumber) : State(){
    GameObject* ui = new GameObject();
    ui->AddComponent(new Sprite(*ui,"resources/img/puzzle/ui/Exemplo.png"));
    ui->box.SetCenter({Game::GetInstance().GetWindowWidth() * 0.5F,Game::GetInstance().GetWindowHeight() * 0.5F});
    AddObject(ui);
    
    puzzle = new FoodPuzzle("resources/map/puzzleMap"+std::to_string(puzzleNumber)+".txt");
    LoadMap();

    CreatePuzzleSelector();
    backGroundMusic = std::make_unique<Music>("resources/music/MusicPuzzle.flac");
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


    if ((InputManager::GetInstance().KeyPress(SPACE_KEY))){
        popRequested = true;
        backGroundMusic->Stop(50);
    }

    if(iM.QuitRequested()) quitRequested = true;

    UpdateArray(dt);

    // checks whether puzzle has been complete 
    if (puzzle->IsCompleted()) quitRequested = true;

    for(std::vector<int>::size_type i=0;i<objectArray.size();i++) {
        // deletes PuzzleSelector if ESCAPE_KEY has been pressed, creates PuzzleSelector
        if(iM.KeyPress(ESCAPE_KEY) && objectArray[i]->GetComponent("FoodPiece").lock().get() != nullptr){
            FoodPiece* foodPiece = (FoodPiece*)(objectArray[i]->GetComponent("FoodPiece").lock().get());
            if (foodPiece->IsLocked()) continue;
            
            objectArray[i]->RequestDelete();
            std::vector<std::weak_ptr<GameObject>> pieces = foodPiece->GetPieces();
            for (int i = 0; i < (int)pieces.size(); i++){
                pieces[i].lock()->RequestDelete();
            }

            CreatePuzzleSelector();
        }

        if(objectArray[i]->IsDead()){
            // deletes PuzzleSelector, creates puzzle piece
            if(objectArray[i]->GetComponent("PuzzleSelector").lock()){
                GameObject* pieces = new GameObject();
                pieces->box.x = 415;
                pieces->box.y = 170;

                // substituir por pegar do inventário depois

                FoodItem* item;
                if (objectArray[i].get()->box.y == 32) item =  new FoodItem(*pieces, FoodItemType::morango);
                else if (objectArray[i]->box.y == 187) item =  new FoodItem(*pieces, FoodItemType::mel);
                else if (objectArray[i]->box.y == 342) item =  new FoodItem(*pieces, FoodItemType::acucar);
                else if (objectArray[i]->box.y == 505) item =  new FoodItem(*pieces, FoodItemType::chocolate);

                pieces->AddComponent(item);
                AddObject(pieces);
            }
            
            // checks whether piece can be locked; if so, creates a PuzzleSelector
            if(objectArray[i]->GetComponent("FoodPiece").lock().get() != nullptr){
                FoodPiece* foodPiece = (FoodPiece*)(objectArray[i]->GetComponent("FoodPiece").lock().get());
                if (foodPiece->GetStatus()){ // only checks if piece is waiting to be evaluated
                    bool locked = puzzle->AddFoodPiece(*foodPiece, {objectArray[i]->box.x, objectArray[i]->box.y});
                    objectArray[i]->UnrequestDelete();
                    if (!locked) continue;
                    
                    foodPiece->Lock();

                    CreatePuzzleSelector();
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
    backGroundMusic->Play();
}

void PuzzleState::Pause(){}

void PuzzleState::Resume(){
    Camera::pos.x = 0;
    Camera::pos.y = 0;
    backGroundMusic->Play();
}

void PuzzleState::LoadMap(){
    std::vector<std::string> map = puzzle->GetMap();
    for(int i = 2; i < (int)map.size(); i++){
        for(int j = 0; j < (int)map[i].size(); j++){
            GameObject* go = new GameObject();
            go->box.x = 415+(60*j);
            go->box.y = 170+(60*(i-2));
            if (map[i][j] == '1') go->AddComponent(new Sprite(*go,"resources/img/puzzleTile_ph.png"));
            else if (map[i][j] == '0') go->AddComponent(new Sprite(*go,"resources/img/puzzleTilec_ph.png"));
            AddObject(go);
        }
    }
}

void PuzzleState::CreatePuzzleSelector(){
    GameObject* puzzleSelector = new GameObject();
    puzzleSelector->AddComponent(new class PuzzleSelector(*puzzleSelector));
    puzzleSelector->box.x = 15;
    puzzleSelector->box.y = 32;
    AddObject(puzzleSelector);
}
