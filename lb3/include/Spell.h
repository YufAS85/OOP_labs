#ifndef SPELL_H
#define SPELL_H

#include <string>
#include <vector>
#include "GameField.h"

class Player;
class Enemy;

class Spell {
protected:
    std::string name;
    int range;
    bool usedThisTurn;
    
public:
    Spell(const std::string& n, int r);
    virtual ~Spell();
    
    virtual void use(int targetX, int targetY, GameField& field, 
                     std::vector<Enemy>& enemies, Player& player) = 0;
    
    virtual std::string getDescription() const;
    
    std::string getName() const;
    int getRange() const;
    bool isUsed() const;
    void setUsed(bool used);
    
    bool canUse(int playerX, int playerY, int targetX, int targetY) const;
};

#endif