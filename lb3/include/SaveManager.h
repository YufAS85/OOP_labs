#ifndef SAVE_MANAGER_H
#define SAVE_MANAGER_H

#include <string>
#include <vector>
#include <exception>

struct EnemySaveData {
    int x, y;
    int health;
    
    EnemySaveData();
    EnemySaveData(int _x, int _y, int h);
};

struct GameSaveData {
    int width, height;
    int playerX, playerY;
    int playerHealth, playerScore, playerKills;
    std::vector<std::string> spells;
    std::vector<EnemySaveData> enemies;
    
    GameSaveData();
};

class SaveException : public std::exception {
private:
    std::string message;
public:
    SaveException(const std::string& msg);
    const char* what() const noexcept override;
};

class LoadException : public std::exception {
private:
    std::string message;
public:
    LoadException(const std::string& msg);
    const char* what() const noexcept override;
};

class SaveManager {
private:
    std::string saveDir;
    
    void ensureDirectoryExists();
    std::string getCurrentTimestamp();
    
public:
    SaveManager(const std::string& dir = "saves/");
    
    void saveGame(const GameSaveData& data, const std::string& filename);
    void saveGame(const GameSaveData& data);
    GameSaveData loadGame(const std::string& filename);
    std::vector<std::string> listSaves();
};

#endif