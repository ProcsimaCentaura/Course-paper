#pragma once

//�� ������ ����� � �������.

// ���� ������� ������ � �������
wchar_t* get_wstring(int max_len) {
    wchar_t* buffer = (wchar_t*)malloc((max_len + 1) * sizeof(wchar_t));
    if (!buffer) return NULL;

    fgetws(buffer, max_len, stdin);
    size_t len = wcslen(buffer);
    if (len > 0 && buffer[len - 1] == L'\n')
        buffer[len - 1] = L'\0';

    return buffer;
}

// ���� ������� �����������
directAscent input_direct_ascent() {
    directAscent da;
    printf("Enter hours (0-23): ");
    scanf_s("%d", &da.hour);
    printf("Enter minutes (0-59): ");
    scanf_s("%d", &da.minutes);
    printf("Enter seconds (0-59.999): ");
    scanf_s("%lf", &da.seconds);
    fflush(stdin);
    return da;
}

// �������� ���� �������� �������
ObjacteTipe* create_object_menu() {
    setlocale(LC_ALL, ""); // ��� ��������� ������� ��������

    // ����� ���� �������
    printf("\nSelect object type:\n");
    printf("1. Star\n2. Black Hole\n3. Nebula\n");
    printf("4. Pulsar\n5. Galaxy\n6. Star Cluster\n");
    printf("Choice: ");

    int choice;
    scanf_s("%d", &choice);
    fflush(stdin);

    // ����� ���� ��� ���� ��������
    wchar_t* name = NULL;
    directAscent ascent;
    double declination, range, mass;
    INFO info = { NULL, 0 };

    printf("\nEnter common parameters:\n");

    // ���� �����
    printf("Object name (max 50 chars): ");
    name = get_wstring(50);

    // ������ �����������
    printf("\nDirect Ascent:\n");
    ascent = input_direct_ascent();

    // ���������
    printf("Declination (-90 to 90): ");
    scanf_s("%lf", &declination);

    // ����������
    printf("Range (in light years): ");
    scanf_s("%lf", &range);

    // �����
    printf("Mass (in solar masses): ");
    scanf_s("%lf", &mass);
    fflush(stdin);

    // ����������� ����
    switch (choice) {
    case 1: { // Star
        wchar_t* star_class;
        double magnitude;

        printf("\nEnter star class (up to 3 chars): ");
        star_class = get_wstring(3);

        printf("Stellar magnitude: ");
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

        printf("\nEnter black hole class (up to 50 chars): ");
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

        printf("\nEnter nebula class (up to 100 chars): ");
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

        printf("\nEnter pulsar frequency (Hz): ");
        scanf_s("%lf", &frequency);

        printf("Stellar magnitude: ");
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

        printf("\nEnter estimated star count: ");
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

        printf("\nEnter star count: ");
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
        printf("Invalid choice!\n");
        free(name);
        return NULL;
    }
}

void DestroyEllementMenu(SpaseAtlas* ATL) {
    printf("��������:\n1)���������� ��������� ��������, \n2)���������� ������������ �������");
    switch (getchar())
    {
    case 1: {
        pop_Back(ATL);
    }
          break;
    case 2: {
        printf("������� ����� ���������� ����������.");
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
    OPEN_FILE,
    ADD_ELEMENT,
    REMOVE_ELEMENT,
    SORT_ATLAS,
    SEARCH_ATLAS,
    RENDER_SKY,
    DISPLAY_TABLE,
    SAVE_THE_ATLAS,
    EXIT
};





void Menu(SpaseAtlas* ATL) {
    CHOISE Choise;
    ObjacteTipe* TEMP;
    SpaseAtlas* temp = nullptr;
    printf("\n���� ���������:\n");
    printf("\n1)��������� ����� �� �����:");
    printf("\n2)�������� ��������: ");
    printf("\n3)������� ��������: ");
    printf("\n4)����������� ���������: ");
    printf("\n5)����� ���������: ");
    printf("\n5)������ ��������� ����: ");
    printf("\n7)����� ������� ��������: ");
    printf("\n8)��������� ����� � �����: ");
    printf("\n9)����� �� ���������: ");
	while (1)
	{
        Choise = (CHOISE)getchar();
        switch (Choise)
        {
        case OPEN_FILE:
            deleteSpaseAtlas(ATL);
            printf("\n������� �������� ����� ��� ��������.\n");
            char filename[100];
            scanf_s("%99s", &filename, 100);
            ATL = load_spase_atlas(filename);
            break;
        case ADD_ELEMENT:
            printf("\n���� ����� ��������: \n");
            TEMP = create_object_menu();
            push_Back(ATL, *TEMP);
            free(TEMP);
            break;
        case REMOVE_ELEMENT:
            printf("\n���� ����������� ��������: \n");
            DestroyEllementMenu(ATL);
            break;
        case SORT_ATLAS:
        {
            printf("\n���� ����������:\n");
            printf("\n1)����������� �� ����");
            printf("\n2)����������� �� �����");
            printf("\n3)����������� �� �����������");
            printf("\n4)����������� �� ����������");
            printf("\n5)����������� �� ����������");
            printf("\n5)����������� �� �����");
            printf("\n7)����������� �� ��������� ������");
            printf("\n8)����������� �� �������� ���������");
            printf("\n9)����������� ������ ���� �� ������ ������ ����");
            printf("\n10)����������� ���������� �� ������ ����������");
            printf("\n11)����������� ������� �� �������");
            printf("\n12)����������� ������� �� ���������");
            printf("\n13)����������� ���������� �� ���������� �����");
            printf("\n14)����������� �������� ��������� �� ���������� �����");
            SortType sortType;
            int Choisees;
            scanf_s("%d", &Choisees);
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
            sortOfAtlass(ATL,sortType);
        }
            break;
        case SEARCH_ATLAS: 
            printf("\n���� ������:\n");
            printf("\n1)������ �� ����");
            printf("\n2)������ �� �����");
            printf("\n3)������ �� �����������");
            printf("\n4)������ �� ����������");
            printf("\n5)������ �� ����������");
            printf("\n5)������ �� �����");
            printf("\n7)������ �� ��������� ������");
            printf("\n8)������ �� �������� ���������");
            printf("\n9)������ ������ ���� �� ������ ������ ����");
            printf("\n10)������ ���������� �� ������ ����������");
            printf("\n11)������ ������� �� �������");
            printf("\n12)������ ������� �� ���������");
            printf("\n13)����������� ���������� �� ���������� �����");
            printf("\n14)����������� �������� ��������� �� ���������� �����");
            SerchType serchType;
            int Choisees;
            scanf_s("%d", &Choisees);
            switch (Choisees)
            {
            case 1:
                serchType = SERCH_BY_TYPE;
                printf("\n������� ���:");
                printf("\n1)������ ������");
                printf("\n2)������ ������ ����");
                printf("\n3)������ ����������");
                printf("\n4)������ ��������");
                printf("\n5)������ ����������");
                printf("\n6)������ �������� ���������");
                TypeOfObjecte TypeObjectSerch;
                switch (getchar())
                {
                case 1:
                    TypeObjectSerch = OBJ_STAR;
                    break;
                case 2:
                    TypeObjectSerch = OBJ_BLACKHOLE;
                    break;
                case 3:
                    TypeObjectSerch = OBJ_NEBULA;
                    break;
                case 4:
                    TypeObjectSerch = OBJ_PULSAR;
                    break;
                case 5:
                    TypeObjectSerch = OBJ_GALAXY;
                    break;
                case 6:
                    TypeObjectSerch = OBJ_STARCLASTER;
                    break;
                default:
                    break;
                }
                temp = SerchInDiapazone(ATL, serchType, TypeObjectSerch);
                
                break;
            case 2:
                serchType = SERCH_BY_NAME;
                printf("\n������� ��� ��������, ��������� ����: ");
                wchar_t* tempCHAR;
                tempCHAR = get_wstring(50);//������� ������������� ������� �����
                temp = SerchInDiapazone(ATL, serchType, tempCHAR);
                free(tempCHAR);
                tempCHAR = nullptr;
                break;
            case 3:
            {
                double tempAscentMin(ascent_to_degrees(input_direct_ascent())), 
                    tempAscentMax(ascent_to_degrees(input_direct_ascent()));
                serchType = SERCH_BY_ASCENT;
                    temp = SerchInDiapazone(ATL, serchType, tempAscentMin, tempAscentMax);
            }
                break;
            case 4:
            {
                double DislinationMin, DislinationMax;
                scanf_s("%d,%d", &DislinationMin, &DislinationMax);
                serchType = SERCH_BY_DISLINATION;
                temp = SerchInDiapazone(ATL, serchType, DislinationMin, DislinationMax);
            }

                break;
            case 5:
            {
                double RangeMin, RangeMax;
                scanf_s("%d,%d", &RangeMin, &RangeMax);
                serchType = SERCH_BY_RANGE;
                temp = SerchInDiapazone(ATL, serchType, RangeMin, RangeMax);
            }
                break;
            case 6:
            {
                double MassMin, MassMax;
                scanf_s("%d,%d", &MassMin, &MassMax);
                serchType = SERCH_BY_MASS;
                temp = SerchInDiapazone(ATL, serchType, MassMin, MassMax);
            }
                break;
            case 7:
                serchType = SERCH_STAR_BY_STAR_CLASS;
                temp = SerchInDiapazone(ATL, serchType, tempCHAR);
                break;
            case 8:
                serchType = SERCH_STAR_BY_STELLAR_MAGNITUDE;
                temp = SerchInDiapazone(ATL, serchType, tempCHAR);
                break;
            case 9:
                serchType = SERCH_BLACK_HOLE_BY_BLACK_HOLE_CLASS;
                temp = SerchInDiapazone(ATL, serchType, tempCHAR);
                break;
            case 10:
                serchType = SERCH_NEBULA_BY_NEBULA_CLASS;
                temp = SerchInDiapazone(ATL, serchType, tempCHAR);
                break;
            case 11:
                serchType = SERCH_PULSAR_BY_PULSAR_FREQUENSY;
                temp = SerchInDiapazone(ATL, serchType, tempCHAR);
                break;
            case 12:
                serchType = SERCH_PULSAR_BY_STELLAR_MAGNITUDE;
                temp = SerchInDiapazone(ATL, serchType, tempCHAR);
                break;
            case 13:
                serchType = SERCH_GALLAXY_BY_COUNT_STAR;
                temp = SerchInDiapazone(ATL, serchType, tempCHAR);
                break;
            case 14:
                serchType = SERCH_STAR_CLASTER_BY_COUNT_STAR;
                temp = SerchInDiapazone(ATL, serchType, tempCHAR);
                break;
            default:
                break;
            }
            print_table(temp);
            printf("\n��������� ��������� ������ � ��������� �����?");
            printf("\n1)��\n2)���");
            char tempChar;
            while(1)
            {
                tempChar = getchar();
                if (tempChar == 1)
                {
                    printf("\n������� �������� ����� ��� ��������.\n");
                    char filename[100];
                    scanf_s("%99s", &filename, 100);
                    if (!save_spase_atlas(temp, filename)) {
                        printf("Save failed!\n");
                        free(temp);
                        temp = nullptr;
                    }
                    break;
                }
                else if (tempChar == 2) {
                    break;
                }
            }
            break;
        case RENDER_SKY:
            render_atlas(ATL);
            break;
        case DISPLAY_TABLE:
            print_table(ATL);
            break;
        case SAVE_THE_ATLAS:
            printf("\n������� �������� ����� ��� ��������.\n");
            char filename[100];
            scanf_s("%99s", &filename, 100);
            if (!save_spase_atlas(ATL, filename)) {
                printf("Save failed!\n");
                deleteSpaseAtlas(ATL);
                ATL = nullptr;
            }
            break;
        case EXIT:
            printf("\n�� ������� ��� ������ �������� ���������?\n���� ��, ������� ����� ������� ����� 0.");
            if (!getchar()) continue;
            deleteSpaseAtlas(ATL);
            return;
            break;
        default:

            break;
        }
	}
}