#pragma once
//Структура для массива, с помощью нее, можно хранить объект
struct ObjacteTipe {
    TypeOfObjecte type;//Перечисоение
    SpaseObgectDeterminant* Objecte;//Указатель на объект
};

struct SpaseAtlas {
    ObjacteTipe* unit;
    int size;
    int copiseti;
};

static void printTipe(const ObjacteTipe* tipe) {
    switch (tipe->type)
    {
    case OBJ_NULL:
        printf("неизвестный, но иннициированный объект");
            break;
    case OBJ_STAR:
        printf("звезда");
        break;
    case OBJ_BLACKHOLE:
        printf("черная дыра");
        break;
    case OBJ_NEBULA:
        printf("туманность");
        break;
    case OBJ_PULSAR:
        printf("пульсар");
        break;
    case OBJ_GALAXY:
        printf("галактика");
        break;
    case OBJ_STARCLASTER:
        printf("звездное скопление");
        break;
    default:
        printf("неизвестный неинициированный тип");
        break;
    }
}

SpaseAtlas* createSpaseAtlas(int size = 10) {
    SpaseAtlas* arr = (SpaseAtlas*)malloc(sizeof(SpaseAtlas));
    if (arr == NULL) {
        printf("Error SpaseAtlas isn't cteate");
        return NULL;
    }
    arr->unit = (ObjacteTipe*)malloc(sizeof(ObjacteTipe) * size);
    if (arr == NULL) {
        printf("Error memori allocation for SpaseAtlas failed");
        return NULL;
    }
    arr->size = size;
    arr->copiseti = 0;
    return arr;
}



void push_Back(SpaseAtlas* arr, TypeOfObjecte type, void* obj) {
    if (arr->copiseti >= arr->size) {
        arr->size *= 2;
        arr->unit = (ObjacteTipe*)realloc(arr->unit, arr->size * sizeof(ObjacteTipe));
    }
    arr->unit[arr->copiseti].type = type;
    arr->unit[arr->copiseti].Objecte = (SpaseObgectDeterminant*)obj;
    arr->copiseti++;
}

void push_Back(SpaseAtlas* arr, ObjacteTipe &objT) {
    if (arr->copiseti >= arr->size) {
        arr->size *= 2;
        arr->unit = (ObjacteTipe*)realloc(arr->unit, arr->size * sizeof(ObjacteTipe));
    }
    arr->unit[arr->copiseti] = objT;
    arr->copiseti++;
}

//Функция для удаления элемента из массива
void pop_Back(SpaseAtlas* arr) {
    if (arr->copiseti > 0) {
        int idx = arr->copiseti - 1;
        // Освобождаем память под объект в зависимости от типа
        switch (arr->unit[idx].type) {
        case OBJ_STAR:
            free((Star*)arr->unit[idx].Objecte);
            break;
        case OBJ_BLACKHOLE:
            free((BlackHole*)arr->unit[idx].Objecte);
            break;
        case OBJ_NEBULA:
            free((Nebula*)arr->unit[idx].Objecte);
            break;
        case OBJ_PULSAR:
            free((Pulsar*)arr->unit[idx].Objecte);
            break;
        case OBJ_GALAXY:
            free((Galaxy*)arr->unit[idx].Objecte);
            break;
        case OBJ_STARCLASTER:
            free((StarCluster*)arr->unit[idx].Objecte);
            break;
        default:
            free(arr->unit[idx].Objecte);
            break;
        }
        arr->unit[idx].Objecte = NULL;
        arr->copiseti--;
    }
}

void processArray(SpaseAtlas* arr) {
    for (size_t i = 0; i < arr->copiseti; i++) {
        SpaseObgectDeterminant* base = arr->unit[i].Objecte; // Чтоб не задолбался писать это все...
        wprintf(L"Name: %ls\n", base->name);

        switch (arr->unit[i].type) {
        case OBJ_STAR: {
            Star* star = (Star*)base;
            printf("Star magnitude: %.2f\n", star->stellarMagnitude);
            break;
        }
        case OBJ_BLACKHOLE: {
            BlackHole* bh = (BlackHole*)base;
            printf("BH class: %s\n", bh->blackHoleClass);
            break;
        }
        case OBJ_NEBULA: {
            Nebula* nebula = (Nebula*)base;
            printf("Nebula class: %s\n", nebula->nebulaClass);
            break;
        }
        case OBJ_PULSAR: {
            Pulsar* pulsar = (Pulsar*)base;
            printf("Pulsar Frequency: %.2f Hz\n", pulsar->pulsarFrequensy);
            printf("Stellar Magnitude: %.2f\n", pulsar->stellarMagnitude);
            break;
        }
        case OBJ_GALAXY: {
            Galaxy* galaxy = (Galaxy*)base;
            printf("Galaxy star count: %.0f\n", galaxy->CountStar);
            break;
        }
        case OBJ_STARCLASTER: {
            StarCluster* cluster = (StarCluster*)base;
            printf("Star cluster count: %lu\n", cluster->CountStar);
            break;
        }
        default:
            printf("Unknown object type\n");
            break;
        }
    }
}

//Удаление SpaseAtlass
void deleteSpaseAtlas(SpaseAtlas* arr) {
    if (!arr) return;
    // Освобождаем все объекты в массиве
    for (int i = 0; i < arr->copiseti; ++i) {
        if (!arr->unit[i].Objecte) continue;
        switch (arr->unit[i].type) {
        case OBJ_STAR:
            free((Star*)arr->unit[i].Objecte);
            break;
        case OBJ_BLACKHOLE:
            free((BlackHole*)arr->unit[i].Objecte);
            break;
        case OBJ_NEBULA:
            free((Nebula*)arr->unit[i].Objecte);
            break;
        case OBJ_PULSAR:
            free((Pulsar*)arr->unit[i].Objecte);
            break;
        case OBJ_GALAXY:
            free((Galaxy*)arr->unit[i].Objecte);
            break;
        case OBJ_STARCLASTER:
            free((StarCluster*)arr->unit[i].Objecte);
            break;
        default:
            free(arr->unit[i].Objecte);
            break;
        }
        arr->unit[i].Objecte = NULL;
    }
    // Освобождаем массив unit
    free(arr->unit);
    arr->unit = NULL;
    // Освобождаем сам атлас
    free(arr);
    arr = nullptr;
}


//Функции невозможно перегрузить по типу возвращаемого значения. По этому созданы
// Типы функций для каждого возможного элемента.
//Функция получения звезды по индексу
Star* get_star(SpaseAtlas* arr, int index) {
    if (index >= 0 && index < arr->copiseti) {
        if (arr->unit[index].type == OBJ_STAR) {
            return (Star*)arr->unit[index].Objecte;
        }
        else {
            printf("\nНеверный возвращаемый объект. Это не звезда.\n Это: " );
            printTipe(&arr->unit[index]);
            return (Star*)arr->unit[index].Objecte;//Вовращаем запрашиваемый объект отметив, что это не тот объект который хотел пользователь.
        }
    }
    else {
        printf("Index out of bounds\n");
        return NULL;
    }
}

//Функция получения черной дыры по индексу
BlackHole* get_blackHole(SpaseAtlas* arr, int index) {
    if (index >= 0 && index < arr->copiseti) {
        if (arr->unit[index].type == OBJ_BLACKHOLE) {
            return (BlackHole*)arr->unit[index].Objecte;
        }
        else {
            printf("\nНеверный возвращаемый объект. Это не черная дыра.\n Это: ");
            printTipe(&arr->unit[index]);
            return (BlackHole*)arr->unit[index].Objecte;//Вовращаем запрашиваемый объект отметив, что это не тот объект который хотел пользователь.
        }
    }
    else {
        printf("Index out of bounds\n");
        return NULL;
    }
}

Nebula* get_nebula(SpaseAtlas* arr, int index) {
    if (index >= 0 && index < arr->copiseti) {
        if (arr->unit[index].type == OBJ_NEBULA) {
            return (Nebula*)arr->unit[index].Objecte;
        }
        else {
            printf("\nНеверный возвращаемый объект. Это не туманность.\n Это: ");
            printTipe(&arr->unit[index]);
            return (Nebula*)arr->unit[index].Objecte;//Вовращаем запрашиваемый объект отметив, что это не тот объект который хотел пользователь.
        }
    }
    else {
        printf("Index out of bounds\n");
        return NULL;
    }
}

Pulsar* get_pulsar(SpaseAtlas* arr, int index) {
    if (index >= 0 && index < arr->copiseti) {
        if (arr->unit[index].type == OBJ_PULSAR) {
            return (Pulsar*)arr->unit[index].Objecte;
        }
        else {
            printf("\nНеверный возвращаемый объект. Это не пульсар.\n Это: ");
            printTipe(&arr->unit[index]);
            return (Pulsar*)arr->unit[index].Objecte;//Вовращаем запрашиваемый объект отметив, что это не тот объект который хотел пользователь.
        }
    }
    else {
        printf("Index out of bounds\n");
        return NULL;
    }
}

Galaxy* get_galaxy(SpaseAtlas* arr, int index) {
    if (index >= 0 && index < arr->copiseti) {
        if (arr->unit[index].type == OBJ_GALAXY) {
            return (Galaxy*)arr->unit[index].Objecte;
        }
        else {
            printf("\nНеверный возвращаемый объект. Это не галлактика.\n Это: ");
            printTipe(&arr->unit[index]);
            return (Galaxy*)arr->unit[index].Objecte;//Вовращаем запрашиваемый объект отметив, что это не тот объект который хотел пользователь.
        }
    }
    else {
        printf("Index out of bounds\n");
        return NULL;
    }
}

StarCluster* get_starCluster(SpaseAtlas* arr, int index) {
    if (index >= 0 && index < arr->copiseti) {
        if (arr->unit[index].type == OBJ_STARCLASTER) {
            return (StarCluster*)arr->unit[index].Objecte;
        }
        else {
            printf("\nНеверный тип возвращаемого объекта. Это не звездное скопление.\n Это: ");
            printTipe(&arr->unit[index]);
            return (StarCluster*)arr->unit[index].Objecte;//Вовращаем запрашиваемый объект отметив, что это не тот объект который хотел пользователь.
        }
    }
    else {
        printf("Index out of bounds\n");
        return NULL;
    }
}

SpaseObgectDeterminant* get_object(SpaseAtlas* arr, int index) {
    if (index >= 0 && index < arr->copiseti) {
        return (SpaseObgectDeterminant*)arr->unit[index].Objecte;
    }
    else {
        printf("Index out of bounds\n");
        return NULL;
    }
}

// Функция для удаления элемента по индексу со сдвигом
void removeAt(SpaseAtlas* arr, int index) {
    if (index < 0 || index >= arr->copiseti) {
        printf("Ошибка: Недопустимый индекс\n");
        return;
    }

    // Освобождаем память удаляемого объекта
    switch (arr->unit[index].type) {
    case OBJ_STAR:
        free((Star*)arr->unit[index].Objecte);
        break;
    case OBJ_BLACKHOLE:
        free((BlackHole*)arr->unit[index].Objecte);
        break;
    case OBJ_NEBULA:
        free((Nebula*)arr->unit[index].Objecte);
        break;
    case OBJ_PULSAR:
        free((Pulsar*)arr->unit[index].Objecte);
        break;
    case OBJ_GALAXY:
        free((Galaxy*)arr->unit[index].Objecte);
        break;
    case OBJ_STARCLASTER:
        free((StarCluster*)arr->unit[index].Objecte);
        break;
    default:
        free(arr->unit[index].Objecte);
        break;
    }

    // Сдвигаем элементы массива
    for (int i = index; i < arr->copiseti - 1; i++) {
        arr->unit[i] = arr->unit[i + 1];
    }

    // Уменьшаем счетчик элементов
    arr->copiseti--;

    // Обнуляем последний элемент после сдвига
    arr->unit[arr->copiseti].Objecte = NULL;
    arr->unit[arr->copiseti].type = OBJ_NULL;
}