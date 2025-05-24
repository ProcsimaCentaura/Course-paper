#pragma once

//Это перечисление типов объектов
enum TypeOfObjecte {
	OBJ_NULL = -1,
	OBJ_STAR,
	OBJ_BLACKHOLE,
	OBJ_NEBULA,
	OBJ_PULSAR,
	OBJ_GALAXY,
	OBJ_STARCLASTER
};

//Как и хотела Дашка, для возвышения отдельная структура
struct directAscent {
	int hour, minutes;
	double seconds;
};

//Отдельная структура для информации, возможно потом потребуется
struct INFO {
	char* info;
	int size; 
};

//Это базовая структура, типа базового класса, нужна для того, чтобы работал полиморфизм
struct SpaseObgectDeterminant {
	wchar_t* name;//Указатель на название
	directAscent Ascent;//Прямое восхождение
	double declination; //Склонение
	double range;
	double mass;
	INFO info;
};

//Структура для звезды
struct Star{
	SpaseObgectDeterminant tipe;
	const wchar_t* starClass;//До 3 символов
	double stellarMagnitude;
};

//Структура для черной дыры
struct BlackHole{
	SpaseObgectDeterminant tipe;
	const wchar_t* blackHoleClass;//До 50 символов
};

//Структура для туманности
struct Nebula{
	SpaseObgectDeterminant tipe;
	const wchar_t* nebulaClass;//До 100 символов

};

//Структура для пульсара
struct Pulsar{
	SpaseObgectDeterminant tipe;
	double pulsarFrequensy;
	double stellarMagnitude;
};

//Структура для галлактики
struct Galaxy{
	SpaseObgectDeterminant tipe;
	double CountStar;
};

//Структура для звездного скопления
struct StarCluster {
	SpaseObgectDeterminant tipe;
	long unsigned CountStar;
};

//
//Функция для создания экземпляра типа Star по ссылке, для введеения в массив.
Star* createOfStar(const wchar_t* name, double range, double magnitude,
	const wchar_t* starClass, double declination, directAscent Ascent, double mass, INFO info = {NULL,NULL})
{
    Star* star = (Star*)malloc(sizeof(Star));
    if (!star) return NULL;

    // Выделяем память под имя (копируем всю строку + нуль-терминатор)
    size_t nameLen = wcslen(name) + 1;
    star->tipe.name = (wchar_t*)malloc(nameLen * sizeof(wchar_t));
    if (!star->tipe.name) {
        free(star);
        return NULL;
    }

    // Безопасное копирование строки
    #ifdef _MSC_VER
        wcsncpy_s(star->tipe.name, nameLen, name, _TRUNCATE);
    #else
        wcsncpy(star->tipe.name, name, nameLen - 1);
        star->tipe.name[nameLen - 1] = L'\0';
    #endif

    star->tipe.range = range;
    star->tipe.declination = declination;
    star->tipe.Ascent = Ascent;
    star->tipe.mass = mass;
	star->tipe.info = info;
    star->starClass = starClass;
    star->stellarMagnitude = magnitude;
    return star;
}

BlackHole* createOfBlackHole(const wchar_t* name, double range,
	const wchar_t* blackHoleClass, double declination, directAscent Ascent, double mass, INFO info = { NULL,NULL })
{
	BlackHole* blackHole = (BlackHole*)malloc(sizeof(BlackHole));

	size_t nameLen = wcslen(name) + 1;
	blackHole->tipe.name = (wchar_t*)malloc(nameLen * sizeof(wchar_t));
	if (!blackHole->tipe.name) {
		free(blackHole);
		return NULL;
	}

	// Безопасное копирование строки
#ifdef _MSC_VER
	wcsncpy_s(blackHole->tipe.name, nameLen, name, _TRUNCATE);
#else
	wcsncpy(star->tipe.name, name, nameLen - 1);
	blackHole->tipe.name[nameLen - 1] = L'\0';
#endif
	blackHole->tipe.range = range;
	blackHole->tipe.declination = declination;
	blackHole->tipe.Ascent = Ascent;
	blackHole->tipe.mass = mass;
	blackHole->tipe.info = info;
	blackHole->blackHoleClass = blackHoleClass;
	return blackHole;
}

Nebula* createOfNebula(const wchar_t* name, double range,
	const wchar_t* nebulaClass, double declination, directAscent Ascent, double mass, INFO info = { NULL,NULL })
{
	Nebula* nebula = (Nebula*)malloc(sizeof(Nebula));
	size_t nameLen = wcslen(name) + 1;
	nebula->tipe.name = (wchar_t*)malloc(nameLen * sizeof(wchar_t));
	if (!nebula->tipe.name) {
		free(nebula);
		return NULL;
	}

	// Безопасное копирование строки
#ifdef _MSC_VER
	wcsncpy_s(nebula->tipe.name, nameLen, name, _TRUNCATE);
#else
	wcsncpy(star->tipe.name, name, nameLen - 1);
	nebula->tipe.name[nameLen - 1] = L'\0';
#endif
	nebula->tipe.range = range;
	nebula->tipe.declination = declination;
	nebula->tipe.Ascent = Ascent;
	nebula->tipe.mass = mass;
	nebula->tipe.info = info;
	nebula->nebulaClass = nebulaClass;
	return nebula;
}

Pulsar* createOfPulsar(const wchar_t* name, double range,
	double declination, directAscent Ascent, double mass, double pulsarFrequensy, double stellarMagnitude, INFO info = { NULL,NULL })
{
	Pulsar* pulsar = (Pulsar*)malloc(sizeof(Pulsar));
	size_t nameLen = wcslen(name) + 1;
	pulsar->tipe.name = (wchar_t*)malloc(nameLen * sizeof(wchar_t));
	if (!pulsar->tipe.name) {
		free(pulsar);
		return NULL;
	}

	// Безопасное копирование строки
#ifdef _MSC_VER
	wcsncpy_s(pulsar->tipe.name, nameLen, name, _TRUNCATE);
#else
	wcsncpy(star->tipe.name, name, nameLen - 1);
	pulsar->tipe.name[nameLen - 1] = L'\0';
#endif
	pulsar->tipe.range = range;
	pulsar->tipe.declination = declination;
	pulsar->tipe.Ascent = Ascent;
	pulsar->tipe.mass = mass;
	pulsar->tipe.info = info;
	pulsar->pulsarFrequensy = pulsarFrequensy;
	pulsar->stellarMagnitude = stellarMagnitude;
	return pulsar;
}

Galaxy* createOfGalaxy(const wchar_t* name, double range,
	double declination, directAscent Ascent, double mass, double CountStar, INFO info = { NULL,NULL })
{
	Galaxy* galaxy = (Galaxy*)malloc(sizeof(Galaxy));
	size_t nameLen = wcslen(name) + 1;
	galaxy->tipe.name = (wchar_t*)malloc(nameLen * sizeof(wchar_t));
	if (!galaxy->tipe.name) {
		free(galaxy);
		return NULL;
	}

	// Безопасное копирование строки
#ifdef _MSC_VER
	wcsncpy_s(galaxy->tipe.name, nameLen, name, _TRUNCATE);
#else
	wcsncpy(star->tipe.name, name, nameLen - 1);
	galaxy->tipe.name[nameLen - 1] = L'\0';
#endif
	galaxy->tipe.range = range;
	galaxy->tipe.declination = declination;
	galaxy->tipe.Ascent = Ascent;
	galaxy->tipe.mass = mass;
	galaxy->tipe.info = info;
	galaxy->CountStar = CountStar;
	return galaxy;
}

StarCluster* createOfStarCluster(const wchar_t* name, double range,
	double declination, directAscent Ascent, double mass, long unsigned CountStar, INFO info = { NULL,NULL })
{
	StarCluster* starCluster = (StarCluster*)malloc(sizeof(StarCluster));
	size_t nameLen = wcslen(name) + 1;
	starCluster->tipe.name = (wchar_t*)malloc(nameLen * sizeof(wchar_t));
	if (!starCluster->tipe.name) {
		free(starCluster);
		return NULL;
	}

	// Безопасное копирование строки
#ifdef _MSC_VER
	wcsncpy_s(starCluster->tipe.name, nameLen, name, _TRUNCATE);
#else
	wcsncpy(star->tipe.name, name, nameLen - 1);
	starCluster->tipe.name[nameLen - 1] = L'\0';
#endif
	starCluster->tipe.range = range;
	starCluster->tipe.declination = declination;
	starCluster->tipe.Ascent = Ascent;
	starCluster->tipe.mass = mass;
	starCluster->tipe.info = info;
	starCluster->CountStar = CountStar;
	return starCluster;
}



