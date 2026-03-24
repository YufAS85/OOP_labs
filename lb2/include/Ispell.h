#ifndef ISPELL_H
#define ISPELL_H

#include <string>
#include <vector>

class GameField;
class Player;
class Enemy;

class ISpell {
public:
    virtual ~ISpell() = default;
    
    virtual void cast(int targetX, int targetY, 
                      GameField& field, 
                      std::vector<Enemy>& enemies, 
                      Player& player) = 0;
    
    virtual std::string getName() const = 0;
    virtual int getRange() const = 0;
    virtual std::string getDescription() const = 0;
    virtual bool canCast(int playerX, int playerY, 
                         int targetX, int targetY) const = 0;
    virtual ISpell* clone() const = 0;  
};

#endif