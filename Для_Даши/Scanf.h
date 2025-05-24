#pragma once

// Прототипы вспомогательных функций
void clear_input_buffer();
int safe_get_int(const wchar_t* prompt, int min_val, int max_val);
double safe_get_double(const wchar_t* prompt, double min_val, double max_val);

//По поводу ввода с консоли.

// Ввод широкой строки с консоли
wchar_t* get_wstring(int max_len) {
    wchar_t* buffer = (wchar_t*)malloc((max_len + 1) * sizeof(wchar_t));
    if (!buffer) return NULL;
    fflush(stdin);
    fgetws(buffer, max_len, stdin);
    size_t len = wcslen(buffer);
    if (len > 0 && buffer[len - 1] == L'\n')
        buffer[len - 1] = L'\0';

    return buffer;
}

char* get_string(int max_len) {
    char* buffer = (char*)malloc((max_len + 1) * sizeof(wchar_t));
    if (!buffer) return NULL;
    fflush(stdin);
    fgets(buffer, max_len, stdin);
    size_t len = strlen(buffer);
    if (len > 0 && buffer[len - 1] == L'\n')
        buffer[len - 1] = L'\0';

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

// Основное меню создания объекта
ObjacteTipe* create_object_menu() {
    setlocale(LC_ALL, ""); // Для поддержки широких символов

    // Выбор типа объекта
    wprintf(L"\nВыберите тип объекта:\n");
    wprintf(L"1. Звезда\n2. Черная дыра\n3. Туманность\n");
    wprintf(L"4. Пульсар\n5. Галактика\n6. Звездное скопление\n");
    wprintf(L"Ваш выбор: ");

    int choice;
    scanf_s("%d", &choice);
    fflush(stdin);

    // Общие поля для всех объектов
    wchar_t* name = NULL;
    directAscent ascent;
    double declination, range, mass;
    INFO info = { NULL, 0 };
    fflush(stdin);
    wprintf(L"\nВведите общие параметры:\n");

    // Ввод имени
    fflush(stdin);
    wprintf(L"Название объекта (макс 50 символов): ");
    name = get_wstring(50);

    // Прямое восхождение
    fflush(stdin);
    wprintf(L"\nПрямое восхождение:\n");
    ascent = input_direct_ascent();

    // Склонение
    fflush(stdin);
    wprintf(L"Склонение (-90 до 90): ");
    scanf_s("%lf", &declination);

    // Расстояние
    fflush(stdin);
    wprintf(L"Расстояние (в световых годах): ");
    scanf_s("%lf", &range);

    // Масса
    fflush(stdin);
    wprintf(L"Масса (в солнечных массах): ");
    scanf_s("%lf", &mass);
    fflush(stdin);

    ObjacteTipe* OBJ;
    OBJ = (ObjacteTipe*)malloc(sizeof(ObjacteTipe));

    // Специфичные поля
    switch (choice) {
    case 1: { // Star
        wchar_t* star_class;
        double magnitude;
        fflush(stdin);
        wprintf(L"\nВведите класс звезды (до 3 символов): ");
        star_class = get_wstring(3);
        fflush(stdin);
        wprintf(L"Звездная величина: ");
        scanf_s("%lf", &magnitude);
        fflush(stdin);

       
        OBJ->Objecte = (SpaseObgectDeterminant*)createOfStar(name, range, magnitude, star_class,
            declination, ascent, mass, info);;
        OBJ->type = OBJ_STAR;
        free(star_class);

    }

    case 2: { // Black Hole
        wchar_t* bh_class;
        fflush(stdin);
        wprintf(L"\nВведите класс черной дыры (до 50 символов): ");
        bh_class = get_wstring(50);
        ObjacteTipe* BH;
        BH = (ObjacteTipe*)malloc(sizeof(ObjacteTipe));
        OBJ->Objecte = (SpaseObgectDeterminant*)createOfBlackHole(name, range, bh_class,
            declination, ascent, mass, info);;
        OBJ->type = OBJ_BLACKHOLE;
        free(bh_class);

    }

    case 3: { // Nebula
        wchar_t* nebula_class;
        fflush(stdin);
        wprintf(L"\nВведите класс туманности (до 100 символов): ");
        nebula_class = get_wstring(100);
        
        ObjacteTipe* NEB;
        NEB = (ObjacteTipe*)malloc(sizeof(ObjacteTipe));
        NEB->Objecte = (SpaseObgectDeterminant*)createOfNebula(name, range, nebula_class,
            declination, ascent, mass, info);;
        NEB->type = OBJ_NEBULA;
        free(nebula_class);

    }

    case 4: { // Pulsar
        double frequency, magnitude;
        fflush(stdin);
        frequency = safe_get_double(L"\nВведите частоту пульсара (Гц): ", 0.0, DBL_MAX);
        fflush(stdin);
        magnitude = safe_get_double(L"Звездная величина: ", 0.0, DBL_MAX);
        fflush(stdin);

       
        OBJ->Objecte = (SpaseObgectDeterminant*)createOfPulsar(name, range, declination, ascent, mass,
            frequency, magnitude, info);
        OBJ->type = OBJ_NEBULA;


    }

    case 5: { // Galaxy
        double count_stars;
        fflush(stdin);
        count_stars = safe_get_double(L"\nВведите предполагаемое количество звезд: ", 0.0, DBL_MAX);

        OBJ->Objecte = (SpaseObgectDeterminant*)createOfGalaxy(name, range, declination, ascent, mass,
            count_stars, info);
        OBJ->type = OBJ_GALAXY;

    }

    case 6: { // Star Cluster
        unsigned long count_stars;
        fflush(stdin);
        count_stars = safe_get_double(L"\nВведите количество звезд: ", 0.0, INT_MAX);
        OBJ->Objecte = (SpaseObgectDeterminant*)createOfStarCluster(name, range, declination, ascent, mass,
            count_stars, info);
        OBJ->type = OBJ_STARCLASTER;

    }

    default:
        wprintf(L"Неверный выбор!\n");
        free(name);
        return NULL;
    }
    free(name);
}

void DestroyEllementMenu(SpaseAtlas* ATL) {
    wprintf(L"Выберите:\n1)уничтожить последний эллемент, \n2)Уничтожить произвольный элемент");
    switch (getchar())
    {
    case 1: {
        pop_Back(ATL);
    }
          break;
    case 2: {
        wprintf(L"Введите номер удаляемого эллеметнта.");
        int index;
        scanf_s("%d", &index);
        removeAt(ATL, index);
    }
          break;
    default:
        break;
    }
}




enum CHOISE
{
    OPEN_FILE = 1,
    ADD_ELEMENT,
    REMOVE_ELEMENT,
    SORT_ATLAS,
    SEARCH_ATLAS,
    RENDER_SKY,
    DISPLAY_TABLE,
    SAVE_THE_ATLAS,
    EXIT
};





// Вспомогательные функции безопасного ввода
void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
    fflush(stdin);
}

int safe_get_int(const wchar_t* prompt, int min_val, int max_val) {
    int value;
    while (1) {
        if (prompt) wprintf(L"%ls: ", prompt);
        if (wscanf_s(L"%d", &value, 4) != 1) {
            wprintf(L"Некорректный ввод! Попробуйте снова.\n");
            clear_input_buffer();
            continue;
        }
        if (value >= min_val && value <= max_val) break;
        wprintf(L"Значение должно быть между %d и %d! Попробуйте снова.\n", min_val, max_val);
    }
    return value;
}

double safe_get_double(const wchar_t* prompt, double min_val, double max_val) {
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