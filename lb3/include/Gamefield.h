#ifndef GAME_FIELD_H
#define GAME_FIELD_H

#include "Cell.h"
#include <vector>

class GameField {
private:
    int width;
    int height;
    std::vector<std::vector<Cell>> grid;
    
public:
    GameField();
    GameField(int w, int h);
    GameField(const GameField& other);
    GameField(GameField&& other) noexcept;
    GameField& operator=(const GameField& other);
    GameField& operator=(GameField&& other) noexcept;
    
    int getWidth() const;
    int getHeight() const;
    bool isValidPosition(int x, int y) const;
    
    void placePlayer(int x, int y);
    void placeEnemy(int x, int y);
    void clearCell(int x, int y);
    void clearAll();
    
    bool isCellEmpty(int x, int y) const;
    bool isCellEnemy(int x, int y) const;
    
    void display() const;
};

#endif