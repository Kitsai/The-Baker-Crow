#include "GameData.h"
#include <memory>

int GameData::playerLife = 3;
bool GameData::playerAlive = false;

bool GameData::intro = true;
bool GameData::quitOWState = false;

bool GameData::hasItem[8] = {true,true,true,false,true,true,true,true};

Vec2 GameData::lastSafePosition = {0,0};
std::vector<std::string> GameData::requests = {};


std::unique_ptr<Music> GameData::backGroundMusic = nullptr;