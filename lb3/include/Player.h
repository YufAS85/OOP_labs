#ifndef PLAYER_H
#define PLAYER_H

#include "Hand.h"
#include <vector>
#include <string>

class Player {
private:
    int health;
    int damage;
    int score;
    int x, y;
    Hand* hand;
    int killsForNewSpell;
    int currentKills;
    
public:
    Player();
    Player(int startX, int startY);
    Player(int startX, int startY, int startHealth, int startScore, int startKills);
    Player(const Player& other);
    Player(Player&& other) noexcept;
    Player& operator=(const Player& other);
    Player& operator=(Player&& other) noexcept;
    ~Player();
    
    int getX() const;
    int getY() const;
    int getHealth() const;
    int getDamage() const;
    int getScore() const;
    Hand* getHand() const;
    int getCurrentKills() const;
    int getKillsNeeded() const;
    
    void setPosition(int newX, int newY);
    void takeDamage(int amount);
    void addScore(int points);
    bool isAlive() const;
    
    void onEnemyKilled();
    void resetTurn();
    
    std::vector<std::string> getSpellNames() const;
    void setSpells(const std::vector<std::string>& spellNames);
};

#endif