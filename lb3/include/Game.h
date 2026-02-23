#ifndef GAME_H
#define GAME_H

#include "GameField.h"
#include "Player.h"
#include "Enemy.h"
#include "SaveManager.h"
#include <vector>

class Game {
private:
    GameField field;
    Player player;
    std::vector<Enemy> enemies;
    bool running;
    bool spellMode;
    bool selectingTarget;
    int selectedSpell;
    int targetX, targetY;
    bool turnUsed;
    
public:
    Game(int width, int height);
    
    void spawnEnemy();
    void display();
    int getAliveEnemiesCount();
    void handleInput(char key);
    void handleMovement(char key);
    void attackEnemyAt(int x, int y);
    void enterSpellMode();
    void exitSpellMode();
    void handleSpellInput(char key);
    void enemyTurn();
    bool isRunning();
    bool isTurnUsed() const;
    
    void saveToFile();
    GameSaveData getSaveData() const;
    void loadFromSave(const GameSaveData& data);
};

#endif