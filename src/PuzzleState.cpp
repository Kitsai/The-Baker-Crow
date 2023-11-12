#include "PuzzleState.h"
#include "InputManager.h"

#include "Game.h"

PuzzleState::PuzzleState(int puzzleNumber) : State(){
    // Load assets
    GameObject* go = new GameObject();
    go->AddComponent((std::shared_ptr<Sprite>)new Sprite(*go,"resources/img/ui_puzzle.png"));
    go->box.SetCenter({Game::GetInstance().GetWindowWidth() * 0.5F,Game::GetInstance().GetWindowHeight() * 0.5F});
    AddObject(go);
    
    puzzle = new FoodPuzzle("resources/map/puzzleMap"+std::to_string(puzzleNumber)+".txt");
    LoadMap(puzzle);
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

    DeleteObjects();

}

void PuzzleState::Start(){
    LoadAssets();
    StartArray();
    started = true;
}

void PuzzleState::Pause(){}

void PuzzleState::Resume(){}

void PuzzleState::LoadMap(FoodPuzzle* puzzle){
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
