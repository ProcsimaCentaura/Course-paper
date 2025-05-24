#include "Header.h"

int main() {
    // Для Windows: настройка кодировки
    setlocale(LC_ALL, "ru_RU.UTF-8");
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    SpaseAtlas* ATL = nullptr;

    Menu(ATL);

    
    return 0;
}