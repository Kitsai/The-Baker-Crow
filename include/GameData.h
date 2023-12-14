#ifndef GameData_h_
#define GameData_h_

#include "Music.h"
#include "Vec2.h"
#include <vector>
#include <string>

/// @brief A static class made to keep important game data.
class GameData {
    public:
        /// @brief Keeps the current Victory status. Changed when win or lose conditions are met.
        static bool playerAlive;
        static bool quitOWState;
        static bool intro;

        static int playerLife;
        static Vec2 lastSafePosition;

        static bool hasItem[8];

        static std::vector<std::string> requests;
        static std::vector<std::string> recipes;
        static std::vector<std::string> clients;
        static bool hasNPC;
        
        static std::unique_ptr<Music> backGroundMusic;
};

#endif
