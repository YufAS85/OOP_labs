#include "Spell.h"
#include <cmath>

Spell::Spell(const std::string& n, int r) : name(n), range(r), usedThisTurn(false) {}

Spell::~Spell() {}

std::string Spell::getDescription() const {
    return name + " (радиус: " + std::to_string(range) + ")";
}

std::string Spell::getName() const { return name; }
int Spell::getRange() const { return range; }
bool Spell::isUsed() const { return usedThisTurn; }
void Spell::setUsed(bool used) { usedThisTurn = used; }

bool Spell::canUse(int playerX, int playerY, int targetX, int targetY) const {
    int distance = abs(playerX - targetX) + abs(playerY - targetY);
    return distance <= range;
}