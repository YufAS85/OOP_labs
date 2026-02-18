#ifndef DAMAGE_SPELL_H
#define DAMAGE_SPELL_H

#include "Spell.h"
#include "Enemy.h"

class DamageSpell : public Spell {
private:
    int damage;
    
public:
    DamageSpell();
    void use(int targetX, int targetY, GameField& field, 
             std::vector<Enemy>& enemies, Player& player) override;
};

#endif