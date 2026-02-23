#ifndef MENU_H
#define MENU_H

#include <string>
#include <vector>

class StartMenu {
public:
    int run();

private:
    void display();
    int getChoice();
};

class SaveLoadMenu {
public:
    int run();

private:
    void display(const std::vector<std::string>& saves);
    int getChoice(int maxSaves);
};

class GameLauncher {
public:
    void run();
    void loadGame(const std::string& filename);
};

class GameApplication {
private:
    StartMenu menu;
    GameLauncher launcher;
    
public:
    void run();
};

#endif