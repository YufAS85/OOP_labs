#include "AreaSpell.h"
#include "Player.h"
#include "GameField.h" 
#include "Enemy.h"
#include <iostream>
#include <conio.h>

AreaSpell::AreaSpell() : Spell("Взрывная волна", 4), damage(15), areaSize(2) {}

SpellCastResult AreaSpell::getCastResult(int targetX, int targetY,
                                          GameField& field,
                                          std::vector<Enemy>& enemies) const {
    SpellCastResult result;
    result.targetX = targetX;
    result.targetY = targetY;
    result.damageDealt = 0;
    result.enemiesHit = 0;
    result.success = false;
    result.message = "Область применена";
    
    // Проверяем область 2x2
    for (int dx = 0; dx < areaSize; dx++) {
        for (int dy = 0; dy < areaSize; dy++) {
            int checkX = targetX + dx;
            int checkY = targetY + dy;
            
            if (!field.isValidPosition(checkX, checkY)) continue;
            
            for (auto& enemy : enemies) {
                if (enemy.isAlive() && enemy.getX() == checkX && enemy.getY() == checkY) {
                    result.success = true;
                    result.damageDealt += damage;
                    result.enemiesHit++;
                    result.message = "Нанесен урон по области";
                    break;
                }
            }
        }
    }
    
    if (result.enemiesHit == 0) {
        result.message = "В области нет врагов. Заклинание потрачено впустую";
    }
    
    return result;
}

void AreaSpell::cast(int targetX, int targetY, 
                     GameField& field, 
                     std::vector<Enemy>& enemies, 
                     Player& player) {
    auto result = getCastResult(targetX, targetY, field, enemies);
    
    if (result.success) {
        // Наносим урон всем врагам в области
        for (int dx = 0; dx < areaSize; dx++) {
            for (int dy = 0; dy < areaSize; dy++) {
                int checkX = targetX + dx;
                int checkY = targetY + dy;
                
                if (!field.isValidPosition(checkX, checkY)) continue;
                
                for (auto& enemy : enemies) {
                    if (enemy.isAlive() && enemy.getX() == checkX && enemy.getY() == checkY) {
                        enemy.takeDamage(damage);
                        
                        if (!enemy.isAlive()) {
                            field.clearCell(checkX, checkY);
                            player.addScore(10);
                        }
                        break;
                    }
                }
            }
        }
    }
    
    usedThisTurn = true;
}