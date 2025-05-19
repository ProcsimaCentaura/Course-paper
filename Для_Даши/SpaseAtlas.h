#pragma once
//Структура для массива, с помощью нее, можно хранить объект
struct ObjacteTipe {
    TypeOfObjecte type;
    SpaseObgectDeterminant* Objecte;
};

struct SpaseAtlas {
    ObjacteTipe* unit;
    int size;
    int copiseti;
};

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
}

