#ifndef ENEMY_H
#define ENEMY_H

class Enemy {
private:
    int health;
    int damage;
    int x;
    int y;
    bool alive;
    
public:
    Enemy(int startX, int startY);
    Enemy(const Enemy& other);
    Enemy(Enemy&& other) noexcept;
    Enemy& operator=(const Enemy& other);
    Enemy& operator=(Enemy&& other) noexcept;
    
    int getX() const;
    int getY() const;
    bool isAlive() const;
    int getDamage() const;
    
    void setPosition(int newX, int newY);
    void takeDamage(int amount);
    void moveTowardsPlayer(int playerX, int playerY);
};

#endif // ENEMY_H