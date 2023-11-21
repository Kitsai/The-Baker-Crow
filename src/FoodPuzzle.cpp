#include <fstream>
#include "FoodPuzzle.h"
#include <iostream>

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

bool FoodPuzzle::AddFoodPiece(FoodPiece& foodPiece, Vec2 position) {
    // Lógica para adicionar uma peça ao mapa
    std::vector<std::vector<int>> form = foodPiece.GetForm();
    Vec2 mapPos = ScreenPosToMapPos(position);

    for (int i = 0; i < (int)form.size(); i++){
        for (int j = 0; j < (int)form[i].size(); j++){
            if (form[i][j] == 1){
                if (mapPos.x + i >= (int)actualMap.size() || mapPos.y + j >= (int)actualMap[0].size()) return false;
                if (actualMap[mapPos.y + i][mapPos.x + j] == '1' || answerMap[mapPos.y + i + 2][mapPos.x + j] == '0') return false;
                actualMap[mapPos.y + i][mapPos.x + j] = '1';
            }
        }
    }

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

std::vector<std::string> FoodPuzzle::GetMap() {
    return answerMap;
}

Vec2 FoodPuzzle::ScreenPosToMapPos(Vec2 pos) {
    Vec2* newPos = new Vec2();
    newPos->x = (pos.x - 415)/60;
    newPos->y = (pos.y - 170)/60;
    return *newPos;
}