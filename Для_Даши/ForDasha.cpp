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

    render_atlas(loaded);

    sortOfAtlass(loaded, SORT_PULSAR_BY_PULSAR_FREQUENSY);

    print_table(loaded);

    SpaseAtlas* ATL = SerchInDiapazone(loaded, SERCH_BY_MASS, 100, 1000);

    print_table(ATL);

    //deleteSpaseAtlas(ATL);

    deleteSpaseAtlas(loaded);//Повторное удаление вызывает ошибку. ОСТОРОЖНО!!!
    loaded = nullptr;

    char s;
    scanf_s("%c", &s);
    return 0;
}