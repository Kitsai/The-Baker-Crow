#ifndef GameData_h_
#define GameData_h_

#include "Vec2.h"

/// @brief A static class made to keep important game data.
class GameData {
    public:
        /// @brief Keeps the current Victory status. Changed when win or lose conditions are met.
        static bool playerAlive;
        static bool quitOWState;

        static int playerLife;
        static Vec2 lastSafePosition;

        static bool hasSugar;
        static bool hasChoco;
        static bool hasMilk;
        static bool hasButter;
        static bool hasHoney;
        static bool hasStraw;
        static bool hasEggs;
        static bool hasWheat;
};

#endif