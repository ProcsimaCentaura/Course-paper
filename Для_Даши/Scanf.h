#pragma once

//По поводу ввода с консоли.

// Ввод широкой строки с консоли
wchar_t* get_wstring(int max_len) {
    wchar_t* buffer = (wchar_t*)malloc((max_len + 1) * sizeof(wchar_t));
    if (!buffer) return NULL;

    fgetws(buffer, max_len, stdin);
    size_t len = wcslen(buffer);
    if (len > 0 && buffer[len - 1] == L'\n')
        buffer[len - 1] = L'\0';

    return buffer;
}

char* get_string(int max_len) {
    char* buffer = (char*)malloc((max_len + 1) * sizeof(wchar_t));
    if (!buffer) return NULL;

    fgets(buffer, max_len, stdin);
    size_t len = strlen(buffer);
    if (len > 0 && buffer[len - 1] == L'\n')
        buffer[len - 1] = L'\0';

    return buffer;
}

// Ввод прямого восхождения
directAscent input_direct_ascent() {
    directAscent da;
    wprintf(L"Enter hours (0-23): ");
    scanf_s("%d", &da.hour);
    wprintf(L"Enter minutes (0-59): ");
    scanf_s("%d", &da.minutes);
    wprintf(L"Enter seconds (0-59.999): ");
    scanf_s("%lf", &da.seconds);
    fflush(stdin);
    return da;
}

// Основное меню создания объекта
ObjacteTipe* create_object_menu() {
    setlocale(LC_ALL, ""); // Для поддержки широких символов

    // Выбор типа объекта
    wprintf(L"\nSelect object type:\n");
    wprintf(L"1. Star\n2. Black Hole\n3. Nebula\n");
    wprintf(L"4. Pulsar\n5. Galaxy\n6. Star Cluster\n");
    wprintf(L"Choice: ");

    int choice;
    scanf_s("%d", &choice);
    fflush(stdin);

    // Общие поля для всех объектов
    wchar_t* name = NULL;
    directAscent ascent;
    double declination, range, mass;
    INFO info = { NULL, 0 };

    wprintf(L"\nEnter common parameters:\n");

    // Ввод имени
    wprintf(L"Object name (max 50 chars): ");
    name = get_wstring(50);

    // Прямое восхождение
    wprintf(L"\nDirect Ascent:\n");
    ascent = input_direct_ascent();

    // Склонение
    wprintf(L"Declination (-90 to 90): ");
    scanf_s("%lf", &declination);

    // Расстояние
    wprintf(L"Range (in light years): ");
    scanf_s("%lf", &range);

    // Масса
    wprintf(L"Mass (in solar masses): ");
    scanf_s("%lf", &mass);
    fflush(stdin);

    // Специфичные поля
    switch (choice) {
    case 1: { // Star
        wchar_t* star_class;
        double magnitude;

        wprintf(L"\nEnter star class (up to 3 chars): ");
        star_class = get_wstring(3);

        wprintf(L"Stellar magnitude: ");
        scanf_s("%lf", &magnitude);
        fflush(stdin);

        ObjacteTipe* STAR;
        STAR = (ObjacteTipe*)malloc(sizeof(ObjacteTipe));
        STAR->Objecte = (SpaseObgectDeterminant*)createOfStar(name, range, magnitude, star_class,
            declination, ascent, mass, info);;
        STAR->type = OBJ_STAR;
        free(star_class);
        return STAR;
    }

    case 2: { // Black Hole
        wchar_t* bh_class;

        wprintf(L"\nEnter black hole class (up to 50 chars): ");
        bh_class = get_wstring(50);
        ObjacteTipe* BH;
        BH = (ObjacteTipe*)malloc(sizeof(ObjacteTipe));
        BH->Objecte = (SpaseObgectDeterminant*)createOfBlackHole(name, range, bh_class,
            declination, ascent, mass, info);;
        BH->type = OBJ_BLACKHOLE;
        free(bh_class);
        return BH;
    }

    case 3: { // Nebula
        wchar_t* nebula_class;

        wprintf(L"\nEnter nebula class (up to 100 chars): ");
        nebula_class = get_wstring(100);
        
        ObjacteTipe* NEB;
        NEB = (ObjacteTipe*)malloc(sizeof(ObjacteTipe));
        NEB->Objecte = (SpaseObgectDeterminant*)createOfNebula(name, range, nebula_class,
            declination, ascent, mass, info);;
        NEB->type = OBJ_NEBULA;
        free(nebula_class);
        return NEB;
    }

    case 4: { // Pulsar
        double frequency, magnitude;

        wprintf(L"\nEnter pulsar frequency (Hz): ");
        scanf_s("%lf", &frequency);

        wprintf(L"Stellar magnitude: ");
        scanf_s("%lf", &magnitude);
        fflush(stdin);

        ObjacteTipe* PUL;
        PUL = (ObjacteTipe*)malloc(sizeof(ObjacteTipe));
        PUL->Objecte = (SpaseObgectDeterminant*)createOfPulsar(name, range, declination, ascent, mass,
            frequency, magnitude, info);
        PUL->type = OBJ_NEBULA;

        return PUL;
    }

    case 5: { // Galaxy
        double count_stars;

        wprintf(L"\nEnter estimated star count: ");
        scanf_s("%lf", &count_stars);
        fflush(stdin);
        ObjacteTipe* GAL;
        GAL = (ObjacteTipe*)malloc(sizeof(ObjacteTipe));
        GAL->Objecte = (SpaseObgectDeterminant*)createOfGalaxy(name, range, declination, ascent, mass,
            count_stars, info);
        GAL->type = OBJ_GALAXY;
        return GAL;
    }

    case 6: { // Star Cluster
        unsigned long count_stars;

        wprintf(L"\nEnter star count: ");
        scanf_s("%lu", &count_stars);
        fflush(stdin);

        ObjacteTipe* CLU;
        CLU = (ObjacteTipe*)malloc(sizeof(ObjacteTipe));
        CLU->Objecte = (SpaseObgectDeterminant*)createOfStarCluster(name, range, declination, ascent, mass,
            count_stars, info);
        CLU->type = OBJ_STARCLASTER;
        return CLU;
    }

    default:
        wprintf(L"Invalid choice!\n");
        free(name);
        return NULL;
    }
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


// Прототипы вспомогательных функций
void clear_input_buffer();
int safe_get_int(const wchar_t* prompt, int min_val, int max_val);
double safe_get_double(const wchar_t* prompt, double min_val, double max_val);


// Вспомогательные функции безопасного ввода
void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
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