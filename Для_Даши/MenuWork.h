#pragma once


void Menu(SpaseAtlas* ATL) {
    char STRCHOISE[100];
    CHOISE Choise;
    int searchChoice;
    ObjacteTipe* TEMP;
    SpaseAtlas* temp = nullptr;
    int STRlen;
    SpaseAtlas* newATL;
    ObjacteTipe* newObj;

    TypeOfObjecte typeChoice;

    char* filename;
    wchar_t* searchStr = NULL;
    double minVal, maxVal;
    int countMin = 0, countMax = 0;

    while (1)
    {
        wprintf(L"\n=== ���� ��������� ===\n");
        wprintf(L"1) ��������� ����� �� �����\n");
        wprintf(L"2) �������� �������\n");
        wprintf(L"3) ������� �������\n");
        wprintf(L"4) ����������� ��������\n");
        wprintf(L"5) ����� ��������\n");
        wprintf(L"6) ������ ��������� ����\n");
        wprintf(L"7) ����� ������� ��������\n");
        wprintf(L"8) ��������� ����� � �����\n");
        wprintf(L"9) ����� �� ���������\n");
        wprintf(L"�������� ��������: ");

        Choise = (CHOISE)safe_get_int(L"", 1, 9);
        clear_input_buffer();


        switch (Choise)
        {
        case OPEN_FILE:
            wprintf(L"\n������� �������� ����� ��� ��������: ");
            filename = get_string(255);
            newATL = load_spase_atlas(filename);
            free(filename);
            if (newATL) {
                deleteSpaseAtlas(ATL);
                ATL = newATL;
                wprintf(L"����� ������� ��������!\n");
            }
            else {
                wprintf(L"������ �������� �����!\n");
            }
            break;
        case ADD_ELEMENT:
            wprintf(L"\n=== ���������� ������ ������� ===\n");
            newObj = create_object_menu();
            if (newObj) {
                push_Back(ATL, *newObj);
                free(newObj);
                wprintf(L"������ ������� ��������!\n");
            }
            else {
                wprintf(L"������ �������� �������!\n");
            }
            break;
        case REMOVE_ELEMENT:
            wprintf(L"\n���� ����������� ��������: \n");
            DestroyEllementMenu(ATL);
            break;
        case SORT_ATLAS:
        {
            wprintf(L"\n���� ����������:\n");
            wprintf(L"\n1)����������� �� ����");
            wprintf(L"\n2)����������� �� �����");
            wprintf(L"\n3)����������� �� �����������");
            wprintf(L"\n4)����������� �� ����������");
            wprintf(L"\n5)����������� �� ����������");
            wprintf(L"\n5)����������� �� �����");
            wprintf(L"\n7)����������� �� ��������� ������");
            wprintf(L"\n8)����������� �� �������� ���������");
            wprintf(L"\n9)����������� ������ ���� �� ������ ������ ����");
            wprintf(L"\n10)����������� ���������� �� ������ ����������");
            wprintf(L"\n11)����������� ������� �� �������");
            wprintf(L"\n12)����������� ������� �� ���������");
            wprintf(L"\n13)����������� ��������� �� ���������� �����");
            wprintf(L"\n14)����������� �������� ��������� �� ���������� �����");
            SortType sortType;

            fflush(stdin);
            int Choisees = safe_get_int(L"�������� ��� ����������", 1, 14);
            switch (Choisees)
            {
            case 1:
                sortType = SORT_BY_TYPE;
                break;
            case 2:
                sortType = SORT_BY_NAME;
                break;
            case 3:
                sortType = SORT_BY_ASCENT;
                break;
            case 4:
                sortType = SORT_BY_DISLINATION;
                break;
            case 5:
                sortType = SORT_BY_RANGE;
                break;
            case 6:
                sortType = SORT_BY_MASS;
                break;
            case 7:
                sortType = SORT_STAR_BY_STAR_CLASS;
                break;
            case 8:
                sortType = SORT_STAR_BY_STELLAR_MAGNITUDE;
                break;
            case 9:
                sortType = SORT_BLACK_HOLE_BY_BLACK_HOLE_CLASS;
                break;
            case 10:
                sortType = SORT_NEBULA_BY_NEBULA_CLASS;
                break;
            case 11:
                sortType = SORT_PULSAR_BY_PULSAR_FREQUENSY;
                break;
            case 12:
                sortType = SORT_PULSAR_BY_STELLAR_MAGNITUDE;
                break;
            case 13:
                sortType = SORT_GALLAXY_BY_COUNT_STAR;
                break;
            case 14:
                sortType = SORT_STAR_CLASTER_BY_COUNT_STAR;
                break;
            default:
                break;
            }
            sortOfAtlass(ATL, sortType);
        }
        break;
        case SEARCH_ATLAS: {
            if (ATL->copiseti == 0) {
                wprintf(L"\n����� ����! ����� ����������.\n");
                break;
            }


            wprintf(L"\n=== ���� ������ ===\n");
            wprintf(L"1) �� ���� �������\n");
            wprintf(L"2) �� �����\n");
            wprintf(L"3) �� ������� �����������\n");
            wprintf(L"4) �� ���������\n");
            wprintf(L"5) �� ����������\n");
            wprintf(L"6) �� �����\n");
            wprintf(L"7) �� ��������� ������\n");
            wprintf(L"8) �� �������� ��������\n");
            wprintf(L"9) �� ������ ������ ����\n");
            wprintf(L"10) �� ������ ����������\n");
            wprintf(L"11) �� ������� ��������\n");
            wprintf(L"12) �� ��������� ��������\n");
            wprintf(L"13) �� ���������� ����� � ���������\n");
            wprintf(L"14) �� ���������� ����� � ���������\n");
            wprintf(L"�������� ��� ������: ");

            // ���������� ���� ������ ������
            searchChoice = safe_get_int(L"", 1, 14);
            clear_input_buffer();

            switch (searchChoice) {
            case 1: { // �� ���� �������
                wprintf(L"\n�������� ��� �������:\n");
                wprintf(L"1) ������\n2) ������ ����\n3) ����������\n");
                wprintf(L"4) �������\n5) ���������\n6) �������� ���������\n");

                int typeInput = safe_get_int(L"��� �����", 1, 6);
                clear_input_buffer();

                typeChoice = static_cast<TypeOfObjecte>(typeInput - 1);
                temp = SerchInDiapazone(ATL, SERCH_BY_TYPE, typeChoice);
                break;
            }

            case 2: { // �� �����
                wprintf(L"\n������� ��� ��� ������: ");
                searchStr = get_wstring(50);
                temp = SerchInDiapazone(ATL, SERCH_BY_NAME, searchStr);
                free(searchStr);
                break;
            }

            case 3: { // ������ �����������
                wprintf(L"\n������� ����������� ��������: ");
                minVal = ascent_to_degrees(input_direct_ascent());
                wprintf(L"������� ������������ ��������: ");
                maxVal = ascent_to_degrees(input_direct_ascent());
                temp = SerchInDiapazone(ATL, SERCH_BY_ASCENT, minVal, maxVal);
                break;
            }

            case 4: // ���������
            case 5: // ����������
            case 6: { // �����
                const wchar_t* paramName[] = { L"���������", L"����������", L"�����" };
                wprintf(L"\n������� �������� ��� %ls:\n", paramName[searchChoice - 4]);//������������� ������� case �� ������)))
                minVal = safe_get_double(L"����������� ��������", 0.0, DBL_MAX);
                maxVal = safe_get_double(L"������������ ��������", minVal, DBL_MAX);

                SerchType types[] = { SERCH_BY_DISLINATION, SERCH_BY_RANGE, SERCH_BY_MASS };
                temp = SerchInDiapazone(ATL, types[searchChoice - 4], minVal, maxVal);
                break;
            }

            case 7: { // �������� �����
                wprintf(L"\n������� �������� �����: ");
                searchStr = get_wstring(3);
                temp = SerchInDiapazone(ATL, SERCH_STAR_BY_STAR_CLASS, searchStr);
                free(searchStr);
                break;
            }

            case 8: { // �������� ��������
                wprintf(L"\n������� �������� �������� ��������:\n");
                minVal = safe_get_double(L"����������� ��������", -50.0, 50.0);
                maxVal = safe_get_double(L"������������ ��������", minVal, 50.0);
                temp = SerchInDiapazone(ATL, SERCH_STAR_BY_STELLAR_MAGNITUDE, minVal, maxVal);
                break;
            }

            case 9: { // ����� ������ ����
                wprintf(L"\n������� ����� ������ ����: ");
                searchStr = get_wstring(50);
                temp = SerchInDiapazone(ATL, SERCH_BLACK_HOLE_BY_BLACK_HOLE_CLASS, searchStr);
                free(searchStr);
                break;
            }

            case 10: { // ����� ����������
                wprintf(L"\n������� ����� ����������: ");
                searchStr = get_wstring(100);
                temp = SerchInDiapazone(ATL, SERCH_NEBULA_BY_NEBULA_CLASS, searchStr);
                free(searchStr);
                break;
            }

            case 11: { // ������� ��������
                wprintf(L"\n������� �������� �������:\n");
                minVal = safe_get_double(L"����������� ������� (Hz)", 0.0, DBL_MAX);
                maxVal = safe_get_double(L"������������ ������� (Hz)", minVal, DBL_MAX);
                temp = SerchInDiapazone(ATL, SERCH_PULSAR_BY_PULSAR_FREQUENSY, minVal, maxVal);
                break;
            }

            case 12: { // ��������� ��������
                wprintf(L"\n������� �������� ���������:\n");
                minVal = safe_get_double(L"����������� ���������", -50.0, 50.0);
                maxVal = safe_get_double(L"������������ ���������", minVal, 50.0);
                temp = SerchInDiapazone(ATL, SERCH_PULSAR_BY_STELLAR_MAGNITUDE, minVal, maxVal);
                break;
            }

            case 13: { // ������ � ���������
                wprintf(L"\n������� �������� ���������� �����:\n");
                minVal = safe_get_double(L"����������� ����������", 0.0, DBL_MAX);
                maxVal = safe_get_double(L"������������ ����������", minVal, DBL_MAX);
                temp = SerchInDiapazone(ATL, SERCH_GALLAXY_BY_COUNT_STAR, minVal, maxVal);
                break;
            }

            case 14: { // ������ � ���������
                wprintf(L"\n������� �������� ���������� �����:\n");
                unsigned long min = safe_get_int(L"����������� ����������", 0, INT_MAX);
                unsigned long max = safe_get_int(L"������������ ����������", min, INT_MAX);
                temp = SerchInDiapazone(ATL, SERCH_STAR_CLASTER_BY_COUNT_STAR,
                    static_cast<double>(min), static_cast<double>(max));
                break;
            }
            }

            // ��������� �����������
            if (temp && temp->copiseti > 0) {
                print_table(temp);
                wprintf(L"\n������� ��������: %d\n", temp->copiseti);

                wprintf(L"\n��������� ���������� ������? (1 - ��, 0 - ���): ");
                if (safe_get_int(L"", 0, 1) == 1) {
                    wprintf(L"������� ��� �����: ");
                    filename = get_string(255);
                    if (!save_spase_atlas(temp, filename)) {
                        wprintf(L"������ ���������� �����!\n");
                    }
                }
            }
            else if (temp == nullptr) {
                wprintf(L"\n������ ��� ���������� ���������� �������.!\n");
            }
            else {
                wprintf(L"\n������� �� �������!\n");
            }

            if (temp) {
                free(temp);
            }
            break;
        }
                         break;
        case RENDER_SKY:
            render_atlas(ATL);
            break;
        case DISPLAY_TABLE:
            print_table(ATL);
            break;
        case SAVE_THE_ATLAS:
            wprintf(L"\n������� �������� ����� ��� ��������.\n");
            fflush(stdin);
            scanf_s("%99s", &filename, 100);
            if (!save_spase_atlas(ATL, filename)) {
                wprintf(L"Save failed!\n");
                deleteSpaseAtlas(ATL);
                ATL = nullptr;
            }
            break;
        case EXIT:
            wprintf(L"\n�� ������� ��� ������ �������� ���������?\n���� ��, ������� ����� ������� ����� 0.");
            if (!getchar()) continue;
            deleteSpaseAtlas(ATL);
            return;
            break;
        default:
            break;
        }

    }
}

