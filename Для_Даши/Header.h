#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>//��������� ��� unicode(��� ������� �� �� ��������)
#include <wchar.h>
#include <float.h>//���� �������� ������������ � ������������� �������� float
#include <ctype.h>//��� ������������ � ������ �� ������
#include <windows.h>//��������� ��� �������(������ �������)
#define _USE_MATH_DEFINES//�������� � ��� ��� ����� ��������, �� ���� �� ������
#include <math.h>

#pragma pack(push, 1) // ����� ��� �������� �������������
//������ ����������� �� ������� ������ ������������ ��� ��������, 
// ��� �� ������������� "�������� �������"
#define _CRT_SECURE_NO_WARNINGS
//��� ��� ���� ����� ��� ���������� �������� ���� ��������� �� ������ 
//������������� ������ strcpy, sprintf, scanf
//����� � �� ���� define �� ����� �������, ���-��� �� ������� ����� � ���� ���
//��� ������ � ������� ���������.

//��� ������.
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