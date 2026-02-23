#ifndef HAND_H
#define HAND_H

#include "Spell.h"
#include <vector>

class Hand {
private:
    std::vector<Spell*> spells;
    int maxSize;
    
public:
    Hand(int size);
    Hand(const Hand& other);
    Hand(Hand&& other) noexcept;
    Hand& operator=(const Hand& other);
    Hand& operator=(Hand&& other) noexcept;
    ~Hand();
    
    bool addSpell(Spell* spell);
    void addRandomSpell();
    
    std::vector<std::string> getSpellNames() const;
    void setSpellsFromNames(const std::vector<std::string>& spellNames);
    
    bool useSpell(int index, int targetX, int targetY, 
                  GameField& field, std::vector<Enemy>& enemies, Player& player);
    
    void display() const;
    void resetTurn();
    int getCount() const;
};

#endif