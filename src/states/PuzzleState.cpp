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

            this->selectorOn = true;
        }

        if(objectArray[i]->IsDead()){
            // checks whether piece can be locked; if so, creates a PuzzleSelector
            if(objectArray[i]->GetComponent("FoodPiece").lock().get() != nullptr){
                FoodPiece* foodPiece = (FoodPiece*)(objectArray[i]->GetComponent("FoodPiece").lock().get());
                if (foodPiece->GetStatus()){ // only checks if piece is waiting to be evaluated
                    bool locked = puzzle->AddFoodPiece(*foodPiece, {objectArray[i]->box.x, objectArray[i]->box.y});
                    objectArray[i]->UnrequestDelete();
                    if (!locked) continue;
                    
                    foodPiece->Lock();

                    this->selectorOn = true;
                    continue;
                }
            }
            
            objectArray.erase(objectArray.begin()+i);
        }
    }
    selector->Update(dt);
}
void PuzzleState::Start(){
    StartArray();
    LoadButtons();
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

void PuzzleState::LoadButtons(){
    std::vector<std::shared_ptr<Button>> buttons;
    Button* butter      = new Button(Vec2(1000, 0), "resources/img/ingredients/butter.png", false);
    Button* chocolate   = new Button(Vec2(1000, 100), "resources/img/ingredients/chocolate.png", false);
    Button* egg         = new Button(Vec2(1000, 200), "resources/img/ingredients/egg.png", false);
    Button* honey       = new Button(Vec2(1000, 300), "resources/img/ingredients/honey.png", false);
    Button* milk        = new Button(Vec2(1000, 400), "resources/img/ingredients/milk.png", false);
    Button* strawberry  = new Button(Vec2(1000, 500),   "resources/img/ingredients/straw.png", false);
    Button* sugar       = new Button(Vec2(1000, 600), "resources/img/ingredients/sugar.png", false);
    Button* wheat       = new Button(Vec2(1000, 700), "resources/img/ingredients/wheat.png", false);

    buttons.push_back((std::shared_ptr<Button>) butter);
    buttons.push_back((std::shared_ptr<Button>) chocolate);
    buttons.push_back((std::shared_ptr<Button>) egg);
    buttons.push_back((std::shared_ptr<Button>) honey);
    buttons.push_back((std::shared_ptr<Button>) milk);
    buttons.push_back((std::shared_ptr<Button>) strawberry);
    buttons.push_back((std::shared_ptr<Button>) sugar);
    buttons.push_back((std::shared_ptr<Button>) wheat);
    
    selector = std::make_unique<PuzzleSelector>(buttons);
}