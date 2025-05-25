#pragma once

// Прототипы вспомогательных функций
void clear_input_buffer();
int safe_get_int(const wchar_t* prompt, int min_val, int max_val);
double safe_get_double(const wchar_t* prompt, double min_val, double max_val);

//По поводу ввода с консоли.

// Ввод широкой строки с консоли
wchar_t* get_wstring(int max_len) {
    if (max_len <= 0) return NULL;
    clear_input_buffer(); // Очистка буфера перед чтением
    // Выделение памяти для строки (+1 для нуль-терминатора)
    wchar_t* buffer = (wchar_t*)malloc((max_len + 1) * sizeof(wchar_t));
    if (!buffer) return NULL;
    if (!fgetws(buffer, max_len + 1, stdin)) {
        free(buffer); // Освобождаем память в случае ошибки
        return NULL;
    }
    // Удаляем символ новой строки, если он есть
    size_t len = wcslen(buffer);
    if (len > 0 && buffer[len - 1] == L'\n') {
        buffer[len - 1] = L'\0';
    }
    else {
        // Если строка слишком длинная, очищаем оставшиеся символы в буфере
        clear_input_buffer();
    }
    return buffer;
}

// Безопасное чтение строки с консоли
char* get_string(int max_len) {
    if (max_len <= 0) return NULL;
    clear_input_buffer(); // Очистка буфера перед чтением
    // Выделение памяти для строки (+1 для нуль-терминатора)
    char* buffer = (char*)malloc(max_len + 1);
    if (!buffer) return NULL;
    // Чтение строки с ограничением длины
    if (fgets(buffer, max_len + 1, stdin) == NULL) {
        free(buffer); // Освобождаем память при ошибке чтения
        return NULL;
    }
    // Удаление символа новой строки
    size_t len = strlen(buffer);
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
    }
    else {
        // Если символ новой строки не найден - очищаем буфер
        clear_input_buffer();
    }
    return buffer;
}

// Ввод прямого восхождения
directAscent input_direct_ascent() {
    directAscent da;
    da.hour = safe_get_int(L"Enter hours (0-23): " , 0, 23);
    da.minutes = safe_get_int(L"Enter minutes (0-59): ", 0, 59);
    da.seconds = safe_get_double(L"Enter seconds (0-59.999): ", 0.0, 59.99999999);
    fflush(stdin);
    return da;
}

ObjacteTipe* create_object_menu() {
    setlocale(LC_ALL, "");
    wprintf(L"\nВыберите тип объекта:\n");
    wprintf(L"1. Звезда\n2. Черная дыра\n3. Туманность\n");
    wprintf(L"4. Пульсар\n5. Галактика\n6. Звездное скопление\nВаш выбор: ");

    int choice = safe_get_int(L"", 1, 6);

    wchar_t* name = NULL;
    directAscent ascent;
    double declination, range, mass;
    INFO info = { NULL, 0 };

    wprintf(L"\nВведите общие параметры:\n");
    wprintf(L"Название объекта (макс 50 символов): ");
    name = get_wstring(50);

    wprintf(L"\nПрямое восхождение:\n");
    ascent = input_direct_ascent();

    declination = safe_get_double(L"Склонение (-90 до 90): ", -90.0, 90.0);
    range = safe_get_double(L"Расстояние (в световых годах): ", 0.0, DBL_MAX);
    mass = safe_get_double(L"Масса (в солнечных массах): ", 0.0, DBL_MAX);

    ObjacteTipe* OBJ = (ObjacteTipe*)malloc(sizeof(ObjacteTipe));

    switch (choice) {
    case 1: { // Звезда
        wprintf(L"\nВведите класс звезды (до 3 символов): ");
        wchar_t* star_class = get_wstring(3);
        double magnitude = safe_get_double(L"Звездная величина: ", -DBL_MAX, DBL_MAX);
        OBJ->Objecte = (SpaseObgectDeterminant*)createOfStar(name, range, magnitude, star_class, declination, ascent, mass, info);
        OBJ->type = OBJ_STAR;
        free(star_class);
        break;
    }
    case 2: { // Черная дыра
        wprintf(L"\nВведите класс черной дыры (до 50 символов): ");
        wchar_t* bh_class = get_wstring(50);
        OBJ->Objecte = (SpaseObgectDeterminant*)createOfBlackHole(name, range, bh_class, declination, ascent, mass, info);
        OBJ->type = OBJ_BLACKHOLE;
        free(bh_class);
        break;
    }
    case 3: { // Туманность
        wprintf(L"\nВведите класс туманности (до 100 символов): ");
        wchar_t* nebula_class = get_wstring(100);
        OBJ->Objecte = (SpaseObgectDeterminant*)createOfNebula(name, range, nebula_class, declination, ascent, mass, info);
        OBJ->type = OBJ_NEBULA;
        free(nebula_class);
        break;
    }
    case 4: { // Пульсар
        double frequency = safe_get_double(L"\nВведите частоту пульсара (Гц): ", 0.0, DBL_MAX);
        double magnitude = safe_get_double(L"Звездная величина: ", -DBL_MAX, DBL_MAX);
        OBJ->Objecte = (SpaseObgectDeterminant*)createOfPulsar(name, range, declination, ascent, mass, frequency, magnitude, info);
        OBJ->type = OBJ_PULSAR;
        break;
    }
    case 5: { // Галактика
        double count_stars = safe_get_double(L"\nВведите предполагаемое количество звезд: ", 0.0, DBL_MAX);
        OBJ->Objecte = (SpaseObgectDeterminant*)createOfGalaxy(name, range, declination, ascent, mass, count_stars, info);
        OBJ->type = OBJ_GALAXY;
        break;
    }
    case 6: { // Звездное скопление
        double count_stars = safe_get_double(L"\nВведите количество звезд: ", 0.0, INT_MAX);
        OBJ->Objecte = (SpaseObgectDeterminant*)createOfStarCluster(name, range, declination, ascent, mass, count_stars, info);
        OBJ->type = OBJ_STARCLASTER;
        break;
    }
    default:
        wprintf(L"Неверный выбор!\n");
        free(name);
        free(OBJ);
        return NULL;
    }
    free(name);
    return OBJ;
}

void DestroyEllementMenu(SpaseAtlas* ATL) {
    wprintf(L"Выберите:\n1) Уничтожить последний элемент\n2) Уничтожить произвольный элемент\nВаш выбор: ");
    clear_input_buffer();
    int choice = safe_get_int(L"", 1, 2);

    switch (choice) {
    case 1:
        pop_Back(ATL);
        break;
    case 2: {
        int index = safe_get_int(L"Введите номер удаляемого элемента", 0, ATL->size - 1);
        removeAt(ATL, index);
        break;
    }
    default:
        wprintf(L"Неверный выбор!\n");
        break;
    }
}









// Вспомогательные функции безопасного ввода
void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int safe_get_int(const wchar_t* prompt, int min_val, int max_val) {
    fflush(stdin);
    int value;
    while (1) {
        if (prompt) wprintf(L"%ls: ", prompt);
        if (wscanf_s(L"%d", &value, 4) != 1) {
            wprintf(L"Некорректный ввод! Попробуйте снова.\n");
            fflush(stdin);
            continue;
        }
        if (value >= min_val && value <= max_val) break;
        wprintf(L"Значение должно быть между %d и %d! Попробуйте снова.\n", min_val, max_val);
    }
    return value;
}

double safe_get_double(const wchar_t* prompt, double min_val, double max_val) {
    fflush(stdin);
    double value;
    while (1) {
        if (prompt) wprintf(L"%ls", prompt);
        if (wscanf_s(L"%lf", &value) != 1) {
            while (getchar() != '\n');
            wprintf(L"Некорректный ввод! Попробуйте снова.\n");
            continue;
        }
        while (getchar() != '\n'); // Очистка буфера

        // Автоматическая корректировка диапазона
        if (min_val > max_val) {
            double temp = min_val;
            min_val = max_val;
            max_val = temp;
        }

        if (value >= min_val && value <= max_val) break;
        wprintf(L"Допустимый диапазон: %.2f - %.2f\n", min_val, max_val);
    }
    return value;
}


#include "StarsWork.h"

// Меню для изменения полей объекта в SpaseAtlas
void edit_object_menu(SpaseAtlas* atlas) {
    if (!atlas || atlas->size == 0) {
        wprintf(L"Атлас пуст!\n");
        return;
    }

    // Выбор объекта для редактирования
    wprintf(L"\nВыберите номер объекта для изменения (0 - %d):\n", atlas->size - 1);
    for (int i = 0; i < atlas->copiseti; ++i) {
        wprintf(L"%d: %ls\n", i, atlas->unit[i].Objecte->name);
    }
    int idx = safe_get_int(L"Введите номер объекта", 0, atlas->size - 1);
    ObjacteTipe* obj = &atlas->unit[idx];

    // Основное меню выбора поля
    int exit_flag = 0;
    while (!exit_flag) {
        wprintf(L"\nВыберите поле для изменения:\n");
        wprintf(L"1. Название\n2. Прямое восхождение\n3. Склонение\n4. Расстояние\n5. Масса\n6. Информация\n");

        // Специфичные поля для типа объекта
        switch (obj->type) {
        case OBJ_STAR:
            wprintf(L"7. Класс звезды\n8. Звездная величина\n");
            break;
        case OBJ_BLACKHOLE:
            wprintf(L"7. Класс черной дыры\n");
            break;
        case OBJ_NEBULA:
            wprintf(L"7. Класс туманности\n");
            break;
        case OBJ_PULSAR:
            wprintf(L"7. Частота пульсара\n8. Звездная величина\n");
            break;
        case OBJ_GALAXY:
            wprintf(L"7. Количество звезд\n");
            break;
        case OBJ_STARCLASTER:
            wprintf(L"7. Количество звезд\n");
            break;
        default:
            break;
        }
        wprintf(L"0. Выход\n");

        int field = safe_get_int(L"Ваш выбор", 0, 8);

        switch (field) {
        case 0:
            exit_flag = 1;
            break;
        case 1: { // Название
            wprintf(L"Новое название (до 50 символов): ");
            wchar_t* new_name = get_wstring(50);
            // Replace the problematic line with the following code to fix the error:
            wcsncpy_s(obj->Objecte->name, 51, new_name, _TRUNCATE);
            obj->Objecte->name[50] = L'\0';
            free(new_name);
            break;
        }
        case 2: { // Прямое восхождение
            wprintf(L"Новое прямое восхождение:\n");
            obj->Objecte->Ascent = input_direct_ascent();
            break;
        }
        case 3: // Склонение
            obj->Objecte->declination = safe_get_double(L"Новое склонение (-90 до 90): ", -90.0, 90.0);
            break;
        case 4: // Расстояние
            obj->Objecte->range = safe_get_double(L"Новое расстояние: ", 0.0, DBL_MAX);
            break;
        case 5: // Масса
            obj->Objecte->mass = safe_get_double(L"Новая масса: ", 0.0, DBL_MAX);
            break;
        case 6: { // Информация
            wprintf(L"Введите новую информацию (до 200 символов): ");
            char* new_info = get_string(200);
            if (obj->Objecte->info.info) free(obj->Objecte->info.info);
            obj->Objecte->info.info = new_info;
            obj->Objecte->info.size = (int)strlen(new_info);
            break;
        }
              // Специфичные поля
        case 7:
            switch (obj->type) {
            case OBJ_STAR: {
                wprintf(L"Новый класс звезды (до 3 символов): ");
                wchar_t* new_class = get_wstring(3);
                ((Star*)obj->Objecte)->starClass = _wcsdup(new_class);
                free(new_class);
                break;
            }
            case OBJ_BLACKHOLE: {
                wprintf(L"Новый класс черной дыры (до 50 символов): ");
                wchar_t* new_class = get_wstring(50);
                ((BlackHole*)obj->Objecte)->blackHoleClass = _wcsdup(new_class);
                free(new_class);
                break;
            }
            case OBJ_NEBULA: {
                wprintf(L"Новый класс туманности (до 100 символов): ");
                wchar_t* new_class = get_wstring(100);
                ((Nebula*)obj->Objecte)->nebulaClass = _wcsdup(new_class);
                free(new_class);
                break;
            }
            case OBJ_PULSAR: {
                ((Pulsar*)obj->Objecte)->pulsarFrequensy = safe_get_double(L"Новая частота пульсара: ", 0.0, DBL_MAX);
                break;
            }
            case OBJ_GALAXY: {
                ((Galaxy*)obj->Objecte)->CountStar = safe_get_double(L"Новое количество звезд: ", 0.0, DBL_MAX);
                break;
            }
            case OBJ_STARCLASTER: {
                ((StarCluster*)obj->Objecte)->CountStar = (long unsigned)safe_get_double(L"Новое количество звезд: ", 0.0, INT_MAX);
                break;
            }
            default:
                wprintf(L"Нет такого поля для этого типа объекта.\n");
                break;
            }
            break;
        case 8:
            if (obj->type == OBJ_STAR) {
                ((Star*)obj->Objecte)->stellarMagnitude = safe_get_double(L"Новая звездная величина: ", -DBL_MAX, DBL_MAX);
            }
            else if (obj->type == OBJ_PULSAR) {
                ((Pulsar*)obj->Objecte)->stellarMagnitude = safe_get_double(L"Новая звездная величина: ", -DBL_MAX, DBL_MAX);
            }
            else {
                wprintf(L"Нет такого поля для этого типа объекта.\n");
            }
            break;
        default:
            wprintf(L"Неверный выбор!\n");
            break;
        }
    }
}

//Функция для вывода слова привет
void PrintHello() {
    printf("Hello");
}