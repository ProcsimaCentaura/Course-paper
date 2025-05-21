#include "Header.h"

int main() {
    // Для Windows: настройка кодировки
    setlocale(LC_ALL, "ru_RU.UTF-8");
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    SpaseAtlas* atl = createSpaseAtlas(10);
    add_test_objects(atl);
    if (!atl) {
        wprintf(L"Ошибка создания атласа!\n");
        return 1;
    }

    if (!save_spase_atlas(atl, "universe.dat")) {
        printf("Save failed!\n");
        deleteSpaseAtlas(atl);
    }

    SpaseAtlas* loaded = load_spase_atlas("universe.dat");
    if (loaded) {
        print_table(loaded);

    }

    //render_atlas(loaded);

    sortOfAtlass(loaded, SORT_BY_MASS);

    print_table(loaded);

    sortOfAtlass(loaded, SORT_BY_NAME);

    print_table(loaded);

    sortOfAtlass(loaded, SORT_BY_RANGE);

    print_table(loaded);

    sortOfAtlass(loaded, SORT_BY_ASCENT);

    print_table(loaded);

    deleteSpaseAtlas(loaded);
    loaded = nullptr;

    char s;
    scanf_s("%c", &s);
    return 0;
}