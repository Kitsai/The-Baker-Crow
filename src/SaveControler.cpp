#include <fstream>
#include <sstream>
#include <iostream>
#include "GameData.h"
#include "SaveController.h"

void SaveController::WriteSave(int i) {
    std::string saveMove = std::to_string(i); 
    std::ofstream saveFile("src/SAVE/save"+saveMove+".txt");

    if (!saveFile.is_open()) {
        std::cerr << "Erro ao tentar escrever no arquivo SAVE"<<std::endl;
        return;
    }
    saveFile << "playerLife: " << GameData::playerLife << "\n";
    saveFile << "playerAlive: " << GameData::playerAlive << "\n";

    saveFile << "SaveIsInUse: " << GameData::SaveIsInUse << "\n";
    saveFile << "intro: " << GameData::intro << "\n";
    saveFile << "quitOWState: " << GameData::quitOWState << "\n";
    saveFile << "completed: " << GameData::completed << "\n";
    saveFile << "lastSafePosition: " << GameData::lastSafePosition.x << " " << GameData::lastSafePosition.y << "\n";

    saveFile << "requests: ";
    for (const auto& request : GameData::requests) {
        saveFile << request << " ";
    }
    saveFile << "\n";

    saveFile << "recipes: ";
    for (const auto& recipe : GameData::recipes) {
        saveFile << recipe << " ";
    }
    saveFile << "\n";

    saveFile << "clients: ";
    for (const auto& client : GameData::clients) {
        saveFile << client << " ";
    }
    saveFile << "\n";

    saveFile << "hasNPC: " << GameData::hasNPC  <<"\n";
    saveFile << "requestDone: " << GameData::requestDone <<"\n";
    saveFile << "chosenRequest: " << GameData::chosenRequest <<"\n";

    saveFile << "hasItem: ";
    for (const auto& item : GameData::hasItem) {
        saveFile << item.first << " ";
    }
    saveFile << "\n";

    saveFile << "revenuesCompleted: ";
    for (const auto& revenue : GameData::revenuesCompleted) {
        saveFile << revenue.first << " ";
    }
    saveFile << "\n";
    saveFile.close();
}

void SaveController::ReadSave(int i) {
    std::string saveMove = std::to_string(i);
    std::ifstream saveFile("src/SAVE/save" + saveMove + ".txt");

    if (!saveFile.is_open()) {
        std::cerr << "Error opening save file " << saveMove << std::endl;
        return;
    }

    std::string line;
    while (std::getline(saveFile, line)) {
        std::istringstream iss(line);
        std::string key;
        iss >> key;

        if (key == "playerLife:") {
            iss >> GameData::playerLife;
        } else if (key == "playerAlive:") {
            iss >> GameData::playerAlive;
        } else if(key == "SaveIsInUse:"){
            iss >> GameData::SaveIsInUse;
        } else if (key == "intro:") {
            iss >> GameData::intro;
        } else if (key == "quitOWState:") {
            iss >> GameData::quitOWState;
        } else if(key == "completed:"){
            iss >> GameData::completed;
        }else if (key == "lastSafePosition:") {
            iss >> GameData::lastSafePosition.x >> GameData::lastSafePosition.y;
        } else if (key == "requests:") {
            GameData::requests.clear();
            std::string request;
            while (iss >> request) {
                GameData::requests.push_back(request);
            }
        } else if (key == "recipes:") {
            GameData::recipes.clear();
            std::string recipes;
            while (iss >> recipes) {
                GameData::recipes.push_back(recipes);
            }
        } else if (key == "clients:") {
            GameData::clients.clear();
            std::string clients;
            while (iss >> clients) {
                GameData::clients.push_back(clients);
            }
        } else if(key == "hasNPC:"){
            iss >> GameData::hasNPC;
        
        } else if(key == "requestDone:"){
            iss >> GameData::requestDone;
        
        } else if(key == "chosenRequest:"){
            iss >> GameData::chosenRequest;
        
        }else if (key == "hasItem:") {
            for (auto& item : GameData::hasItem) {
                bool hasItem;
                iss >> hasItem;
                item.first = hasItem;
            }
        } else if (key == "revenuesCompleted:") {
            for (auto& revenue : GameData::revenuesCompleted) {
                bool completed;
                iss >> completed;
                revenue.first = completed;
            }
        }
    }
    saveFile.close();
}