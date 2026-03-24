#ifndef SPELL_H
#define SPELL_H

#include "ISpell.h"

class Spell : public ISpell {
protected:
    std::string name;
    int range;
    bool usedThisTurn;
    
public:
    Spell(const std::string& n, int r);
    virtual ~Spell() = default;
    
    std::string getName() const override;
    int getRange() const override;
    std::string getDescription() const override;
    bool canCast(int playerX, int playerY, int targetX, int targetY) const override;
    
    bool isUsed() const;
    void setUsed(bool used);
};

#endif