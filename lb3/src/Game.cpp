#include "Game.h"
#include "Menu.h"         
#include "Constants.h"  
#include <iostream>
#include <cstdlib>
#include <conio.h>

extern const int SCORE_PER_KILL;
extern const int DEFAULT_ENEMY_DAMAGE;

Game::Game(int width, int height) 
    : field(width, height), 
      player(width/2, height/2),
      running(true),
      spellMode(false),
      selectingTarget(false),
      selectedSpell(-1),
      targetX(0), targetY(0),
      turnUsed(false) {
    
    field.placePlayer(player.getX(), player.getY());
    
    for (int i = 0; i < 3; i++) {
        spawnEnemy();
    }
}

void Game::spawnEnemy() {
    int x, y;
    do {
        x = rand() % field.getWidth();
        y = rand() % field.getHeight();
    } while (!field.isCellEmpty(x, y));
    
    enemies.push_back(Enemy(x, y));
    field.placeEnemy(x, y);
}

void Game::display() {
    system("cls");
    field.display();
    
    std::cout << "\n=== Игрок ===\n";
    std::cout << "Здоровье: " << player.getHealth() 
         << " | Урон: " << player.getDamage()
         << " | Очки: " << player.getScore() << "\n";
    std::cout << "Врагов осталось: " << getAliveEnemiesCount() << "\n";
    std::cout << "Прогресс убийств: " << player.getCurrentKills() 
         << "/" << player.getKillsNeeded() << "\n";
    
    player.getHand()->display();
    
    if (spellMode) {
        std::cout << "\n=== РЕЖИМ ЗАКЛИНАНИЙ ===\n";
        if (selectingTarget) {
            std::cout << "Цель: (" << targetX << "," << targetY << ")\n";
            std::cout << "Перемещение: w/a/s/d, Enter - применить, ESC - отмена\n";
        } else {
            std::cout << "Выберите заклинание (1-" << player.getHand()->getCount() 
                 << ") или ESC для выхода\n";
        }
    } else {
        std::cout << "\nКоманды: w/a/s/d - движение, f - заклинания, x - сохранить, q - выход\n";
    }
    
    if (turnUsed) {
        std::cout << "Ход использован! Ожидайте хода врагов...\n";
    }
}

int Game::getAliveEnemiesCount() {
    int count = 0;
    for (auto& enemy : enemies) {
        if (enemy.isAlive()) count++;
    }
    return count;
}

void Game::handleInput(char key) {
    if (turnUsed) {
        return;
    }
    
    if (key == 'x' || key == 'X') {
        saveToFile();
        return;
    }
    
    if (spellMode) {
        handleSpellInput(key);
        return;
    }
    
    switch(key) {
        case 'w': case 'a': case 's': case 'd':
            handleMovement(key);
            break;
        case 'f':
            enterSpellMode();
            break;
        case 'q':
            running = false;
            break;
    }
}

void Game::handleMovement(char key) {
    int newX = player.getX();
    int newY = player.getY();
    
    switch(key) {
        case 'w': newY--; break;
        case 's': newY++; break;
        case 'a': newX--; break;
        case 'd': newX++; break;
    }
    
    if (!field.isValidPosition(newX, newY)) {
        std::cout << "Нельзя выйти за границы поля!\n";
        std::cout << "Нажмите любую клавишу...\n";
        _getch();
        return;
    }
    
    if (field.isCellEnemy(newX, newY)) {
        attackEnemyAt(newX, newY);
        turnUsed = true;
    }
    else if (field.isCellEmpty(newX, newY)) {
        field.clearCell(player.getX(), player.getY());
        player.setPosition(newX, newY);
        field.placePlayer(player.getX(), player.getY());
        turnUsed = true;
    }
}

void Game::attackEnemyAt(int x, int y) {
    for (auto& enemy : enemies) {
        if (enemy.isAlive() && enemy.getX() == x && enemy.getY() == y) {
            std::cout << "Атака! Нанесен урон врагу!\n";
            enemy.takeDamage(player.getDamage());
            if (!enemy.isAlive()) {
                field.clearCell(x, y);
                player.addScore(SCORE_PER_KILL);
                std::cout << "Враг уничтожен! +" << SCORE_PER_KILL << " очков\n";
                
                if (getAliveEnemiesCount() == 0) {
                    std::cout << "\nВЫ ПОБЕДИЛИ! Все враги уничтожены!\n";
                    std::cout << "Нажмите любую клавишу...\n";
                    _getch();
                    running = false;
                    return;
                }
            }
            std::cout << "Нажмите любую клавишу...\n";
            _getch();
            break;
        }
    }
}

void Game::enterSpellMode() {
    if (player.getHand()->getCount() == 0) {
        std::cout << "Нет заклинаний для использования!\n";
        std::cout << "Нажмите любую клавишу...\n";
        _getch();
        return;
    }
    spellMode = true;
    selectingTarget = false;
    selectedSpell = -1;
}

void Game::exitSpellMode() {
    spellMode = false;
    selectingTarget = false;
    selectedSpell = -1;
}

void Game::handleSpellInput(char key) {
    if (!selectingTarget) {
        if (key >= '1' && key <= '9') {
            int index = key - '0';
            if (index <= player.getHand()->getCount()) {
                selectedSpell = index;
                selectingTarget = true;
                targetX = player.getX();
                targetY = player.getY();
            }
        }
        else if (key == 27) {
            exitSpellMode();
        }
    }
    else {
        int newX = targetX;
        int newY = targetY;
        
        switch(key) {
            case 'w': newY--; break;
            case 's': newY++; break;
            case 'a': newX--; break;
            case 'd': newX++; break;
            case 13:
                if (player.getHand()->useSpell(selectedSpell - 1, targetX, targetY, 
                                              field, enemies, player)) {
                    turnUsed = true;
                    
                    if (getAliveEnemiesCount() == 0) {
                        std::cout << "\nВЫ ПОБЕДИЛИ! Все враги уничтожены!\n";
                        std::cout << "Нажмите любую клавишу...\n";
                        _getch();
                        running = false;
                        return;
                    }
                }
                exitSpellMode();
                return;
            case 27:
                selectingTarget = false;
                return;
        }
        
        if (field.isValidPosition(newX, newY)) {
            targetX = newX;
            targetY = newY;
        }
    }
}

void Game::enemyTurn() {
    std::cout << "\n--- Ход врагов ---\n";
    
    for (auto& enemy : enemies) {
        if (!enemy.isAlive()) continue;
        
        int oldX = enemy.getX();
        int oldY = enemy.getY();
        
        enemy.moveTowardsPlayer(player.getX(), player.getY());
        
        int newX = enemy.getX();
        int newY = enemy.getY();
        
        if (newX == player.getX() && newY == player.getY()) {
            player.takeDamage(enemy.getDamage());
            enemy.setPosition(oldX, oldY);
        }
        else if (field.isCellEmpty(newX, newY)) {
            field.clearCell(oldX, oldY);
            field.placeEnemy(newX, newY);
        } else {
            enemy.setPosition(oldX, oldY);
        }
    }
    
    std::cout << "Ход врагов завершен. Нажмите любую клавишу...\n";
    _getch();
    
    player.resetTurn();
    turnUsed = false;
}

bool Game::isRunning() { 
    if (!player.isAlive()) {
        std::cout << "\n=== ИГРОК ПОГИБ ===\n";
        std::cout << "Финальный счет: " << player.getScore() << std::endl;
        std::cout << "Нажмите любую клавишу для выхода...\n";
        _getch();
        return false;
    }
    
    if (getAliveEnemiesCount() == 0 && running) {
        std::cout << "\nВЫ ПОБЕДИЛИ! Все враги уничтожены!\n";
        std::cout << "Нажмите любую клавишу...\n";
        _getch();
        return false;
    }
    
    return running; 
}

bool Game::isTurnUsed() const { return turnUsed; }

void Game::saveToFile() {
    GameSaveData data = getSaveData();
    SaveManager saver;
    saver.saveGame(data);
    std::cout << "\nИгра сохранена!\n";
    std::cout << "Нажмите любую клавишу...\n";
    _getch();
}

GameSaveData Game::getSaveData() const {
    GameSaveData data;
    
    data.width = field.getWidth();
    data.height = field.getHeight();
    
    data.playerX = player.getX();
    data.playerY = player.getY();
    data.playerHealth = player.getHealth();
    data.playerScore = player.getScore();
    data.playerKills = player.getCurrentKills();
    
    data.spells = player.getSpellNames();
    
    for (const auto& enemy : enemies) {
        if (enemy.isAlive()) {
            data.enemies.push_back(EnemySaveData(
                enemy.getX(),
                enemy.getY(),
                enemy.getHealth()
            ));
        }
    }
    
    return data;
}

void Game::loadFromSave(const GameSaveData& data) {
    field = GameField(data.width, data.height);
    
    player = Player(data.playerX, data.playerY, data.playerHealth, 
                    data.playerScore, data.playerKills);
    
    player.setSpells(data.spells);
    
    enemies.clear();
    for (const auto& ed : data.enemies) {
        Enemy enemy(ed.x, ed.y, ed.health, DEFAULT_ENEMY_DAMAGE);
        enemies.push_back(enemy);
        field.placeEnemy(ed.x, ed.y);
    }
    
    field.placePlayer(data.playerX, data.playerY);
    
    running = true;
    spellMode = false;
    selectingTarget = false;
    selectedSpell = -1;
    turnUsed = false;
}

void GameLauncher::run() {
    try {
        system("cls");
        std::cout << "Введите размер поля (ширина высота) от " 
             << MIN_FIELD_SIZE << " до " << MAX_FIELD_SIZE << ": ";
        
        int width, height;
        std::cin >> width >> height;
        
        Game game(width, height);
        
        while (game.isRunning()) {
            game.display();
            
            char key = _getch();
            game.handleInput(key);
            
            if (game.isRunning() && game.isTurnUsed()) {
                game.enemyTurn();
            }
        }
        
    } catch (const std::exception& e) {
        std::cout << "Ошибка: " << e.what() << std::endl;
        std::cout << "Нажмите любую клавишу...\n";
        _getch();
    }
}

void GameLauncher::loadGame(const std::string& filename) {
    try {
        SaveManager saver;
        GameSaveData data = saver.loadGame(filename);
        
        Game game(10, 10);
        game.loadFromSave(data);
        
        while (game.isRunning()) {
            game.display();
            
            char key = _getch();
            game.handleInput(key);
            
            if (game.isRunning() && game.isTurnUsed()) {
                game.enemyTurn();
            }
        }
        
    } catch (const LoadException& e) {
        std::cout << "\nОшибка загрузки: " << e.what() << "\n";
        std::cout << "Нажмите любую клавишу...\n";
        _getch();
    }
}