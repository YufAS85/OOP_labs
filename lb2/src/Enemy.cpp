#include "Enemy.h"

Enemy::Enemy(int startX, int startY) 
    : health(30), damage(10), x(startX), y(startY), alive(true) {}

Enemy::Enemy(const Enemy& other)
    : health(other.health), damage(other.damage), 
      x(other.x), y(other.y), alive(other.alive) {}

Enemy::Enemy(Enemy&& other) noexcept
    : health(other.health), damage(other.damage),
      x(other.x), y(other.y), alive(other.alive) {
    other.alive = false;
    other.x = -1;
    other.y = -1;
}

Enemy& Enemy::operator=(const Enemy& other) {
    if (this != &other) {
        health = other.health;
        damage = other.damage;
        x = other.x;
        y = other.y;
        alive = other.alive;
    }
    return *this;
}

Enemy& Enemy::operator=(Enemy&& other) noexcept {
    if (this != &other) {
        health = other.health;
        damage = other.damage;
        x = other.x;
        y = other.y;
        alive = other.alive;
        other.alive = false;
        other.x = -1;
        other.y = -1;
    }
    return *this;
}

int Enemy::getX() const { return x; }
int Enemy::getY() const { return y; }
bool Enemy::isAlive() const { return alive; }
int Enemy::getDamage() const { return damage; }
int Enemy::getHealth() const { return health; }

void Enemy::setPosition(int newX, int newY) {
    x = newX;
    y = newY;
}

void Enemy::takeDamage(int amount) {
    health -= amount;
    if (health <= 0) {
        alive = false;
    }
}

void Enemy::moveTowardsPlayer(int playerX, int playerY) {
    if (!alive) return;
    
    if (playerX > x) x++;
    else if (playerX < x) x--;
    
    if (playerY > y) y++;
    else if (playerY < y) y--;
}