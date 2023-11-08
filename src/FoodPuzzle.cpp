#include <fstream>
#include "FoodPuzzle.h"

FoodPuzzle::FoodPuzzle(std::string mapFilePath) : completed(false) {
    std::ifstream file(mapFilePath);
    std::string line;
    while (std::getline(file, line)) {
        answerMap.push_back(line);
    }
    file.close();
    actualMap.resize(answerMap.size(), std::string(answerMap[0].size(), '0'));
}

bool FoodPuzzle::IsCompleted() {
    return completed;
}

bool FoodPuzzle::AddFoodPiece(const FoodPiece& foodPiece) {
    // Lógica para adicionar uma peça ao mapa
    return true;
}

bool FoodPuzzle::RemoveFoodPiece(const FoodPiece& foodPiece) {
    // Lógica para remover uma peça do mapa
    return true;
}

void FoodPuzzle::LockFoodPiece(const FoodPiece& foodPiece) {
}

void FoodPuzzle::UnLockFoodPiece(const FoodPiece& foodPiece) {
}