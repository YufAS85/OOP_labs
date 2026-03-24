#ifndef AREA_SPELL_H
#define AREA_SPELL_H

#include "Spell.h"
#include "SpellCastResult.h"

class AreaSpell : public Spell {
private:
    int damage;
    int areaSize;
    
public:
    AreaSpell();
    void cast(int targetX, int targetY, 
              GameField& field, 
              std::vector<Enemy>& enemies, 
              Player& player) override;
    
    SpellCastResult getCastResult(int targetX, int targetY,
                                   GameField& field,
                                   std::vector<Enemy>& enemies) const;
    
    ISpell* clone() const override { return new AreaSpell(*this); }
};

#endif