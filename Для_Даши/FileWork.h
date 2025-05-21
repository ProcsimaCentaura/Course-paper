#pragma once
// Вспомогательные функции для работы со строками
static void write_wstring(const wchar_t* str, FILE* fp) {
    size_t len = wcslen(str);
    fwrite(&len, sizeof(size_t), 1, fp);
    fwrite(str, sizeof(wchar_t), len, fp);
}

static wchar_t* read_wstring(FILE* fp) {
    size_t len;
    fread(&len, sizeof(size_t), 1, fp);
    wchar_t* str = (wchar_t*)malloc((len + 1) * sizeof(wchar_t));
    fread(str, sizeof(wchar_t), len, fp);
    str[len] = L'\0';
    return str;
}

// Функции для работы с базовой структурой
static void save_spase_object(const SpaseObgectDeterminant* obj, FILE* fp) {
    write_wstring(obj->name, fp);
    fwrite(&obj->Ascent, sizeof(struct directAscent), 1, fp);
    fwrite(&obj->declination, sizeof(double), 1, fp);
    fwrite(&obj->range, sizeof(double), 1, fp);
    fwrite(&obj->mass, sizeof(double), 1, fp);

    // Сохранение INFO
    fwrite(&obj->info.size, sizeof(int), 1, fp);
    if (obj->info.size > 0) {
        fwrite(obj->info.info, sizeof(char), obj->info.size, fp);
    }
}

static void load_spase_object(SpaseObgectDeterminant* obj, FILE* fp) {
    obj->name = read_wstring(fp);
    fread(&obj->Ascent, sizeof(struct directAscent), 1, fp);
    fread(&obj->declination, sizeof(double), 1, fp);
    fread(&obj->range, sizeof(double), 1, fp);
    fread(&obj->mass, sizeof(double), 1, fp);

    // Загрузка INFO^^ Здесь крылась мощная ошибка, я пока не проверял, но тем не менее.
    fread(&obj->info.size, sizeof(int), 1, fp);
    if (obj->info.size > 0) {
        obj->info.info = (char*)malloc(obj->info.size);
        fread(obj->info.info, sizeof(char), obj->info.size, fp);
    }
}

// Функции для конкретных типов объектов
inline static void save_star(const Star* obj, FILE* fp) {
    save_spase_object(&obj->tipe, fp);
    write_wstring(obj->starClass, fp);
    fwrite(&obj->stellarMagnitude, sizeof(double), 1, fp);
}


inline static void save_blackhole(const BlackHole* obj, FILE* fp) {
    save_spase_object(&obj->tipe, fp);
    write_wstring(obj->blackHoleClass, fp);
}

inline static void save_nebula(const Nebula* obj, FILE* fp) {
    save_spase_object(&obj->tipe, fp);
    write_wstring(obj->nebulaClass, fp);
}

inline static void save_pulsar(const Pulsar* obj, FILE* fp) {
    save_spase_object(&obj->tipe, fp);
    fwrite(&obj->pulsarFrequensy, sizeof(double), 1, fp);
    fwrite(&obj->stellarMagnitude, sizeof(double), 1, fp);
}

void save_galaxy(const Galaxy* obj, FILE* fp) {
    save_spase_object(&obj->tipe, fp);
    fwrite(&obj->CountStar, sizeof(double), 1, fp);
}

inline static void save_starcluster(const StarCluster* obj, FILE* fp) {
    save_spase_object(&obj->tipe, fp);
    fwrite(&obj->CountStar, sizeof(double), 1, fp);
}






inline static Star* load_star(FILE* fp) {
    Star* obj = (Star*)malloc(sizeof(Star));
    load_spase_object(&obj->tipe, fp);
    obj->starClass = read_wstring(fp);
    fread(&obj->stellarMagnitude, sizeof(double), 1, fp);
    return obj;
}

inline static BlackHole* load_blackHole(FILE* fp) {
    BlackHole* obj = (BlackHole*)malloc(sizeof(BlackHole));
    load_spase_object(&obj->tipe, fp);
    obj->blackHoleClass = read_wstring(fp);
    return obj;
}

inline static Nebula* load_nebula(FILE* fp) {
    Nebula* obj = (Nebula*)malloc(sizeof(Nebula));
    load_spase_object(&obj->tipe, fp);
    obj->nebulaClass = read_wstring(fp);
    return obj;
}

inline static Pulsar* load_pulsar(FILE* fp) {
    Pulsar* obj = (Pulsar*)malloc(sizeof(Pulsar));
    load_spase_object(&obj->tipe, fp);
    fread(&obj->pulsarFrequensy, sizeof(double), 1, fp);
    fread(&obj->stellarMagnitude, sizeof(double), 1, fp);
    return obj;
}

inline static Galaxy* load_galaxy(FILE* fp) {
    Galaxy* obj = (Galaxy*)malloc(sizeof(Galaxy));
    load_spase_object(&obj->tipe, fp);
    fread(&obj->CountStar, sizeof(double), 1, fp);
    return obj;
}

inline static StarCluster* load_starcluster(FILE* fp) {
    StarCluster* obj = (StarCluster*)malloc(sizeof(StarCluster));
    load_spase_object(&obj->tipe, fp);
    fread(&obj->CountStar, sizeof(double), 1, fp);
    return obj;
}

// Основные функции работы с атласом
int save_spase_atlas(const SpaseAtlas* atlas, const char* filename) {
    FILE* fp;
    fopen_s(&fp, filename, "wb");
    if (!fp) return 0;

    // Запись заголовка
    const char header[8] = "SPASEAT";
    fwrite(header, sizeof(char), 7, fp);

    // Запись основных данных
    fwrite(&atlas->size, sizeof(int), 1, fp);
    fwrite(&atlas->copiseti, sizeof(int), 1, fp);

    for (int i = 0; i < atlas->copiseti; i++) {
        ObjacteTipe* item = &atlas->unit[i];
        fwrite(&item->type, sizeof(TypeOfObjecte), 1, fp);

        switch (item->type) {
        case OBJ_STAR:
            save_star((Star*)item->Objecte, fp);
            break;
        case OBJ_BLACKHOLE:
            save_blackhole((BlackHole*)item->Objecte, fp);
            break;
        case OBJ_NEBULA:
            save_nebula((Nebula*)item->Objecte, fp);
            break;
        case OBJ_PULSAR:
            save_pulsar((Pulsar*)item->Objecte, fp);
            break;
        case OBJ_GALAXY:
            save_galaxy((Galaxy*)item->Objecte, fp);
            break;
        case OBJ_STARCLASTER:
            save_starcluster((StarCluster*)item->Objecte, fp);
            break;
        default:
            break;
        }
    }

    fclose(fp);
    return 1;
}

SpaseAtlas* load_spase_atlas(const char* filename) {
    FILE* fp;
    fopen_s(&fp, filename, "rb");
    if (!fp) return nullptr;

    // Проверка заголовка
    char header[8] = { 0 };
    fread(header, sizeof(char), 7, fp);
    if (memcmp(header, "SPASEAT", 7) != 0) {
        fclose(fp);
        return nullptr;
    }
    //Не переписать, так как в
    SpaseAtlas* atlas = (SpaseAtlas*)malloc(sizeof(SpaseAtlas));
    fread(&atlas->size, sizeof(int), 1, fp);
    fread(&atlas->copiseti, sizeof(int), 1, fp);

    atlas->unit = (ObjacteTipe*)malloc(atlas->size * sizeof(ObjacteTipe));

    for (int i = 0; i < atlas->copiseti; i++) {
        fread(&atlas->unit[i].type, sizeof(TypeOfObjecte), 1, fp);

        switch (atlas->unit[i].type) {
        case OBJ_STAR:
            atlas->unit[i].Objecte = (SpaseObgectDeterminant*)load_star(fp);
            break;
        case OBJ_BLACKHOLE:
            atlas->unit[i].Objecte = (SpaseObgectDeterminant*)load_blackHole(fp);
            break;
        case OBJ_NEBULA:
            atlas->unit[i].Objecte = (SpaseObgectDeterminant*)load_nebula(fp);
            break;
        case OBJ_PULSAR:
            atlas->unit[i].Objecte = (SpaseObgectDeterminant*)load_pulsar(fp);
            break;
        case OBJ_GALAXY:
            atlas->unit[i].Objecte = (SpaseObgectDeterminant*)load_galaxy(fp);
            break;
        case OBJ_STARCLASTER:
            atlas->unit[i].Objecte = (SpaseObgectDeterminant*)load_starcluster(fp);
            break;
        default:
            atlas->unit[i].Objecte = NULL;
            break;
        }
    }

    fclose(fp);
    return atlas;
}