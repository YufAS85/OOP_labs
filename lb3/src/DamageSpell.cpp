#include "DamageSpell.h"
#include "Player.h"
#include "Enemy.h" 
#include <iostream>
#include <conio.h>

extern const int SCORE_PER_KILL;
extern const int DAMAGE_SPELL_DAMAGE;

DamageSpell::DamageSpell() : Spell("Огненная стрела", 3), damage(DAMAGE_SPELL_DAMAGE) {}

void DamageSpell::use(int targetX, int targetY, GameField& field, 
                     std::vector<Enemy>& enemies, Player& player) {
    std::cout << "\n=== ПРИМЕНЕНИЕ ЗАКЛИНАНИЯ ===\n";
    std::cout << "Заклинание: " << name << "\n";
    std::cout << "Цель: (" << targetX << "," << targetY << ")\n";
    
    if (!field.isCellEnemy(targetX, targetY)) {
        std::cout << "Нет врага в целевой клетке! Заклинание не сработало.\n";
        std::cout << "Нажмите любую клавишу для продолжения...\n";
        _getch();
        return;
    }
    
    for (auto& enemy : enemies) {
        if (enemy.isAlive() && enemy.getX() == targetX && enemy.getY() == targetY) {
            int oldHealth = enemy.getHealth();
            std::cout << "Враг найден! Текущее здоровье: " << oldHealth << "\n";
            std::cout << "Наносится " << damage << " урона!\n";
            
            enemy.takeDamage(damage);
            
            if (!enemy.isAlive()) {
                std::cout << "Враг уничтожен! +" << SCORE_PER_KILL << " очков\n";
                field.clearCell(targetX, targetY);
                player.addScore(SCORE_PER_KILL);
            } else {
                std::cout << "У врага осталось здоровья: " << enemy.getHealth() << "\n";
            }
            break;
        }
    }
    usedThisTurn = true;
    std::cout << "=== ЗАКЛИНАНИЕ ПРИМЕНЕНО ===\n";
    std::cout << "Нажмите любую клавишу для продолжения...\n";
    _getch();
}