#ifndef CELL_H
#define CELL_H

class Cell {
private:
    char symbol;
    bool hasEnemy;
    bool hasPlayer;
    
public:
    Cell();
    Cell(const Cell& other);
    Cell(Cell&& other) noexcept;
    Cell& operator=(const Cell& other);
    Cell& operator=(Cell&& other) noexcept;
    
    char getSymbol() const;
    bool isEmpty() const;
    bool isEnemy() const;
    bool isPlayer() const;
    
    void setEnemy(bool present);
    void setPlayer(bool present);
};

#endif