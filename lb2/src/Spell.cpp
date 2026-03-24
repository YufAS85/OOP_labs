#include "Spell.h"
#include <cmath>

Spell::Spell(const std::string& n, int r) 
    : name(n), range(r), usedThisTurn(false) {}

std::string Spell::getName() const { 
    return name; 
}

int Spell::getRange() const { 
    return range; 
}

std::string Spell::getDescription() const {
    return name + " (радиус: " + std::to_string(range) + ")";
}

bool Spell::canCast(int playerX, int playerY, int targetX, int targetY) const {
    int distance = std::abs(playerX - targetX) + std::abs(playerY - targetY);
    return distance <= range;
}

bool Spell::isUsed() const { 
    return usedThisTurn; 
}

void Spell::setUsed(bool used) { 
    usedThisTurn = used; 
}