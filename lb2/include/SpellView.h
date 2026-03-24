#ifndef SPELL_VIEW_H
#define SPELL_VIEW_H

#include "SpellCastResult.h"
#include <iostream>
#include <string>

class SpellView {
private:
    std::ostream& output;
    
public:
    SpellView(std::ostream& out = std::cout) : output(out) {}
    
    static void showCastResult(const SpellCastResult& result);
    static void showCannotCast(int distance, int range);
    static void showSpellSelection(int count);
    static void showTargetSelection(int x, int y);
    static void showEmptyHand();
};

#endif