#ifndef SPELL_CAST_RESULT_H
#define SPELL_CAST_RESULT_H

#include <string>

class SpellCastResult {
public:
    int targetX;
    int targetY;
    int damageDealt;
    int enemiesHit;
    bool success;
    bool enemyKilled;
    std::string message;
    
    SpellCastResult() 
        : targetX(0), targetY(0), damageDealt(0), 
          enemiesHit(0), success(false), enemyKilled(false) {}
};

#endif