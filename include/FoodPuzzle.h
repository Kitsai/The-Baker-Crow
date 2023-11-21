#ifndef FoodPuzzle_h_
#define FoodPuzzle_h_

#include <string>
#include <vector>
#include "FoodPiece.h"

class FoodPuzzle {
public:
    FoodPuzzle(std::string mapFilePath);
    bool IsCompleted();
    bool AddFoodPiece(FoodPiece& foodPiece, Vec2 position);
    bool RemoveFoodPiece(const FoodPiece& foodPiece);    
    void LockFoodPiece(const FoodPiece& foodPiece);
    void UnLockFoodPiece(const FoodPiece& foodPiece);
    std::vector<std::string> GetMap();

private:
    bool completed;
    std::vector<std::string> answerMap;
    std::vector<std::string> actualMap; 
    std::vector<FoodPiece> foodPieces;

    Vec2 ScreenPosToMapPos(Vec2 pos);
};
#endif
