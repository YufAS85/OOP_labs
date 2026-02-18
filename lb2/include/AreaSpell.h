#ifndef AREA_SPELL_H
#define AREA_SPELL_H

#include "Spell.h"
#include "Enemy.h"

class AreaSpell : public Spell {
private:
    int damage;
    int areaSize;
    
public:
    AreaSpell();
    void use(int targetX, int targetY, GameField& field, 
             std::vector<Enemy>& enemies, Player& player) override;
};

#endif