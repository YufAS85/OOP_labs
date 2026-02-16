#ifndef PLAYER_H
#define PLAYER_H

class Player {
private:
    int health;
    int damage;
    int score;
    int x;
    int y;
    
public:
    Player(int startX, int startY);
    Player(const Player& other);
    Player(Player&& other) noexcept;
    Player& operator=(const Player& other);
    Player& operator=(Player&& other) noexcept;
    
    int getX() const;
    int getY() const;
    int getHealth() const;
    int getDamage() const;
    int getScore() const;
    
    void setPosition(int newX, int newY);
    void takeDamage(int amount);
    void addScore(int points);
    bool isAlive() const;
};

#endif // PLAYER_H