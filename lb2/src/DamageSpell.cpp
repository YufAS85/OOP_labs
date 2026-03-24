#include "DamageSpell.h"
#include "GameField.h"
#include "Player.h"
#include "Enemy.h"

DamageSpell::DamageSpell() : Spell("Огненная стрела", 3), damage(25) {}

SpellCastResult DamageSpell::getCastResult(int targetX, int targetY,
                                            GameField& field,
                                            std::vector<Enemy>& enemies) const {
    SpellCastResult result;
    result.targetX = targetX;
    result.targetY = targetY;
    result.damageDealt = 0;
    result.enemiesHit = 0;
    result.success = false;
    
    if (!field.isCellEnemy(targetX, targetY)) {
        result.message = "Нет врага в целевой клетке!";
        return result;
    }
    
    for (auto& enemy : enemies) {
        if (enemy.isAlive() && enemy.getX() == targetX && enemy.getY() == targetY) {
            result.success = true;
            result.damageDealt = damage;
            result.enemiesHit = 1;
            result.message = "Враг получил " + std::to_string(damage) + " урона";
            break;
        }
    }
    
    return result;
}

void DamageSpell::cast(int targetX, int targetY, 
                       GameField& field, 
                       std::vector<Enemy>& enemies, 
                       Player& player) {
    auto result = getCastResult(targetX, targetY, field, enemies);
    
    if (result.success) {
        for (auto& enemy : enemies) {
            if (enemy.isAlive() && enemy.getX() == targetX && enemy.getY() == targetY) {
                int oldHealth = enemy.getHealth();
                enemy.takeDamage(damage);
                
                if (!enemy.isAlive()) {
                    field.clearCell(targetX, targetY);
                    player.addScore(10);
                    result.enemyKilled = true;
                }
                break;
            }
        }
    }
    
    usedThisTurn = true;
}

