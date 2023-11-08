#ifndef FoodPuzzle_h_
#define FoodPuzzle_h_

#include <string>
#include <vector>
#include "FoodPiece.h"

class FoodPuzzle {
public:
    
    FoodPuzzle(std::string mapFilePath);
    void AddFoodPiece(const FoodPiece& foodPiece, int x, int y);
    void RemoveFoodPiece(const FoodPiece& foodPiece);

private:
    std::vector<std::string> map;
    std::vector<FoodPiece> foodPieces;
};
#endif