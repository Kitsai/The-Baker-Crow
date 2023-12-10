#include "GameData.h"

int GameData::playerLife = 3;
bool GameData::playerAlive = false;

bool GameData::quitOWState = false;

bool GameData::hasButter    = false;
bool GameData::hasChoco     = false;
bool GameData::hasEggs      = false;
bool GameData::hasHoney     = false;
bool GameData::hasMilk      = false;
bool GameData::hasSugar     = false;
bool GameData::hasWheat     = false;
bool GameData::hasStraw     = false;

Vec2 GameData::lastSafePosition = {0,0};