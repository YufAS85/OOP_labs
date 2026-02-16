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
    GameField(int w, int h);
    GameField(const GameField& other);
    GameField(GameField&& other) noexcept;
    GameField& operator=(const GameField& other);
    GameField& operator=(GameField&& other) noexcept;
    ~GameField() = default;
    
    int getWidth() const;
    int getHeight() const;
    
    void placePlayer(int x, int y);
    void placeEnemy(int x, int y);
    void clearCell(int x, int y);
    
    bool isCellEmpty(int x, int y) const;
    bool isCellEnemy(int x, int y) const;
    
    void display() const;
};

#endif // GAME_FIELD_H