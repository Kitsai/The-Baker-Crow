#include "GameData.h"

int GameData::playerLife = 3;
bool GameData::playerAlive = false;

bool GameData::quitOWState = false;

Vec2 GameData::lastSafePosition = {0,0};