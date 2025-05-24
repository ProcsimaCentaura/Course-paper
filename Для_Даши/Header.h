#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>//Требуется для unicode(мне кажется он не сработал)
#include <wchar.h>
#include <float.h>//Ради констант минимального и максимального значения float
#include <ctype.h>//Для безопасности и защиты от дурака
#include <windows.h>//Требуется для рендера(размер консоли)
#define _USE_MATH_DEFINES//Возможно и без них можно обойтись, но пока не убираю
#include <math.h>

#pragma pack(push, 1) // Важно для бинарной совместимости
//Разные компиляторы по разному делают выравнивание для структур, 
// так мы устанавливаем "Стандарт проекта"
#define _CRT_SECURE_NO_WARNINGS
//Это для того чтобы мой компилятор перестал меня тревожить по поводу 
//использования всяких strcpy, sprintf, scanf
//Узнал я об этом define не очень вовремя, так-что по большей части у меня уже
//Все потоко и буферно безопасно.

//Для цветов.
#define ANSI_RESET_ALL          "\x1b[0m"

#define ANSI_COLOR_BLACK        "\x1b[30m"
#define ANSI_COLOR_RED          "\x1b[31m"
#define ANSI_COLOR_GREEN        "\x1b[32m"
#define ANSI_COLOR_YELLOW       "\x1b[33m"
#define ANSI_COLOR_BLUE         "\x1b[34m"
#define ANSI_COLOR_MAGENTA      "\x1b[35m"
#define ANSI_COLOR_CYAN         "\x1b[36m"
#define ANSI_COLOR_WHITE        "\x1b[37m"

#define ANSI_BACKGROUND_BLACK   "\x1b[40m"
#define ANSI_BACKGROUND_RED     "\x1b[41m"
#define ANSI_BACKGROUND_GREEN   "\x1b[42m"
#define ANSI_BACKGROUND_YELLOW  "\x1b[43m"
#define ANSI_BACKGROUND_BLUE    "\x1b[44m"
#define ANSI_BACKGROUND_MAGENTA "\x1b[45m"
#define ANSI_BACKGROUND_CYAN    "\x1b[46m"
#define ANSI_BACKGROUND_WHITE   "\x1b[47m"

#define ANSI_STYLE_BOLD         "\x1b[1m"
#define ANSI_STYLE_ITALIC       "\x1b[3m"
#define ANSI_STYLE_UNDERLINE    "\x1b[4m"

#include "StarsWork.h"
#include "SpaseAtlas.h"
#include "Rendering.h"
#include "PrintTable.h"
#include "FileWork.h"
#include "SerchAndSort.h"
#include "Test.h"
#include "Scanf.h"
#include "MenuWork.h"