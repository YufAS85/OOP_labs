#include "Player.h"
#include <iostream>

Player::Player(int startX, int startY) 
    : health(100), damage(10), score(0), x(startX), y(startY),
      hand(new Hand(5)), killsForNewSpell(3), currentKills(0) {}

Player::Player(const Player& other)
    : health(other.health), damage(other.damage), 
      score(other.score), x(other.x), y(other.y),
      hand(new Hand(*other.hand)),
      killsForNewSpell(other.killsForNewSpell),
      currentKills(other.currentKills) {}

Player::Player(Player&& other) noexcept
    : health(other.health), damage(other.damage),
      score(other.score), x(other.x), y(other.y),
      hand(other.hand),
      killsForNewSpell(other.killsForNewSpell),
      currentKills(other.currentKills) {
    other.health = 0;
    other.x = -1;
    other.y = -1;
    other.hand = nullptr;
}

Player& Player::operator=(const Player& other) {
    if (this != &other) {
        health = other.health;
        damage = other.damage;
        score = other.score;
        x = other.x;
        y = other.y;
        
        delete hand;
        hand = new Hand(*other.hand);
        
        killsForNewSpell = other.killsForNewSpell;
        currentKills = other.currentKills;
    }
    return *this;
}

Player& Player::operator=(Player&& other) noexcept {
    if (this != &other) {
        health = other.health;
        damage = other.damage;
        score = other.score;
        x = other.x;
        y = other.y;
        
        delete hand;
        hand = other.hand;
        
        killsForNewSpell = other.killsForNewSpell;
        currentKills = other.currentKills;
        
        other.health = 0;
        other.x = -1;
        other.y = -1;
        other.hand = nullptr;
    }
    return *this;
}

Player::~Player() {
    delete hand;
}

int Player::getX() const { return x; }
int Player::getY() const { return y; }
int Player::getHealth() const { return health; }
int Player::getDamage() const { return damage; }
int Player::getScore() const { return score; }
Hand* Player::getHand() const { return hand; }
int Player::getCurrentKills() const { return currentKills; }
int Player::getKillsNeeded() const { return killsForNewSpell; }

void Player::setPosition(int newX, int newY) {
    x = newX;
    y = newY;
}

void Player::takeDamage(int amount) {
    health -= amount;
    if (health < 0) health = 0;
    std::cout << "Игрок получил " << amount << " урона! Здоровье: " << health << std::endl;
}

void Player::addScore(int points) {
    score += points;
    std::cout << "Получено очков: " << points << ". Всего: " << score << "\n";
    onEnemyKilled();
}

bool Player::isAlive() const { return health > 0; }

void Player::onEnemyKilled() {
    currentKills++;
    std::cout << "Прогресс убийств: " << currentKills << "/" << killsForNewSpell << "\n";
    
    if (currentKills >= killsForNewSpell) {
        std::cout << "=== ПОЛУЧЕНО НОВОЕ ЗАКЛИНАНИЕ! ===\n";
        hand->addRandomSpell();
        currentKills = 0;
        std::cout << "Счетчик убийств сброшен. До следующего заклинания: " 
             << killsForNewSpell << " убийств\n";
    }
}

void Player::resetTurn() {
    hand->resetTurn();
}