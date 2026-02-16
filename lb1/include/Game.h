#ifndef GAME_H
#define GAME_H

#include "GameField.h"
#include "Player.h"
#include "Enemy.h"
#include <vector>

class Game {
private:
    GameField field;
    Player player;
    std::vector<Enemy> enemies;
    bool running;
    
public:
    Game(int width, int height);
    
    void display();
    void handleInput(char key);
    void enemyTurn();
    bool isRunning();
    
private:
    int getAliveEnemiesCount() const;
    void attackEnemyAt(int x, int y);
};

#endif // GAME_H