#include "Player.h"
#include <algorithm>

Player::Player(int startX, int startY) 
    : health(100), damage(10), score(0), x(startX), y(startY) {}

Player::Player(const Player& other)
    : health(other.health), damage(other.damage), 
      score(other.score), x(other.x), y(other.y) {}

Player::Player(Player&& other) noexcept
    : health(other.health), damage(other.damage),
      score(other.score), x(other.x), y(other.y) {
    other.health = 0;
    other.x = -1;
    other.y = -1;
}

Player& Player::operator=(const Player& other) {
    if (this != &other) {
        health = other.health;
        damage = other.damage;
        score = other.score;
        x = other.x;
        y = other.y;
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
        
        other.health = 0;
        other.x = -1;
        other.y = -1;
    }
    return *this;
}

int Player::getX() const { return x; }
int Player::getY() const { return y; }
int Player::getHealth() const { return health; }
int Player::getDamage() const { return damage; }
int Player::getScore() const { return score; }

void Player::setPosition(int newX, int newY) {
    x = newX;
    y = newY;
}

void Player::takeDamage(int amount) {
    health -= amount;
    if (health < 0) health = 0;
}

void Player::addScore(int points) {
    score += points;
}

bool Player::isAlive() const { return health > 0; }