#ifndef GameData_h_
#define GameData_h_

#include "Vec2.h"

/// @brief A static class made to keep important game data.
class GameData {
    public:
        /// @brief Keeps the current Victory status. Changed when win or lose conditions are met.
        static bool playerAlive;

        static Vec2 lastSafePosition;
};

#endif