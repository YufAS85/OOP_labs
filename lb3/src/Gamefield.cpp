#include "GameField.h"
#include <iostream>
#include <stdexcept>

extern const int MIN_FIELD_SIZE;
extern const int MAX_FIELD_SIZE;

GameField::GameField() : width(0), height(0) {}

GameField::GameField(int w, int h) : width(w), height(h) {
    if (w < MIN_FIELD_SIZE || w > MAX_FIELD_SIZE || h < MIN_FIELD_SIZE || h > MAX_FIELD_SIZE) {
        throw std::invalid_argument("Размер поля должен быть от " + std::to_string(MIN_FIELD_SIZE) + " до " + std::to_string(MAX_FIELD_SIZE));
    }
    grid.resize(height, std::vector<Cell>(width));
}

GameField::GameField(const GameField& other) 
    : width(other.width), height(other.height), grid(other.grid) {}

GameField& GameField::operator=(const GameField& other) {
    if (this != &other) {
        width = other.width;
        height = other.height;
        grid = other.grid;
    }
    return *this;
}

GameField::GameField(GameField&& other) noexcept
    : width(other.width), height(other.height), grid(std::move(other.grid)) {
    other.width = 0;
    other.height = 0;
}

GameField& GameField::operator=(GameField&& other) noexcept {
    if (this != &other) {
        width = other.width;
        height = other.height;
        grid = std::move(other.grid);
        other.width = 0;
        other.height = 0;
    }
    return *this;
}

int GameField::getWidth() const { return width; }
int GameField::getHeight() const { return height; }

bool GameField::isValidPosition(int x, int y) const {
    return x >= 0 && x < width && y >= 0 && y < height;
}

void GameField::placePlayer(int x, int y) {
    if (isValidPosition(x, y)) {
        grid[y][x].setPlayer(true);
    }
}

void GameField::placeEnemy(int x, int y) {
    if (isValidPosition(x, y)) {
        grid[y][x].setEnemy(true);
    }
}

void GameField::clearCell(int x, int y) {
    if (isValidPosition(x, y)) {
        grid[y][x].setPlayer(false);
        grid[y][x].setEnemy(false);
    }
}

void GameField::clearAll() {
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            grid[y][x].setPlayer(false);
            grid[y][x].setEnemy(false);
        }
    }
}

bool GameField::isCellEmpty(int x, int y) const {
    if (!isValidPosition(x, y)) return false;
    return grid[y][x].isEmpty();
}

bool GameField::isCellEnemy(int x, int y) const {
    if (!isValidPosition(x, y)) return false;
    return grid[y][x].isEnemy();
}

void GameField::display() const {
    std::cout << "\n  ";
    for (int x = 0; x < width; x++) {
        std::cout << x % 10 << " ";
    }
    std::cout << "\n";
    
    for (int y = 0; y < height; y++) {
        std::cout << y % 10 << " ";
        for (int x = 0; x < width; x++) {
            std::cout << grid[y][x].getSymbol() << " ";
        }
        std::cout << "\n";
    }
}