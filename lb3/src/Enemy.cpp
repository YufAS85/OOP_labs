#include "Enemy.h"

extern const int DEFAULT_ENEMY_HEALTH;
extern const int DEFAULT_ENEMY_DAMAGE;

Enemy::Enemy() : health(0), damage(0), x(0), y(0), alive(false) {}

Enemy::Enemy(int startX, int startY) 
    : health(DEFAULT_ENEMY_HEALTH), damage(DEFAULT_ENEMY_DAMAGE), x(startX), y(startY), alive(true) {}

Enemy::Enemy(int startX, int startY, int startHealth, int startDamage) 
    : health(startHealth), damage(startDamage), x(startX), y(startY), alive(true) {}

Enemy::Enemy(const Enemy& other)
    : health(other.health), damage(other.damage), 
      x(other.x), y(other.y), alive(other.alive) {}

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

Enemy::Enemy(Enemy&& other) noexcept
    : health(other.health), damage(other.damage),
      x(other.x), y(other.y), alive(other.alive) {
    other.alive = false;
    other.x = -1;
    other.y = -1;
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