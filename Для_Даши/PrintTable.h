﻿#pragma once
// Вспомогательные функции для форматирования данных
inline static void format_directAscent(struct directAscent a, wchar_t* buffer) {
    _snwprintf_s(buffer, 20, _TRUNCATE, L"%02dh %02dm %04.1fs", a.hour, a.minutes, a.seconds);
}

inline static void format_declination(double dec, wchar_t* buffer) {
    _snwprintf_s(buffer, 20, _TRUNCATE, L"%.4f°", dec);
}

// Основная функция вывода таблицы
void print_table(struct SpaseAtlas* atlas) {
    if (atlas==NULL)
    {
        wprintf(L"Ошибка, атлас не существует.");
        return;
    }
    printf("\x1b[2J");//Очистка консоли
    // Настройка локаализации для широких символов
    //Надо ввести функцию, разной посветки линии, в зависимости от типа объекта, например
    // Желтый для звезд, фиолетовый для черных дыр. Естественно это правило таблицы
    //А не рендеринга
    // Шапка таблицы
    wprintf(L"\n┌────────────────────┬──────────────┬────────────┬────────────┬────────────┬────────────────┬──────────────┬────────┐\n");
    wprintf(L"\n│%-19ls │ %-13ls │ %-11ls │ %-11ls │ %-11ls │ %-15ls │ %-13ls │ %-7ls │\n",
        L"Название", L"Прям. восх.", L"Склонение", L"Расстояние", L"Масса",
        L"Класс/Тип", L"Зв. величина", L"Частота/Кол-во");
    wprintf(L"\n├────────────────────┼──────────────┼────────────┼────────────┼────────────┼────────────────┼──────────────┼────────┤\n");

    wchar_t buffer[20];
    for (int i = 0; i < atlas->copiseti; i++) {
        struct ObjacteTipe* obj = &atlas->unit[i];
        struct SpaseObgectDeterminant* base = obj->Objecte;

        // Общие данные для всех объектов
        format_directAscent(base->Ascent, buffer);
        wchar_t asc_buf[20];
        _snwprintf_s(asc_buf, sizeof(asc_buf), L"%ls", buffer);

        format_declination(base->declination, buffer);
        wchar_t dec_buf[20];
        _snwprintf_s(dec_buf, sizeof(dec_buf), L"%ls", buffer);

        // Поля, специфичные для типа
        const wchar_t* class_info = L"";
        wchar_t value1[20] = L"";
        wchar_t value2[20] = L"";

        switch (obj->type) {
        case OBJ_STAR: {
            printf(ANSI_COLOR_YELLOW);
            Star* star = (Star*)base;
            class_info = star->starClass;
            _snwprintf_s(value1, sizeof(value1), L"%.2f", star->stellarMagnitude);
            break;
        }
        case OBJ_BLACKHOLE: {
            printf(ANSI_COLOR_MAGENTA);
            BlackHole* bh = (BlackHole*)base;
            class_info = bh->blackHoleClass;
            break;
        }
        case OBJ_NEBULA: {
            printf(ANSI_COLOR_BLUE);
            Nebula* neb = (Nebula*)base;
            class_info = neb->nebulaClass;
            break;
        }
        case OBJ_PULSAR: {
            printf(ANSI_COLOR_CYAN);
            Pulsar* pulsar = (Pulsar*)base;
            _snwprintf_s(value1, sizeof(value1), L"%.2f", pulsar->stellarMagnitude);
            _snwprintf_s(value2, sizeof(value2), L"%.1f Hz", pulsar->pulsarFrequensy);
            break;
        }
        case OBJ_GALAXY: {
            printf(ANSI_COLOR_GREEN);
            Galaxy* gal = (Galaxy*)base;
            _snwprintf_s(value2, sizeof(value2), L"%.1e", gal->CountStar);
            break;
        }
        case OBJ_STARCLASTER: {
            printf(ANSI_COLOR_WHITE);
            StarCluster* cl = (StarCluster*)base;
            _snwprintf_s(value2, sizeof(value2), L"%lu", cl->CountStar);
            break;
        }
        default: break;
        }

        // Вывод строки
        wprintf(L"\n│%-19ls│ %-13s │ %-11s │ %-11.2f │ %-11.2e │ %-15s │ %-15s │ %-7s │\n",
            base->name,
            asc_buf,
            dec_buf,
            base->range,
            base->mass,
            class_info,
            value1,
            value2);
        printf(ANSI_RESET_ALL);//Убираем все цвета.
    }
    wprintf(L"\n└────────────────────┴──────────────┴────────────┴────────────┴────────────┴────────────────┴──────────────┴────────┘\n");
}