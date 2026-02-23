#include "Menu.h"
#include "Constants.h"
#include <cstdlib>
#include <ctime>
#include <windows.h>

int main() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    srand(time(NULL));
    
    GameApplication app;
    app.run();
    
    return 0;
}