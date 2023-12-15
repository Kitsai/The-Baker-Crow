#ifndef GameData_h_
#define GameData_h_


#include <vector>
#include <string>

#include "Vec2.h"
#include "Music.h"
#include "items.h"

/// @brief A static class made to keep important game data.
class GameData {
    public:
        /// @brief Keeps the current Victory status. Changed when win or lose conditions are met.
        static bool playerAlive;
        static bool quitOWState;
        static bool intro;

        static int playerLife;
        static Vec2 lastSafePosition;

        static std::vector<std::string> requests;
        static std::vector<std::string> recipes;
        static std::vector<std::string> clients;
        static bool hasNPC;
        static bool requestDone;
        
        static bool completed;
        static std::string chosenRequest;
        
        static std::unique_ptr<Music> backGroundMusic;
        static std::vector<std::pair<bool, FoodItemType>> hasItem;
        static std::vector<std::pair<bool, RevenuesItemType>> revenuesCompleted;
};

#endif
