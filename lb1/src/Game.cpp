#include "Game.h"
#include <iostream>
#include <cstdlib>
#include <algorithm>

Game::Game(int width, int height) 
    : field(width, height), 
      player(width/2, height/2),
      running(true) {
    
    field.placePlayer(player.getX(), player.getY());
    
    // Создаем 3 врагов
    for (int i = 0; i < 3; i++) {
        int x, y;
        do {
            x = rand() % width;
            y = rand() % height;
        } while (!field.isCellEmpty(x, y));
        
        enemies.push_back(Enemy(x, y));
        field.placeEnemy(x, y);
    }
}

void Game::display() {
    field.display();
    std::cout << "Здоровье: " << player.getHealth() 
              << " | Урон: " << player.getDamage()
              << " | Очки: " << player.getScore() << std::endl;
    std::cout << "Врагов осталось: " << getAliveEnemiesCount() << std::endl;
    std::cout << "Команды: w/a/s/d - движение, q - выход\n";
}

int Game::getAliveEnemiesCount() const {
    int count = 0;
    for (const auto& enemy : enemies) {
        if (enemy.isAlive()) count++;
    }
    return count;
}

void Game::attackEnemyAt(int x, int y) {
    for (auto& enemy : enemies) {
        if (enemy.isAlive() && enemy.getX() == x && enemy.getY() == y) {
            std::cout << "Атака! Нанесен урон врагу!\n";
            enemy.takeDamage(player.getDamage());
            if (!enemy.isAlive()) {
                field.clearCell(x, y);
                player.addScore(10);
                std::cout << "Враг уничтожен! +10 очков\n";
            }
            break;
        }
    }
}

void Game::handleInput(char key) {
    int newX = player.getX();
    int newY = player.getY();
    
    switch(key) {
        case 'w': newY--; break;
        case 's': newY++; break;
        case 'a': newX--; break;
        case 'd': newX++; break;
        case 'q': running = false; return;
        default: return;
    }
    
    // Проверяем границы
    if (newX < 0 || newX >= field.getWidth() || 
        newY < 0 || newY >= field.getHeight()) {
        std::cout << "Нельзя выйти за границы поля!\n";
        return;
    }
    
    // Проверяем врага
    if (field.isCellEnemy(newX, newY)) {
        attackEnemyAt(newX, newY);
        return;
    }
    
    // Перемещение
    if (field.isCellEmpty(newX, newY)) {
        field.clearCell(player.getX(), player.getY());
        player.setPosition(newX, newY);
        field.placePlayer(player.getX(), player.getY());
    } else {
        std::cout << "Туда нельзя!\n";
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
            std::cout << "Враг атаковал! Нанесено " 
                      << enemy.getDamage() << " урона\n";
            enemy.setPosition(oldX, oldY);
        }
        else if (field.isCellEmpty(newX, newY)) {
            field.clearCell(oldX, oldY);
            field.placeEnemy(newX, newY);
        } else {
            enemy.setPosition(oldX, oldY);
        }
    }
}

bool Game::isRunning() { 
    if (!player.isAlive()) {
        std::cout << "\n=== ИГРОК ПОГИБ ===\n";
        std::cout << "Финальный счет: " << player.getScore() << std::endl;
        return false;
    }
    return running; 
}