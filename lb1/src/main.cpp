#include "Game.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <conio.h>
#include <windows.h>

int main() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    srand(static_cast<unsigned>(time(nullptr)));
    
    try {
        std::cout << "=== Добро пожаловать в игру ===\n";
        std::cout << "Введите размер поля (ширина высота) от 10 до 25: ";
        
        int width, height;
        std::cin >> width >> height;
        
        Game game(width, height);
        
        while (game.isRunning()) {
            system("cls");
            game.display();
            
            std::cout << "\nВаш ход: ";
            char key = _getch();
            std::cout << key << std::endl;
            
            game.handleInput(key);
            
            if (game.isRunning()) {
                game.enemyTurn();
            }
        }
        
    } catch (const std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
    }
    
    std::cout << "\nИгра завершена!\n";
    system("pause");
    return 0;
}