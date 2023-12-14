#include "GameData.h"

int GameData::playerLife = 3;
bool GameData::playerAlive = false;

bool GameData::intro = true;
bool GameData::quitOWState = false;

Vec2 GameData::lastSafePosition = {0,0};

std::vector<std::string> GameData::requests = {};
std::vector<std::pair<bool, FoodItemType>> GameData::hasItem = {
    
    {false, butter},
    {false, chocolate},
    {false, eggs},
    {false, honey},
    {false, milk},
    {false, straw},
    {false, sugar},
    {false, wheat},
};

std::vector<std::pair<bool, RevenuesItemType>> GameData::revenuesCompleted = {
    
    {false, brigadeiro},
    {false, cake},
    {false, cheesebread},
    {false, macarons},
    {false, pudding},

};

std::unique_ptr<Music> GameData::backGroundMusic = nullptr;