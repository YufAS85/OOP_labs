#include "SpellView.h"
#include <iostream>
#include <conio.h>

void SpellView::showCastResult(const SpellCastResult& result) {
    std::cout << "\n=== ПРИМЕНЕНИЕ ЗАКЛИНАНИЯ ===\n";
    std::cout << "Цель: (" << result.targetX << "," << result.targetY << ")\n";
    std::cout << result.message << "\n";
    
    if (result.success) {
        std::cout << "Нанесено урона: " << result.damageDealt << "\n";
        std::cout << "Поражено врагов: " << result.enemiesHit << "\n";
        
        if (result.enemyKilled) {
            std::cout << "Враг уничтожен! +10 очков\n";
        }
    }
    
    std::cout << "=== ЗАКЛИНАНИЕ ПРИМЕНЕНО ===\n";
    std::cout << "Нажмите любую клавишу для продолжения...\n";
    _getch();
}

void SpellView::showCannotCast(int distance, int range) {
    std::cout << "Цель вне радиуса! Расстояние: " << distance 
              << ", радиус заклинания: " << range << "\n";
    std::cout << "Нажмите любую клавишу для продолжения...\n";
    _getch();
}

void SpellView::showSpellSelection(int count) {
    std::cout << "Выберите заклинание (1-" << count 
              << ") или ESC для выхода из режима\n";
}

void SpellView::showTargetSelection(int x, int y) {
    std::cout << "Цель: (" << x << "," << y << ")\n";
    std::cout << "Перемещение: w/a/s/d, Enter - применить, ESC - отмена\n";
}

void SpellView::showEmptyHand() {
    std::cout << "Нет заклинаний для использования!\n";
    std::cout << "Нажмите любую клавишу для продолжения...\n";
    _getch();
}