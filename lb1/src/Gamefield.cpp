#include "GameField.h"
#include <iostream>
#include <stdexcept>

GameField::GameField(int w, int h) : width(w), height(h) {
    if (w < 10 || w > 25 || h < 10 || h > 25) {
        throw std::invalid_argument("Размер поля должен быть от 10 до 25");
    }
    grid.resize(height, std::vector<Cell>(width));
}

GameField::GameField(const GameField& other) 
    : width(other.width), height(other.height), grid(other.grid) {}

GameField::GameField(GameField&& other) noexcept
    : width(other.width), height(other.height), grid(std::move(other.grid)) {
    other.width = 0;
    other.height = 0;
}

GameField& GameField::operator=(const GameField& other) {
    if (this != &other) {
        width = other.width;
        height = other.height;
        grid = other.grid;
    }
    return *this;
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

void GameField::placePlayer(int x, int y) {
    if (x >= 0 && x < width && y >= 0 && y < height) {
        grid[y][x].setPlayer(true);
    }
}

void GameField::placeEnemy(int x, int y) {
    if (x >= 0 && x < width && y >= 0 && y < height) {
        grid[y][x].setEnemy(true);
    }
}

void GameField::clearCell(int x, int y) {
    if (x >= 0 && x < width && y >= 0 && y < height) {
        grid[y][x].setPlayer(false);
        grid[y][x].setEnemy(false);
    }
}

bool GameField::isCellEmpty(int x, int y) const {
    if (x < 0 || x >= width || y < 0 || y >= height) return false;
    return grid[y][x].isEmpty();
}

bool GameField::isCellEnemy(int x, int y) const {
    if (x < 0 || x >= width || y < 0 || y >= height) return false;
    return grid[y][x].isEnemy();
}

void GameField::display() const {
    std::cout << "\n";
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            std::cout << grid[y][x].getSymbol() << " ";
        }
        std::cout << "\n";
    }
}