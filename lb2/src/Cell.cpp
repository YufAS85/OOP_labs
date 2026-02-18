#include "Cell.h"

Cell::Cell() : symbol('.'), hasEnemy(false), hasPlayer(false) {}

Cell::Cell(const Cell& other) 
    : symbol(other.symbol), hasEnemy(other.hasEnemy), hasPlayer(other.hasPlayer) {}

Cell::Cell(Cell&& other) noexcept
    : symbol(other.symbol), hasEnemy(other.hasEnemy), hasPlayer(other.hasPlayer) {
    other.symbol = '.';
    other.hasEnemy = false;
    other.hasPlayer = false;
}

Cell& Cell::operator=(const Cell& other) {
    if (this != &other) {
        symbol = other.symbol;
        hasEnemy = other.hasEnemy;
        hasPlayer = other.hasPlayer;
    }
    return *this;
}

Cell& Cell::operator=(Cell&& other) noexcept {
    if (this != &other) {
        symbol = other.symbol;
        hasEnemy = other.hasEnemy;
        hasPlayer = other.hasPlayer;
        other.symbol = '.';
        other.hasEnemy = false;
        other.hasPlayer = false;
    }
    return *this;
}

char Cell::getSymbol() const { return symbol; }

bool Cell::isEmpty() const { 
    return symbol == '.' && !hasEnemy && !hasPlayer; 
}

bool Cell::isEnemy() const { return hasEnemy; }
bool Cell::isPlayer() const { return hasPlayer; }

void Cell::setEnemy(bool present) {
    hasEnemy = present;
    if (present) symbol = 'E';
    else if (!hasPlayer) symbol = '.';
}

void Cell::setPlayer(bool present) {
    hasPlayer = present;
    if (present) symbol = 'P';
    else if (!hasEnemy) symbol = '.';
}