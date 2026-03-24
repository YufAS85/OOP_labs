#ifndef DAMAGE_SPELL_H
#define DAMAGE_SPELL_H

#include "Spell.h"
#include "SpellCastResult.h"

class DamageSpell : public Spell {
private:
    int damage;
    
public:
    DamageSpell();
    void cast(int targetX, int targetY, 
              GameField& field, 
              std::vector<Enemy>& enemies, 
              Player& player) override;
    
    SpellCastResult getCastResult(int targetX, int targetY,
                                   GameField& field,
                                   std::vector<Enemy>& enemies) const;
    
    ISpell* clone() const override { return new DamageSpell(*this); }
};

#endif