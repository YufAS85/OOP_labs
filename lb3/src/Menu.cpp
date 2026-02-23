#include "Menu.h"
#include "SaveManager.h"
#include "Game.h"
#include <iostream>
#include <conio.h>
#include <windows.h>

extern const int MIN_FIELD_SIZE;
extern const int MAX_FIELD_SIZE;

int StartMenu::run() {
    while (true) {
        display();
        int choice = getChoice();
        
        if (choice == 1 || choice == 2 || choice == 3) {
            return choice;
        }
    }
}

void StartMenu::display() {
    system("cls");
    std::cout << "=== Добро пожаловать в игру! ===\n";
    std::cout << "1. Новая игра\n";
    std::cout << "2. Загрузить игру\n";
    std::cout << "3. Выход\n";
    std::cout << "Выберите опцию: ";
}

int StartMenu::getChoice() {
    char choice = _getch();
    while (choice < '1' || choice > '3') {
        std::cout << "\nНеверный выбор! Пожалуйста, выберите 1, 2 или 3: ";
        choice = _getch();
    }
    return choice - '0';
}

int SaveLoadMenu::run() {
    SaveManager saver;
    auto saves = saver.listSaves();
    
    if (saves.empty()) {
        std::cout << "\nНет доступных сохранений!\n";
        std::cout << "Нажмите любую клавишу...\n";
        _getch();
        return -1;
    }
    
    while (true) {
        display(saves);
        int choice = getChoice(saves.size());
        
        if (choice == 0) return -1;
        if (choice > 0) return choice - 1;
    }
}

void SaveLoadMenu::display(const std::vector<std::string>& saves) {
    system("cls");
    std::cout << "=== ЗАГРУЗКА ИГРЫ ===\n\n";
    
    for (size_t i = 0; i < saves.size(); i++) {
        std::cout << i + 1 << ". " << saves[i] << "\n";
    }
    std::cout << "0. Назад\n";
    std::cout << "\nВыберите сохранение: ";
}

int SaveLoadMenu::getChoice(int maxSaves) {
    char c = _getch();
    if (c == '0') return 0;
    
    int choice = c - '0';
    if (choice >= 1 && choice <= maxSaves) {
        return choice;
    }
    return -2;
}

void GameApplication::run() {
    while (true) {
        int choice = menu.run();
        
        if (choice == 1) {
            launcher.run();
        }
        else if (choice == 2) {
            SaveLoadMenu loadMenu;
            int saveIndex = loadMenu.run();
            
            if (saveIndex >= 0) {
                SaveManager saver;
                auto saves = saver.listSaves();
                if (saveIndex < (int)saves.size()) {
                    launcher.loadGame(saves[saveIndex]);
                }
            }
        }
        else if (choice == 3) {
            break;
        }
    }
}