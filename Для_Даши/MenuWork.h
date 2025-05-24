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
        wprintf(L"\n=== Меню программы ===\n");
        wprintf(L"1) Загрузить атлас из файла\n");
        wprintf(L"2) Добавить элемент\n");
        wprintf(L"3) Удалить элемент\n");
        wprintf(L"4) Сортировать элементы\n");
        wprintf(L"5) Поиск элемента\n");
        wprintf(L"6) Рендер звездного неба\n");
        wprintf(L"7) Вывод таблицы объектов\n");
        wprintf(L"8) Сохранить атлас в файле\n");
        wprintf(L"9) Выйти из программы\n");
        wprintf(L"Выберите действие: ");

        Choise = (CHOISE)safe_get_int(L"", 1, 9);
        clear_input_buffer();


        switch (Choise)
        {
        case OPEN_FILE:
            wprintf(L"\nВведите название файла для загрузки: ");
            filename = get_string(255);
            newATL = load_spase_atlas(filename);
            free(filename);
            if (newATL) {
                deleteSpaseAtlas(ATL);
                ATL = newATL;
                wprintf(L"Атлас успешно загружен!\n");
            }
            else {
                wprintf(L"Ошибка загрузки файла!\n");
            }
            break;
        case ADD_ELEMENT:
            wprintf(L"\n=== Добавление нового объекта ===\n");
            newObj = create_object_menu();
            if (newObj) {
                push_Back(ATL, *newObj);
                free(newObj);
                wprintf(L"Объект успешно добавлен!\n");
            }
            else {
                wprintf(L"Ошибка создания объекта!\n");
            }
            break;
        case REMOVE_ELEMENT:
            wprintf(L"\nМеню уничтожения элемента: \n");
            DestroyEllementMenu(ATL);
            break;
        case SORT_ATLAS:
        {
            wprintf(L"\nМеню сортировки:\n");
            wprintf(L"\n1)Сортировать по типу");
            wprintf(L"\n2)Сортировать по имени");
            wprintf(L"\n3)Сортировать по восхождению");
            wprintf(L"\n4)Сортировать по наклонению");
            wprintf(L"\n5)Сортировать по расстоянии");
            wprintf(L"\n5)Сортировать по массе");
            wprintf(L"\n7)Сортировать по звездному классу");
            wprintf(L"\n8)Сортировать по звездной магнитуде");
            wprintf(L"\n9)Сортировать черные дыры по классу черной дыры");
            wprintf(L"\n10)Сортировать туманности по классу туманности");
            wprintf(L"\n11)Сортировать пульсар по частоте");
            wprintf(L"\n12)Сортировать пульсар по магнитуде");
            wprintf(L"\n13)Сортировать галактики по количеству звезд");
            wprintf(L"\n14)Сортировать звездные скопления по количеству звезд");
            SortType sortType;

            fflush(stdin);
            int Choisees = safe_get_int(L"Выберите тип сортировки", 1, 14);
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
                wprintf(L"\nАтлас пуст! Поиск невозможен.\n");
                break;
            }


            wprintf(L"\n=== Меню поиска ===\n");
            wprintf(L"1) По типу объекта\n");
            wprintf(L"2) По имени\n");
            wprintf(L"3) По прямому восхождению\n");
            wprintf(L"4) По склонению\n");
            wprintf(L"5) По расстоянию\n");
            wprintf(L"6) По массе\n");
            wprintf(L"7) По звездному классу\n");
            wprintf(L"8) По звездной величине\n");
            wprintf(L"9) По классу черной дыры\n");
            wprintf(L"10) По классу туманности\n");
            wprintf(L"11) По частоте пульсара\n");
            wprintf(L"12) По магнитуде пульсара\n");
            wprintf(L"13) По количеству звезд в галактике\n");
            wprintf(L"14) По количеству звезд в скоплении\n");
            wprintf(L"Выберите тип поиска: ");

            // Безопасный ввод выбора поиска
            searchChoice = safe_get_int(L"", 1, 14);
            clear_input_buffer();

            switch (searchChoice) {
            case 1: { // По типу объекта
                wprintf(L"\nВыберите тип объекта:\n");
                wprintf(L"1) Звезда\n2) Черная дыра\n3) Туманность\n");
                wprintf(L"4) Пульсар\n5) Галактика\n6) Звездное скопление\n");

                int typeInput = safe_get_int(L"Ваш выбор", 1, 6);
                clear_input_buffer();

                typeChoice = static_cast<TypeOfObjecte>(typeInput - 1);
                temp = SerchInDiapazone(ATL, SERCH_BY_TYPE, typeChoice);
                break;
            }

            case 2: { // По имени
                wprintf(L"\nВведите имя для поиска: ");
                searchStr = get_wstring(50);
                temp = SerchInDiapazone(ATL, SERCH_BY_NAME, searchStr);
                free(searchStr);
                break;
            }

            case 3: { // Прямое восхождение
                wprintf(L"\nВведите минимальное значение: ");
                minVal = ascent_to_degrees(input_direct_ascent());
                wprintf(L"Введите максимальное значение: ");
                maxVal = ascent_to_degrees(input_direct_ascent());
                temp = SerchInDiapazone(ATL, SERCH_BY_ASCENT, minVal, maxVal);
                break;
            }

            case 4: // Склонение
            case 5: // Расстояние
            case 6: { // Масса
                const wchar_t* paramName[] = { L"склонение", L"расстояние", L"массу" };
                wprintf(L"\nВведите диапазон для %ls:\n", paramName[searchChoice - 4]);//использование свойств case по полной)))
                minVal = safe_get_double(L"Минимальное значение", 0.0, DBL_MAX);
                maxVal = safe_get_double(L"Максимальное значение", minVal, DBL_MAX);

                SerchType types[] = { SERCH_BY_DISLINATION, SERCH_BY_RANGE, SERCH_BY_MASS };
                temp = SerchInDiapazone(ATL, types[searchChoice - 4], minVal, maxVal);
                break;
            }

            case 7: { // Звездный класс
                wprintf(L"\nВведите звездный класс: ");
                searchStr = get_wstring(3);
                temp = SerchInDiapazone(ATL, SERCH_STAR_BY_STAR_CLASS, searchStr);
                free(searchStr);
                break;
            }

            case 8: { // Звездная величина
                wprintf(L"\nВведите диапазон звездной величины:\n");
                minVal = safe_get_double(L"Минимальное значение", -50.0, 50.0);
                maxVal = safe_get_double(L"Максимальное значение", minVal, 50.0);
                temp = SerchInDiapazone(ATL, SERCH_STAR_BY_STELLAR_MAGNITUDE, minVal, maxVal);
                break;
            }

            case 9: { // Класс черной дыры
                wprintf(L"\nВведите класс черной дыры: ");
                searchStr = get_wstring(50);
                temp = SerchInDiapazone(ATL, SERCH_BLACK_HOLE_BY_BLACK_HOLE_CLASS, searchStr);
                free(searchStr);
                break;
            }

            case 10: { // Класс туманности
                wprintf(L"\nВведите класс туманности: ");
                searchStr = get_wstring(100);
                temp = SerchInDiapazone(ATL, SERCH_NEBULA_BY_NEBULA_CLASS, searchStr);
                free(searchStr);
                break;
            }

            case 11: { // Частота пульсара
                wprintf(L"\nВведите диапазон частоты:\n");
                minVal = safe_get_double(L"Минимальная частота (Hz)", 0.0, DBL_MAX);
                maxVal = safe_get_double(L"Максимальная частота (Hz)", minVal, DBL_MAX);
                temp = SerchInDiapazone(ATL, SERCH_PULSAR_BY_PULSAR_FREQUENSY, minVal, maxVal);
                break;
            }

            case 12: { // Магнитуда пульсара
                wprintf(L"\nВведите диапазон магнитуды:\n");
                minVal = safe_get_double(L"Минимальная магнитуда", -50.0, 50.0);
                maxVal = safe_get_double(L"Максимальная магнитуда", minVal, 50.0);
                temp = SerchInDiapazone(ATL, SERCH_PULSAR_BY_STELLAR_MAGNITUDE, minVal, maxVal);
                break;
            }

            case 13: { // Звезды в галактике
                wprintf(L"\nВведите диапазон количества звезд:\n");
                minVal = safe_get_double(L"Минимальное количество", 0.0, DBL_MAX);
                maxVal = safe_get_double(L"Максимальное количество", minVal, DBL_MAX);
                temp = SerchInDiapazone(ATL, SERCH_GALLAXY_BY_COUNT_STAR, minVal, maxVal);
                break;
            }

            case 14: { // Звезды в скоплении
                wprintf(L"\nВведите диапазон количества звезд:\n");
                unsigned long min = safe_get_int(L"Минимальное количество", 0, INT_MAX);
                unsigned long max = safe_get_int(L"Максимальное количество", min, INT_MAX);
                temp = SerchInDiapazone(ATL, SERCH_STAR_CLASTER_BY_COUNT_STAR,
                    static_cast<double>(min), static_cast<double>(max));
                break;
            }
            }

            // Обработка результатов
            if (temp && temp->copiseti > 0) {
                print_table(temp);
                wprintf(L"\nНайдено объектов: %d\n", temp->copiseti);

                wprintf(L"\nСохранить результаты поиска? (1 - Да, 0 - Нет): ");
                if (safe_get_int(L"", 0, 1) == 1) {
                    wprintf(L"Введите имя файла: ");
                    filename = get_string(255);
                    if (!save_spase_atlas(temp, filename)) {
                        wprintf(L"Ошибка сохранения файла!\n");
                    }
                }
            }
            else if (temp == nullptr) {
                wprintf(L"\nОшибка при объявлении временного массива.!\n");
            }
            else {
                wprintf(L"\nОбъекты не найдены!\n");
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
            wprintf(L"\nВведите название файла для загрузки.\n");
            fflush(stdin);
            scanf_s("%99s", &filename, 100);
            if (!save_spase_atlas(ATL, filename)) {
                wprintf(L"Save failed!\n");
                deleteSpaseAtlas(ATL);
                ATL = nullptr;
            }
            break;
        case EXIT:
            wprintf(L"\nВы уверены что хотите покинуть программу?\nЕсли да, нажмите любую клавишу кроме 0.");
            if (!getchar()) continue;
            deleteSpaseAtlas(ATL);
            return;
            break;
        default:
            break;
        }

    }
}

