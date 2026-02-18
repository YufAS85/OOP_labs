#include "Game.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <conio.h>
#include <windows.h>

int main() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    srand(time(NULL));
    
    try {
        std::cout << "=== Добро пожаловать в игру! ===\n";
        std::cout << "Введите размер поля (ширина высота) от 10 до 25: ";
        
        int width, height;
        std::cin >> width >> height;
        
        Game game(width, height);
        
        while (game.isRunning()) {
            game.display();
            
            char key = _getch();
            game.handleInput(key);
            
            if (game.isRunning() && game.isTurnUsed()) {
                game.enemyTurn();
            }
        }
        
    } catch (const std::exception& e) {
        std::cout << "Ошибка: " << e.what() << std::endl;
        std::cout << "Нажмите любую клавишу...\n";
        _getch();
    }
    
    return 0;
}