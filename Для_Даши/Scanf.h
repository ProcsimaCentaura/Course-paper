#pragma once

// ��������� ��������������� �������
void clear_input_buffer();
int safe_get_int(const wchar_t* prompt, int min_val, int max_val);
double safe_get_double(const wchar_t* prompt, double min_val, double max_val);

//�� ������ ����� � �������.

// ���� ������� ������ � �������
wchar_t* get_wstring(int max_len) {
    wchar_t* buffer = (wchar_t*)malloc((max_len + 1) * sizeof(wchar_t));
    if (!buffer) return NULL;
    fflush(stdin);
    fgetws(buffer, max_len, stdin);
    fflush(stdin);
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
    fflush(stdin);
    size_t len = strlen(buffer);
    if (len > 0 && buffer[len - 1] == L'\n')
        buffer[len - 1] = L'\0';

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

// �������� ���� �������� �������
ObjacteTipe* create_object_menu() {
    setlocale(LC_ALL, ""); // ��� ��������� ������� ��������

    // ����� ���� �������
    wprintf(L"\n�������� ��� �������:\n");
    wprintf(L"1. ������\n2. ������ ����\n3. ����������\n");
    wprintf(L"4. �������\n5. ���������\n6. �������� ���������\n");
    wprintf(L"��� �����: ");

    int choice;
    scanf_s("%d", &choice);
    fflush(stdin);

    // ����� ���� ��� ���� ��������
    wchar_t* name = NULL;
    directAscent ascent;
    double declination, range, mass;
    INFO info = { NULL, 0 };

    wprintf(L"\n������� ����� ���������:\n");

    // ���� �����
    wprintf(L"�������� ������� (���� 50 ��������): ");
    name = get_wstring(50);

    // ������ �����������
    wprintf(L"\n������ �����������:\n");
    ascent = input_direct_ascent();

    // ���������
    wprintf(L"��������� (-90 �� 90): ");
    scanf_s("%lf", &declination);

    // ����������
    wprintf(L"���������� (� �������� �����): ");
    scanf_s("%lf", &range);

    // �����
    wprintf(L"����� (� ��������� ������): ");
    scanf_s("%lf", &mass);
    fflush(stdin);

    // ����������� ����
    switch (choice) {
    case 1: { // Star
        wchar_t* star_class;
        double magnitude;

        wprintf(L"\n������� ����� ������ (�� 3 ��������): ");
        star_class = get_wstring(3);

        wprintf(L"�������� ��������: ");
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

        wprintf(L"\n������� ����� ������ ���� (�� 50 ��������): ");
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

        wprintf(L"\n������� ����� ���������� (�� 100 ��������): ");
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

        wprintf(L"\n������� ������� �������� (��): ");
        scanf_s("%lf", &frequency);

        wprintf(L"�������� ��������: ");
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

        wprintf(L"\n������� �������������� ���������� �����: ");
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

        wprintf(L"\n������� ���������� �����: ");
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
        wprintf(L"�������� �����!\n");
        free(name);
        return NULL;
    }
}

void DestroyEllementMenu(SpaseAtlas* ATL) {
    wprintf(L"��������:\n1)���������� ��������� ��������, \n2)���������� ������������ �������");
    switch (getchar())
    {
    case 1: {
        pop_Back(ATL);
    }
          break;
    case 2: {
        wprintf(L"������� ����� ���������� ����������.");
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





// ��������������� ������� ����������� �����
void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int safe_get_int(const wchar_t* prompt, int min_val, int max_val) {
    int value;
    while (1) {
        if (prompt) wprintf(L"%ls: ", prompt);
        if (wscanf_s(L"%d", &value, 4) != 1) {
            wprintf(L"������������ ����! ���������� �����.\n");
            clear_input_buffer();
            continue;
        }
        if (value >= min_val && value <= max_val) break;
        wprintf(L"�������� ������ ���� ����� %d � %d! ���������� �����.\n", min_val, max_val);
    }
    return value;
}

double safe_get_double(const wchar_t* prompt, double min_val, double max_val) {
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