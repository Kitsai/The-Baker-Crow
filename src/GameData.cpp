#include "GameData.h"
#include <memory>

int GameData::playerLife = 3;
bool GameData::playerAlive = false;

bool GameData::intro = true;
bool GameData::quitOWState = false;

bool GameData::hasButter    = false;
bool GameData::hasChoco     = true;
bool GameData::hasEggs      = true;
bool GameData::hasHoney     = true;
bool GameData::hasMilk      = true;
bool GameData::hasSugar     = true;
bool GameData::hasWheat     = true;
bool GameData::hasStraw     = true;

Vec2 GameData::lastSafePosition = {0,0};
std::vector<std::string> GameData::requests = {};


std::unique_ptr<Music> GameData::backGroundMusic = nullptr;