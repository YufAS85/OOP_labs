#include "Hand.h"
#include "DamageSpell.h"
#include "AreaSpell.h"
#include "Player.h"
#include "Enemy.h"
#include <iostream>
#include <cstdlib>
#include <conio.h>

Hand::Hand(int size) : maxSize(size) {
    addRandomSpell();
}

Hand::Hand(const Hand& other) : maxSize(other.maxSize) {
    for (Spell* spell : other.spells) {
        if (dynamic_cast<DamageSpell*>(spell)) {
            spells.push_back(new DamageSpell(*dynamic_cast<DamageSpell*>(spell)));
        } else if (dynamic_cast<AreaSpell*>(spell)) {
            spells.push_back(new AreaSpell(*dynamic_cast<AreaSpell*>(spell)));
        }
    }
}

Hand& Hand::operator=(const Hand& other) {
    if (this != &other) {
        for (Spell* spell : spells) {
            delete spell;
        }
        spells.clear();
        
        maxSize = other.maxSize;
        for (Spell* spell : other.spells) {
            if (dynamic_cast<DamageSpell*>(spell)) {
                spells.push_back(new DamageSpell(*dynamic_cast<DamageSpell*>(spell)));
            } else if (dynamic_cast<AreaSpell*>(spell)) {
                spells.push_back(new AreaSpell(*dynamic_cast<AreaSpell*>(spell)));
            }
        }
    }
    return *this;
}

Hand::Hand(Hand&& other) noexcept
    : spells(std::move(other.spells)), maxSize(other.maxSize) {}

Hand& Hand::operator=(Hand&& other) noexcept {
    if (this != &other) {
        spells = std::move(other.spells);
        maxSize = other.maxSize;
    }
    return *this;
}

Hand::~Hand() {
    for (Spell* spell : spells) {
        delete spell;
    }
}

bool Hand::hasSpellOfType(int type) {
    for (Spell* spell : spells) {
        if (type == 0 && dynamic_cast<DamageSpell*>(spell)) return true;
        if (type == 1 && dynamic_cast<AreaSpell*>(spell)) return true;
    }
    return false;
}

bool Hand::addSpell(Spell* spell) {
    if (spells.size() >= maxSize) {
        std::cout << "Рука полна! Нельзя добавить новое заклинание.\n";
        delete spell;
        return false;
    }
    
    spells.push_back(spell);
    std::cout << "Добавлено заклинание: " << spell->getName() << "\n";
    std::cout << "Заклинаний в руке: " << spells.size() << "/" << maxSize << "\n";
    return true;
}

void Hand::addRandomSpell() {
    if (spells.size() >= maxSize) return;
    
    if (spells.size() == 1) {
        bool hasDamage = hasSpellOfType(0);
        if (hasDamage) {
            addSpell(new AreaSpell());
            return;
        } else {
            addSpell(new DamageSpell());
            return;
        }
    }
    
    int type = rand() % 2;
    if (type == 0) {
        addSpell(new DamageSpell());
    } else {
        addSpell(new AreaSpell());
    }
}

bool Hand::useSpell(int index, int targetX, int targetY, 
                  GameField& field, std::vector<Enemy>& enemies, Player& player) {
    if (index < 0 || index >= spells.size()) {
        std::cout << "Неверный индекс заклинания!\n";
        std::cout << "Нажмите любую клавишу для продолжения...\n";
        _getch();
        return false;
    }
    
    Spell* spell = spells[index];
    
    if (spell->isUsed()) {
        std::cout << "Это заклинание уже использовано в этот ход!\n";
        std::cout << "Нажмите любую клавишу для продолжения...\n";
        _getch();
        return false;
    }
    
    int playerX = player.getX();
    int playerY = player.getY();
    
    std::cout << "\nПроверка дальности:\n";
    std::cout << "Игрок: (" << playerX << "," << playerY << ")\n";
    std::cout << "Цель: (" << targetX << "," << targetY << ")\n";
    
    if (!spell->canUse(playerX, playerY, targetX, targetY)) {
        int distance = abs(playerX - targetX) + abs(playerY - targetY);
        std::cout << "Цель вне радиуса! Расстояние: " << distance 
             << ", радиус заклинания: " << spell->getRange() << "\n";
        std::cout << "Нажмите любую клавишу для продолжения...\n";
        _getch();
        return false;
    }
    
    std::cout << "Цель в радиусе действия\n";
    
    spell->use(targetX, targetY, field, enemies, player);
    return true;
}

void Hand::display() const {
    if (spells.empty()) {
        std::cout << "Рука пуста.\n";
        return;
    }
    
    std::cout << "\n--- Рука игрока ---\n";
    for (size_t i = 0; i < spells.size(); i++) {
        std::cout << i + 1 << ". " << spells[i]->getDescription();
        if (spells[i]->isUsed()) {
            std::cout << " [ИСПОЛЬЗОВАНО]";
        }
        std::cout << "\n";
    }
}

void Hand::resetTurn() {
    for (auto spell : spells) {
        spell->setUsed(false);
    }
}

int Hand::getCount() const { return spells.size(); }