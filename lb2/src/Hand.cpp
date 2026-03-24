#include "Hand.h"
#include "DamageSpell.h"
#include "AreaSpell.h"
#include "Player.h"
#include "GameField.h" 
#include "Enemy.h"
#include "SpellView.h"
#include <iostream>
#include <cstdlib>
#include <conio.h>

Hand::Hand(int size) : maxSize(size) {
    addRandomSpell();
}

Hand::Hand(const Hand& other) : maxSize(other.maxSize) {
    for (ISpell* spell : other.spells) {
        spells.push_back(spell->clone());  
    }
}

Hand& Hand::operator=(const Hand& other) {
    if (this != &other) {
        for (ISpell* spell : spells) {
            delete spell;
        }
        spells.clear();
        
        maxSize = other.maxSize;
        for (ISpell* spell : other.spells) {
            spells.push_back(spell->clone());
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
    for (ISpell* spell : spells) {
        delete spell;
    }
}

bool Hand::hasSpellOfType(int type) {
    for (ISpell* spell : spells) {
        if (type == 0 && spell->getName() == "Огненная стрела") return true;
        if (type == 1 && spell->getName() == "Взрывная волна") return true;
    }
    return false;
}

bool Hand::addSpell(ISpell* spell) {
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
        return false;
    }
    
    ISpell* spell = spells[index];
    
    Spell* concreteSpell = dynamic_cast<Spell*>(spell);
    if (concreteSpell && concreteSpell->isUsed()) {
        std::cout << "Это заклинание уже использовано в этот ход!\n";
        std::cout << "Нажмите любую клавишу для продолжения...\n";
        _getch();
        return false;
    }
    
    int playerX = player.getX();
    int playerY = player.getY();
    
    if (!spell->canCast(playerX, playerY, targetX, targetY)) {
        int distance = abs(playerX - targetX) + abs(playerY - targetY);
        SpellView::showCannotCast(distance, spell->getRange());
        return false;
    }
    
    spell->cast(targetX, targetY, field, enemies, player);
    
    if (concreteSpell) {
        concreteSpell->setUsed(true);
    }
    
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
        
        Spell* concreteSpell = dynamic_cast<Spell*>(spells[i]);
        if (concreteSpell && concreteSpell->isUsed()) {
            std::cout << " [ИСПОЛЬЗОВАНО]";
        }
        std::cout << "\n";
    }
}

void Hand::resetTurn() {
    for (auto spell : spells) {
        Spell* concreteSpell = dynamic_cast<Spell*>(spell);
        if (concreteSpell) {
            concreteSpell->setUsed(false);
        }
    }
}

int Hand::getCount() const { return spells.size(); }