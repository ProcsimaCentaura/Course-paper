#include "Header.h"

int main() {
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    // Для Windows: настройка кодировки
    setlocale(LC_ALL, "ru_RU.UTF-8");
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    SpaseAtlas* ATL = nullptr;

    Menu(ATL);

    _CrtDumpMemoryLeaks();
    return 0;
}