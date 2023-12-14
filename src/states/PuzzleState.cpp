#include "Button.h"
#include "Game.h"
#include "GameData.h"
#include "selectors/Selector.h"
#include "FoodItem.h"
#include "FoodPiece.h"
#include "InputManager.h"
#include "selectors/Selector.h"
#include "states/PuzzleState.h"
#include "defines/DefineInput.h"
#include <algorithm>
#include <cstdio>
#include <memory>
#include <vector>

PuzzleState::PuzzleState(int puzzleNumber) : State(),selectorOn(true), currentButton(4), selector(nullptr){
    
    this->positions.emplace_back(Vec2(25, 15));
    this->positions.emplace_back(Vec2(25, 170));
    this->positions.emplace_back(Vec2(25, 325));
    this->positions.emplace_back(Vec2(25, 480));

    GameObject* ui = new GameObject();
    ui->AddComponent(new Sprite(*ui,"resources/img/PuzzleBack.png"));
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
            if(selectorOn){
                FoodItemType itemType;
                if ( selector->GetNameSellectedButton() == "straw")         itemType = FoodItemType::straw;
                else if (selector->GetNameSellectedButton() == "butter")    itemType = FoodItemType::butter;
                else if (selector->GetNameSellectedButton() == "chocolate") itemType = FoodItemType::chocolate;
                else if (selector->GetNameSellectedButton() == "milk")      itemType = FoodItemType::milk;
                else if (selector->GetNameSellectedButton() == "eggs")      itemType = FoodItemType::eggs;
                else if (selector->GetNameSellectedButton() == "sugar")     itemType = FoodItemType::sugar;
                else if (selector->GetNameSellectedButton() == "wheat")     itemType = FoodItemType::wheat;
                else if (selector->GetNameSellectedButton() == "honey")     itemType = FoodItemType::honey;

                GameObject* pieces = new GameObject();
                pieces->box.x = 415;
                pieces->box.y = 170;
                pieces->AddComponent(new FoodItem(*pieces, itemType));
                
                AddObject(pieces);
                this->selectorOn = false;
            }
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
    if(selector && selectorOn){
        if (InputManager::GetInstance().KeyPress(UP_ARROW_KEY)  && selector->GetSelected() == 1 && currentButton > 4){
            selector->Unchose();
            UpdateSelector(Direction::Up);
        }
        
        else if (InputManager::GetInstance().KeyPress(DOWN_ARROW_KEY) && selector->GetSelected() == 4 && currentButton < maxButton){
            selector->Unchose();
            UpdateSelector(Direction::Down);
        }
        
        else
            selector->Update(dt);
    }
}
void PuzzleState::Start(){
    StartArray();
    LoadSelector();
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


void PuzzleState::LoadSelector(){
    int count = 0;

    for(std::pair<bool, FoodItemType> item : GameData::hasItem ){
        if(item.first){
            count++;
        }
    }
    this->maxButton = count;

    UpdateSelector(Direction::Load);
}

void PuzzleState::UpdateSelector(Direction direction) {
    int count = 0;
    int limitNumber = 4;

    if (direction == Direction::Up)
        currentButton--;
    
    else if (direction == Direction::Down)
        currentButton++;
    
    int dif = currentButton - limitNumber;
    
    std::vector<std::shared_ptr<Button>> buttons;

    for(std::pair<bool, FoodItemType> item : GameData::hasItem){
        if(item.first && dif > 0){
            dif = dif -1;
        }
        
        else if(item.first && !((int) buttons.size() >= limitNumber) && dif == 0){
            std::shared_ptr<Button> foodButton = std::make_shared<Button>(positions[count], "resources/img/FoodCircle/"+foodItemTypeToString[item.second]+".png",foodItemTypeToString[item.second], false);
            buttons.push_back( foodButton);
            count++;
        }
    }
    selector = nullptr;
    if (direction == Direction::Down){
        selector = new Selector(buttons, limitNumber);
    }
    else
        selector = new Selector(buttons);
}