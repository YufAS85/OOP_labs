#include "AreaSpell.h"
#include "Player.h"
#include "Enemy.h"
#include <iostream>
#include <conio.h>

extern const int SCORE_PER_KILL;
extern const int AREA_SPELL_DAMAGE;

AreaSpell::AreaSpell() : Spell("Взрывная волна", 4), damage(AREA_SPELL_DAMAGE), areaSize(2) {}

void AreaSpell::use(int targetX, int targetY, GameField& field, 
                   std::vector<Enemy>& enemies, Player& player) {
    std::cout << "\n=== ПРИМЕНЕНИЕ ЗАКЛИНАНИЯ ===\n";
    std::cout << "Заклинание: " << name << "\n";
    std::cout << "Центр области: (" << targetX << "," << targetY << ")\n";
    std::cout << "Область поражения: " << areaSize << "x" << areaSize << "\n";
    
    int enemiesHit = 0;
    int totalDamage = 0;
    
    for (int dx = 0; dx < areaSize; dx++) {
        for (int dy = 0; dy < areaSize; dy++) {
            int checkX = targetX + dx;
            int checkY = targetY + dy;
            
            if (!field.isValidPosition(checkX, checkY)) continue;
            
            for (auto& enemy : enemies) {
                if (enemy.isAlive() && enemy.getX() == checkX && enemy.getY() == checkY) {
                    enemiesHit++;
                    totalDamage += damage;
                    
                    std::cout << "Враг в клетке (" << checkX << "," << checkY 
                         << ") получил " << damage << " урона!\n";
                    
                    enemy.takeDamage(damage);
                    
                    if (!enemy.isAlive()) {
                        std::cout << "  Враг уничтожен!\n";
                        field.clearCell(checkX, checkY);
                        player.addScore(SCORE_PER_KILL);
                    }
                    break;
                }
            }
        }
    }
    
    if (enemiesHit == 0) {
        std::cout << "В области нет врагов. Заклинание потрачено впустую.\n";
    } else {
        std::cout << "Всего поражено врагов: " << enemiesHit << "\n";
        std::cout << "Суммарный урон: " << totalDamage << "\n";
    }
    
    usedThisTurn = true;
    std::cout << "=== ЗАКЛИНАНИЕ ПРИМЕНЕНО ===\n";
    std::cout << "Нажмите любую клавишу для продолжения...\n";
    _getch();
}