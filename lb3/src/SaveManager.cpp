#include "SaveManager.h"
#include <fstream>
#include <sstream>
#include <filesystem>
#include <ctime>
#include <iostream>

namespace fs = std::filesystem;

EnemySaveData::EnemySaveData() : x(0), y(0), health(0) {}
EnemySaveData::EnemySaveData(int _x, int _y, int h) : x(_x), y(_y), health(h) {}

GameSaveData::GameSaveData() : width(0), height(0), playerX(0), playerY(0),
                               playerHealth(0), playerScore(0), playerKills(0) {}

SaveException::SaveException(const std::string& msg) : message("Ошибка сохранения: " + msg) {}
const char* SaveException::what() const noexcept { return message.c_str(); }

LoadException::LoadException(const std::string& msg) : message("Ошибка загрузки: " + msg) {}
const char* LoadException::what() const noexcept { return message.c_str(); }

SaveManager::SaveManager(const std::string& dir) : saveDir(dir) {
    ensureDirectoryExists();
}

void SaveManager::ensureDirectoryExists() {
    if (!fs::exists(saveDir)) {
        fs::create_directory(saveDir);
    }
}

std::string SaveManager::getCurrentTimestamp() {
    time_t now = time(nullptr);
    char buf[20];
    strftime(buf, sizeof(buf), "%Y%m%d_%H%M%S", localtime(&now));
    return std::string(buf);
}

void SaveManager::saveGame(const GameSaveData& data, const std::string& filename) {
    std::string fullPath = saveDir + filename;
    std::ofstream file(fullPath);
    
    if (!file.is_open()) {
        throw SaveException("Не удалось создать файл");
    }
    
    file << "[FIELD]\n";
    file << data.width << " " << data.height << "\n";
    
    file << "[PLAYER]\n";
    file << data.playerX << " " << data.playerY << " "
         << data.playerHealth << " " << data.playerScore << " "
         << data.playerKills << "\n";
    
    file << "[SPELLS]\n";
    file << data.spells.size() << "\n";
    for (const auto& spell : data.spells) {
        file << spell << "\n";
    }
    
    file << "[ENEMIES]\n";
    file << data.enemies.size() << "\n";
    for (const auto& enemy : data.enemies) {
        file << enemy.x << " " << enemy.y << " " << enemy.health << "\n";
    }
    
    file.close();
}

void SaveManager::saveGame(const GameSaveData& data) {
    std::string filename = "save_" + getCurrentTimestamp() + ".txt";
    saveGame(data, filename);
    std::cout << "Игра сохранена в файл: " << filename << "\n";
}

GameSaveData SaveManager::loadGame(const std::string& filename) {
    std::string fullPath = saveDir + filename;
    std::ifstream file(fullPath);
    
    if (!file.is_open()) {
        throw LoadException("Файл сохранения не найден");
    }
    
    GameSaveData data;
    std::string marker;
    
    file >> marker;
    if (marker != "[FIELD]") throw LoadException("Неверный формат файла");
    file >> data.width >> data.height;
    
    file >> marker;
    if (marker != "[PLAYER]") throw LoadException("Неверный формат файла");
    file >> data.playerX >> data.playerY 
         >> data.playerHealth >> data.playerScore >> data.playerKills;
    
    file >> marker;
    if (marker != "[SPELLS]") throw LoadException("Неверный формат файла");
    int spellCount;
    file >> spellCount;
    data.spells.clear();
    file.ignore();
    for (int i = 0; i < spellCount; i++) {
        std::string spell;
        getline(file, spell);
        data.spells.push_back(spell);
    }
    
    file >> marker;
    if (marker != "[ENEMIES]") throw LoadException("Неверный формат файла");
    int enemyCount;
    file >> enemyCount;
    data.enemies.clear();
    for (int i = 0; i < enemyCount; i++) {
        int x, y, health;
        file >> x >> y >> health;
        data.enemies.push_back(EnemySaveData(x, y, health));
    }
    
    return data;
}

std::vector<std::string> SaveManager::listSaves() {
    std::vector<std::string> saves;
    
    try {
        for (const auto& entry : fs::directory_iterator(saveDir)) {
            if (entry.path().extension() == ".txt") {
                saves.push_back(entry.path().filename().string());
            }
        }
    } catch (...) {}
    
    return saves;
}