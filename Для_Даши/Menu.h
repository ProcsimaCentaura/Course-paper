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

// Ввод прямого восхождения
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

// Основное меню создания объекта
ObjacteTipe* create_object_menu() {
    setlocale(LC_ALL, ""); // Для поддержки широких символов

    // Выбор типа объекта
    printf("\nSelect object type:\n");
    printf("1. Star\n2. Black Hole\n3. Nebula\n");
    printf("4. Pulsar\n5. Galaxy\n6. Star Cluster\n");
    printf("Choice: ");

    int choice;
    scanf_s("%d", &choice);
    fflush(stdin);

    // Общие поля для всех объектов
    wchar_t* name = NULL;
    directAscent ascent;
    double declination, range, mass;
    INFO info = { NULL, 0 };

    printf("\nEnter common parameters:\n");

    // Ввод имени
    printf("Object name (max 50 chars): ");
    name = get_wstring(50);

    // Прямое восхождение
    printf("\nDirect Ascent:\n");
    ascent = input_direct_ascent();

    // Склонение
    printf("Declination (-90 to 90): ");
    scanf_s("%lf", &declination);

    // Расстояние
    printf("Range (in light years): ");
    scanf_s("%lf", &range);

    // Масса
    printf("Mass (in solar masses): ");
    scanf_s("%lf", &mass);
    fflush(stdin);

    // Специфичные поля
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
    printf("Выберите:\n1)уничтожить последний эллемент, \n2)Уничтожить произвольный элемент");
    switch (getchar())
    {
    case 1: {
        pop_Back(ATL);
    }
          break;
    case 2: {
        printf("Введите номер удаляемого эллеметнта.");
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
    printf("\nМеню программы:\n");
    printf("\n1)Загрузить атлас из файла:");
    printf("\n2)Добавить эллемент: ");
    printf("\n3)Удалить эллемент: ");
    printf("\n4)Сортировать эллементы: ");
    printf("\n5)Поиск эллемента: ");
    printf("\n5)Рендер звездного неба: ");
    printf("\n7)Вывод таблицы объектов: ");
    printf("\n8)Сохранить атлас в файле: ");
    printf("\n9)Выйти из программы: ");
	while (1)
	{
        Choise = (CHOISE)getchar();
        switch (Choise)
        {
        case OPEN_FILE:
            deleteSpaseAtlas(ATL);
            printf("\nВведите название файла для загрузки.\n");
            char filename[100];
            scanf_s("%99s", &filename, 100);
            ATL = load_spase_atlas(filename);
            break;
        case ADD_ELEMENT:
            printf("\nМеню ввода элемента: \n");
            TEMP = create_object_menu();
            push_Back(ATL, *TEMP);
            free(TEMP);
            break;
        case REMOVE_ELEMENT:
            printf("\nМеню уничтожения элемента: \n");
            DestroyEllementMenu(ATL);
            break;
        case SORT_ATLAS:
        {
            printf("\nМеню сортировки:\n");
            printf("\n1)Сортировать по типу");
            printf("\n2)Сортировать по имени");
            printf("\n3)Сортировать по восхождению");
            printf("\n4)Сортировать по наклонению");
            printf("\n5)Сортировать по расстоянии");
            printf("\n5)Сортировать по массе");
            printf("\n7)Сортировать по звездному классу");
            printf("\n8)Сортировать по звездной магнитуде");
            printf("\n9)Сортировать черные дыры по классу черной дыры");
            printf("\n10)Сортировать туманности по классу туманности");
            printf("\n11)Сортировать пульсар по частоте");
            printf("\n12)Сортировать пульсар по магнитуде");
            printf("\n13)Сортировать галлактики по количеству звезд");
            printf("\n14)Сортировать звездные скопления по количеству звезд");
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
            printf("\nМеню поиска:\n");
            printf("\n1)Искать по типу");
            printf("\n2)Искать по имени");
            printf("\n3)Искать по восхождению");
            printf("\n4)Искать по наклонению");
            printf("\n5)Искать по расстоянии");
            printf("\n5)Искать по массе");
            printf("\n7)Искать по звездному классу");
            printf("\n8)Искать по звездной магнитуде");
            printf("\n9)Искать черные дыры по классу черной дыры");
            printf("\n10)Искать туманности по классу туманности");
            printf("\n11)Искать пульсар по частоте");
            printf("\n12)Искать пульсар по магнитуде");
            printf("\n13)Сортировать галлактики по количеству звезд");
            printf("\n14)Сортировать звездные скопления по количеству звезд");
            SerchType serchType;
            int Choisees;
            scanf_s("%d", &Choisees);
            switch (Choisees)
            {
            case 1:
                serchType = SERCH_BY_TYPE;
                printf("\nВведите тип:");
                printf("\n1)Искать звезды");
                printf("\n2)Искать черные дыры");
                printf("\n3)Искать туманности");
                printf("\n4)Искать пульсары");
                printf("\n5)Искать галлактики");
                printf("\n6)Искать звездные скопления");
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
                printf("\nВведите имя искомого, небесного тела: ");
                wchar_t* tempCHAR;
                tempCHAR = get_wstring(50);//Функция автоматически создает место
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
            printf("\nСохранить результат поиска в оттельном файле?");
            printf("\n1)Да\n2)Нет");
            char tempChar;
            while(1)
            {
                tempChar = getchar();
                if (tempChar == 1)
                {
                    printf("\nВведите название файла для загрузки.\n");
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
            printf("\nВведите название файла для загрузки.\n");
            char filename[100];
            scanf_s("%99s", &filename, 100);
            if (!save_spase_atlas(ATL, filename)) {
                printf("Save failed!\n");
                deleteSpaseAtlas(ATL);
                ATL = nullptr;
            }
            break;
        case EXIT:
            printf("\nВы уверены что хотите покинуть программу?\nЕсли да, нажмити любую клавишу кроме 0.");
            if (!getchar()) continue;
            deleteSpaseAtlas(ATL);
            return;
            break;
        default:

            break;
        }
	}
}