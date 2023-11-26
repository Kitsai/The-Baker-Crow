#include "Game.h"
#include "selectors/Selector.h"
#include "FoodItem.h"
#include "FoodPiece.h"
#include "InputManager.h"
#include "states/PuzzleState.h"
#include "defines/DefineInput.h"

PuzzleState::PuzzleState(int puzzleNumber) : State(){
    GameObject* ui = new GameObject();
    ui->AddComponent(new Sprite(*ui,"resources/img/ui_puzzle.png"));
    ui->box.SetCenter({Game::GetInstance().GetWindowWidth() * 0.5F,Game::GetInstance().GetWindowHeight() * 0.5F});
    AddObject(ui);
    
    puzzle = new FoodPuzzle("resources/map/puzzleMap"+std::to_string(puzzleNumber)+".txt");
    LoadMap();

    // load music

    GameObject* selector = new GameObject();
    selector->AddComponent(new Selector(*selector));
    selector->box.x = 15;
    selector->box.y = 32;
    AddObject(selector);
    backGroundMusic =  std::make_unique<Music>("resources/music/MusicPuzzle.flac");
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
        // deletes selector if ESCAPE_KEY has been pressed, creates selector
        if(iM.KeyPress(ESCAPE_KEY) && objectArray[i]->GetComponent("FoodPiece").lock()){
            objectArray[i]->RequestDelete();

            FoodPiece* foodPiece = (FoodPiece*)(objectArray[i]->GetComponent("FoodPiece").lock().get());
            std::vector<std::weak_ptr<GameObject>> pieces = foodPiece->GetPieces();
            for (int i = 0; i < (int)pieces.size(); i++){
                pieces[i].lock()->RequestDelete();
            }

            GameObject* selector = new GameObject();
            selector->AddComponent(new Selector(*selector));
            selector->box.x = 15;
            selector->box.y = 32;
            AddObject(selector);
        }

        if(objectArray[i]->IsDead()){
            // deletes selector, creates puzzle piece
            if(objectArray[i]->GetComponent("Selector").lock()){
                GameObject* pieces = new GameObject();
                pieces->box.x = 415;
                pieces->box.y = 170;

                // substituir por pegar do inventário depois
                FoodItem* item;
                if (objectArray[i].get()->box.y == 32) item = new FoodItem(*pieces, "morango");
                else if (objectArray[i].get()->box.y == 187) item = new FoodItem(*pieces, "mel");
                else if (objectArray[i].get()->box.y == 342) item = new FoodItem(*pieces, "acucar");
                else if (objectArray[i].get()->box.y == 505) item = new FoodItem(*pieces, "chocolate");
                pieces->AddComponent(item);
                AddObject(pieces);
            }

            // deletes puzzle piece, creates selector
            bool locked = false;
            if(objectArray[i]->GetComponent("FoodPiece").lock()){
                locked = puzzle->AddFoodPiece(*(FoodPiece*)objectArray[i]->GetComponent("FoodPiece").lock().get());
                if (!locked) {
                    objectArray[i]->UnrequestDelete();
                    continue; // if unable to add piece to puzzle, doesn't delete piece
                }
                
                GameObject* selector = new GameObject();
                selector->AddComponent(new Selector(*selector));
                selector->box.x = 15;
                selector->box.y = 32;
                AddObject(selector);
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
            go->box.x = 415+(67*j);
            go->box.y = 170+(67*(i-2));
            if (map[i][j] == '1') go->AddComponent(new Sprite(*go,"resources/img/puzzleTile_ph.png"));
            else if (map[i][j] == '0') go->AddComponent(new Sprite(*go,"resources/img/puzzleTilec_ph.png"));
            AddObject(go);
        }
    }
}