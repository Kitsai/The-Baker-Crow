#include "GameData.h"

int GameData::playerLife = 3;
bool GameData::playerAlive = false;

bool GameData::intro = true;
bool GameData::quitOWState = false;
bool GameData::completed = false;

Vec2 GameData::lastSafePosition = {0,0};

std::vector<std::string> GameData::requests = {};
std::vector<std::string> GameData::recipes = {};
std::vector<std::string> GameData::clients = {};
bool GameData::hasNPC = false;

std::vector<std::pair<bool, FoodItemType>> GameData::hasItem = {
    
    {false, butter},
    {true, chocolate},
    {true, eggs},
    {true, honey},
    {true, milk},
    {true, straw},
    {true, sugar},
    {true, wheat},

};

std::unique_ptr<Music> GameData::backGroundMusic = nullptr;
