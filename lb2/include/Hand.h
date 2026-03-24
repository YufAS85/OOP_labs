#ifndef HAND_H
#define HAND_H

#include "ISpell.h"
#include <vector>

class GameField;
class Enemy;
class Player;

class Hand {
private:
    std::vector<ISpell*> spells;  
    int maxSize;
    
public:
    Hand(int size);
    Hand(const Hand& other);
    Hand(Hand&& other) noexcept;
    Hand& operator=(const Hand& other);
    Hand& operator=(Hand&& other) noexcept;
    ~Hand();
    
    bool addSpell(ISpell* spell);
    void addRandomSpell();
    bool useSpell(int index, int targetX, int targetY, 
                  GameField& field, std::vector<Enemy>& enemies, Player& player);
    void display() const;
    void resetTurn();
    int getCount() const;
    
private:
    bool hasSpellOfType(int type);
};

#endif