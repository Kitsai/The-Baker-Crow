#ifndef FoodPuzzle_h_
#define FoodPuzzle_h_

#include <string>
#include <vector>
#include "FoodPiece.h"

class FoodPuzzle {
public:
    FoodPuzzle(std::string mapFilePath);
    bool IsCompleted();
    bool AddFoodPiece(const FoodPiece& foodPiece);
    bool RemoveFoodPiece(const FoodPiece& foodPiece);    
    void LockFoodPiece(const FoodPiece& foodPiece);
    void UnLockFoodPiece(const FoodPiece& foodPiece);

private:
    bool completed;
    std::vector<std::string> answerMap;
    std::vector<std::string> actualMap; 
    std::vector<FoodPiece> foodPieces;
};
#endif
