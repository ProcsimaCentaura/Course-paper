#pragma once
inline static char get_object_symbol(TypeOfObjecte type) {
    switch (type) {
    case OBJ_STAR:       return '*';
    case OBJ_BLACKHOLE:  return '0';
    case OBJ_NEBULA:    return 'N';
    case OBJ_PULSAR:     return 'P';
    case OBJ_GALAXY:    return 'G';
    case OBJ_STARCLASTER: return 'S';
    default:             return '?';
    }
}

// Конвертация прямого восхождения в градусы
//Функция полезная, потребовалась в SortByAscent по этоме не static
inline double ascent_to_degrees(directAscent a) {
    return (a.hour + a.minutes / 60.0 + a.seconds / 3600.0) * 15.0;
}

// Получение размеров терминала
inline static void get_terminal_size(int* cols, int* rows) {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    *cols = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    *rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
}

inline static void set_cursor_position(int x, int y) {
    COORD coord = { x, y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

// Основная функция рендеринга
void render_atlas(struct SpaseAtlas* atlas) {
    int width, height;
    get_terminal_size(&width, &height);

    printf("\x1b[2J"); // Очистка экрана

    for (int i = 0; i < atlas->copiseti; i++) {
        struct ObjacteTipe* obj = &atlas->unit[i];
        struct SpaseObgectDeterminant* base = obj->Objecte;

        // Рассчет координат
        double ra_deg = ascent_to_degrees(base->Ascent);
        double dec_deg = base->declination;

        int x = (ra_deg / 360.0) * (width - 1);
        int y = height - ((dec_deg + 90.0) / 180.0 * height);

        // Установка цвета и позиции
        printf("\x1b[%d;%dH", y, x);
        printf("\x1b[33m%c", get_object_symbol(obj->type)); // Желтый цвет
    }

    printf("\x1b[0m"); // Сброс цвета
    printf("\x1b[%d;0H", height); // Курсор вниз
    fflush(stdout);
}

