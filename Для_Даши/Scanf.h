#pragma once

// ��������� ��������������� �������
void clear_input_buffer();
int safe_get_int(const wchar_t* prompt, int min_val, int max_val);
double safe_get_double(const wchar_t* prompt, double min_val, double max_val);

//�� ������ ����� � �������.

// ���� ������� ������ � �������
wchar_t* get_wstring(int max_len) {
    if (max_len <= 0) return NULL;
    clear_input_buffer(); // ������� ������ ����� �������
    // ��������� ������ ��� ������ (+1 ��� ����-�����������)
    wchar_t* buffer = (wchar_t*)malloc((max_len + 1) * sizeof(wchar_t));
    if (!buffer) return NULL;
    if (!fgetws(buffer, max_len + 1, stdin)) {
        free(buffer); // ����������� ������ � ������ ������
        return NULL;
    }
    // ������� ������ ����� ������, ���� �� ����
    size_t len = wcslen(buffer);
    if (len > 0 && buffer[len - 1] == L'\n') {
        buffer[len - 1] = L'\0';
    }
    else {
        // ���� ������ ������� �������, ������� ���������� ������� � ������
        clear_input_buffer();
    }
    return buffer;
}

// ���������� ������ ������ � �������
char* get_string(int max_len) {
    if (max_len <= 0) return NULL;
    clear_input_buffer(); // ������� ������ ����� �������
    // ��������� ������ ��� ������ (+1 ��� ����-�����������)
    char* buffer = (char*)malloc(max_len + 1);
    if (!buffer) return NULL;
    // ������ ������ � ������������ �����
    if (fgets(buffer, max_len + 1, stdin) == NULL) {
        free(buffer); // ����������� ������ ��� ������ ������
        return NULL;
    }
    // �������� ������� ����� ������
    size_t len = strlen(buffer);
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
    }
    else {
        // ���� ������ ����� ������ �� ������ - ������� �����
        clear_input_buffer();
    }
    return buffer;
}

// ���� ������� �����������
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
    wprintf(L"\n�������� ��� �������:\n");
    wprintf(L"1. ������\n2. ������ ����\n3. ����������\n");
    wprintf(L"4. �������\n5. ���������\n6. �������� ���������\n��� �����: ");

    int choice = safe_get_int(L"", 1, 6);

    wchar_t* name = NULL;
    directAscent ascent;
    double declination, range, mass;
    INFO info = { NULL, 0 };

    wprintf(L"\n������� ����� ���������:\n");
    wprintf(L"�������� ������� (���� 50 ��������): ");
    name = get_wstring(50);

    wprintf(L"\n������ �����������:\n");
    ascent = input_direct_ascent();

    declination = safe_get_double(L"��������� (-90 �� 90): ", -90.0, 90.0);
    range = safe_get_double(L"���������� (� �������� �����): ", 0.0, DBL_MAX);
    mass = safe_get_double(L"����� (� ��������� ������): ", 0.0, DBL_MAX);

    ObjacteTipe* OBJ = (ObjacteTipe*)malloc(sizeof(ObjacteTipe));

    switch (choice) {
    case 1: { // ������
        wprintf(L"\n������� ����� ������ (�� 3 ��������): ");
        wchar_t* star_class = get_wstring(3);
        double magnitude = safe_get_double(L"�������� ��������: ", -DBL_MAX, DBL_MAX);
        OBJ->Objecte = (SpaseObgectDeterminant*)createOfStar(name, range, magnitude, star_class, declination, ascent, mass, info);
        OBJ->type = OBJ_STAR;
        free(star_class);
        break;
    }
    case 2: { // ������ ����
        wprintf(L"\n������� ����� ������ ���� (�� 50 ��������): ");
        wchar_t* bh_class = get_wstring(50);
        OBJ->Objecte = (SpaseObgectDeterminant*)createOfBlackHole(name, range, bh_class, declination, ascent, mass, info);
        OBJ->type = OBJ_BLACKHOLE;
        free(bh_class);
        break;
    }
    case 3: { // ����������
        wprintf(L"\n������� ����� ���������� (�� 100 ��������): ");
        wchar_t* nebula_class = get_wstring(100);
        OBJ->Objecte = (SpaseObgectDeterminant*)createOfNebula(name, range, nebula_class, declination, ascent, mass, info);
        OBJ->type = OBJ_NEBULA;
        free(nebula_class);
        break;
    }
    case 4: { // �������
        double frequency = safe_get_double(L"\n������� ������� �������� (��): ", 0.0, DBL_MAX);
        double magnitude = safe_get_double(L"�������� ��������: ", -DBL_MAX, DBL_MAX);
        OBJ->Objecte = (SpaseObgectDeterminant*)createOfPulsar(name, range, declination, ascent, mass, frequency, magnitude, info);
        OBJ->type = OBJ_PULSAR;
        break;
    }
    case 5: { // ���������
        double count_stars = safe_get_double(L"\n������� �������������� ���������� �����: ", 0.0, DBL_MAX);
        OBJ->Objecte = (SpaseObgectDeterminant*)createOfGalaxy(name, range, declination, ascent, mass, count_stars, info);
        OBJ->type = OBJ_GALAXY;
        break;
    }
    case 6: { // �������� ���������
        double count_stars = safe_get_double(L"\n������� ���������� �����: ", 0.0, INT_MAX);
        OBJ->Objecte = (SpaseObgectDeterminant*)createOfStarCluster(name, range, declination, ascent, mass, count_stars, info);
        OBJ->type = OBJ_STARCLASTER;
        break;
    }
    default:
        wprintf(L"�������� �����!\n");
        free(name);
        free(OBJ);
        return NULL;
    }
    free(name);
    return OBJ;
}

void DestroyEllementMenu(SpaseAtlas* ATL) {
    wprintf(L"��������:\n1) ���������� ��������� �������\n2) ���������� ������������ �������\n��� �����: ");
    clear_input_buffer();
    int choice = safe_get_int(L"", 1, 2);

    switch (choice) {
    case 1:
        pop_Back(ATL);
        break;
    case 2: {
        int index = safe_get_int(L"������� ����� ���������� ��������", 0, ATL->size - 1);
        removeAt(ATL, index);
        break;
    }
    default:
        wprintf(L"�������� �����!\n");
        break;
    }
}









// ��������������� ������� ����������� �����
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
            wprintf(L"������������ ����! ���������� �����.\n");
            fflush(stdin);
            continue;
        }
        if (value >= min_val && value <= max_val) break;
        wprintf(L"�������� ������ ���� ����� %d � %d! ���������� �����.\n", min_val, max_val);
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
            wprintf(L"������������ ����! ���������� �����.\n");
            continue;
        }
        while (getchar() != '\n'); // ������� ������

        // �������������� ������������� ���������
        if (min_val > max_val) {
            double temp = min_val;
            min_val = max_val;
            max_val = temp;
        }

        if (value >= min_val && value <= max_val) break;
        wprintf(L"���������� ��������: %.2f - %.2f\n", min_val, max_val);
    }
    return value;
}


#include "StarsWork.h"

// ���� ��� ��������� ����� ������� � SpaseAtlas
void edit_object_menu(SpaseAtlas* atlas) {
    if (!atlas || atlas->size == 0) {
        wprintf(L"����� ����!\n");
        return;
    }

    // ����� ������� ��� ��������������
    wprintf(L"\n�������� ����� ������� ��� ��������� (0 - %d):\n", atlas->size - 1);
    for (int i = 0; i < atlas->copiseti; ++i) {
        wprintf(L"%d: %ls\n", i, atlas->unit[i].Objecte->name);
    }
    int idx = safe_get_int(L"������� ����� �������", 0, atlas->size - 1);
    ObjacteTipe* obj = &atlas->unit[idx];

    // �������� ���� ������ ����
    int exit_flag = 0;
    while (!exit_flag) {
        wprintf(L"\n�������� ���� ��� ���������:\n");
        wprintf(L"1. ��������\n2. ������ �����������\n3. ���������\n4. ����������\n5. �����\n6. ����������\n");

        // ����������� ���� ��� ���� �������
        switch (obj->type) {
        case OBJ_STAR:
            wprintf(L"7. ����� ������\n8. �������� ��������\n");
            break;
        case OBJ_BLACKHOLE:
            wprintf(L"7. ����� ������ ����\n");
            break;
        case OBJ_NEBULA:
            wprintf(L"7. ����� ����������\n");
            break;
        case OBJ_PULSAR:
            wprintf(L"7. ������� ��������\n8. �������� ��������\n");
            break;
        case OBJ_GALAXY:
            wprintf(L"7. ���������� �����\n");
            break;
        case OBJ_STARCLASTER:
            wprintf(L"7. ���������� �����\n");
            break;
        default:
            break;
        }
        wprintf(L"0. �����\n");

        int field = safe_get_int(L"��� �����", 0, 8);

        switch (field) {
        case 0:
            exit_flag = 1;
            break;
        case 1: { // ��������
            wprintf(L"����� �������� (�� 50 ��������): ");
            wchar_t* new_name = get_wstring(50);
            // Replace the problematic line with the following code to fix the error:
            wcsncpy_s(obj->Objecte->name, 51, new_name, _TRUNCATE);
            obj->Objecte->name[50] = L'\0';
            free(new_name);
            break;
        }
        case 2: { // ������ �����������
            wprintf(L"����� ������ �����������:\n");
            obj->Objecte->Ascent = input_direct_ascent();
            break;
        }
        case 3: // ���������
            obj->Objecte->declination = safe_get_double(L"����� ��������� (-90 �� 90): ", -90.0, 90.0);
            break;
        case 4: // ����������
            obj->Objecte->range = safe_get_double(L"����� ����������: ", 0.0, DBL_MAX);
            break;
        case 5: // �����
            obj->Objecte->mass = safe_get_double(L"����� �����: ", 0.0, DBL_MAX);
            break;
        case 6: { // ����������
            wprintf(L"������� ����� ���������� (�� 200 ��������): ");
            char* new_info = get_string(200);
            if (obj->Objecte->info.info) free(obj->Objecte->info.info);
            obj->Objecte->info.info = new_info;
            obj->Objecte->info.size = (int)strlen(new_info);
            break;
        }
              // ����������� ����
        case 7:
            switch (obj->type) {
            case OBJ_STAR: {
                wprintf(L"����� ����� ������ (�� 3 ��������): ");
                wchar_t* new_class = get_wstring(3);
                ((Star*)obj->Objecte)->starClass = _wcsdup(new_class);
                free(new_class);
                break;
            }
            case OBJ_BLACKHOLE: {
                wprintf(L"����� ����� ������ ���� (�� 50 ��������): ");
                wchar_t* new_class = get_wstring(50);
                ((BlackHole*)obj->Objecte)->blackHoleClass = _wcsdup(new_class);
                free(new_class);
                break;
            }
            case OBJ_NEBULA: {
                wprintf(L"����� ����� ���������� (�� 100 ��������): ");
                wchar_t* new_class = get_wstring(100);
                ((Nebula*)obj->Objecte)->nebulaClass = _wcsdup(new_class);
                free(new_class);
                break;
            }
            case OBJ_PULSAR: {
                ((Pulsar*)obj->Objecte)->pulsarFrequensy = safe_get_double(L"����� ������� ��������: ", 0.0, DBL_MAX);
                break;
            }
            case OBJ_GALAXY: {
                ((Galaxy*)obj->Objecte)->CountStar = safe_get_double(L"����� ���������� �����: ", 0.0, DBL_MAX);
                break;
            }
            case OBJ_STARCLASTER: {
                ((StarCluster*)obj->Objecte)->CountStar = (long unsigned)safe_get_double(L"����� ���������� �����: ", 0.0, INT_MAX);
                break;
            }
            default:
                wprintf(L"��� ������ ���� ��� ����� ���� �������.\n");
                break;
            }
            break;
        case 8:
            if (obj->type == OBJ_STAR) {
                ((Star*)obj->Objecte)->stellarMagnitude = safe_get_double(L"����� �������� ��������: ", -DBL_MAX, DBL_MAX);
            }
            else if (obj->type == OBJ_PULSAR) {
                ((Pulsar*)obj->Objecte)->stellarMagnitude = safe_get_double(L"����� �������� ��������: ", -DBL_MAX, DBL_MAX);
            }
            else {
                wprintf(L"��� ������ ���� ��� ����� ���� �������.\n");
            }
            break;
        default:
            wprintf(L"�������� �����!\n");
            break;
        }
    }
}

//������� ��� ������ ����� ������
void PrintHello() {
    printf("Hello");
}