#pragma once


//Перечисление для удобной сортировки
enum SortType
{
	SORT_BY_TYPE = 100,
	SORT_BY_NAME = 101,
	SORT_BY_ASCENT = 102,
	SORT_BY_DISLINATION = 103,
	SORT_BY_RANGE = 104,
	SORT_BY_MASS = 105,
	SORT_STAR_BY_STAR_CLASS = 200,
	SORT_STAR_BY_STELLAR_MAGNITUDE = 201,
	SORT_BLACK_HOLE_BY_BLACK_HOLE_CLASS = 300,
	SORT_NEBULA_BY_NEBULA_CLASS = 400,
	SORT_PULSAR_BY_PULSAR_FREQUENSY = 500,
	SORT_PULSAR_BY_STELLAR_MAGNITUDE = 501,
	SORT_GALLAXY_BY_COUNT_STAR = 600,
	SORT_STAR_CLASTER_BY_COUNT_STAR = 700,
};

enum SerchType
{
	SERCH_BY_TYPE = 100,
	SERCH_BY_NAME = 101,
	SERCH_BY_ASCENT = 102,
	SERCH_BY_DISLINATION = 103,
	SERCH_BY_RANGE = 104,
	SERCH_BY_MASS = 105,
	SERCH_STAR_BY_STAR_CLASS = 200,
	SERCH_STAR_BY_STELLAR_MAGNITUDE = 201,
	SERCH_BLACK_HOLE_BY_BLACK_HOLE_CLASS = 300,
	SERCH_NEBULA_BY_NEBULA_CLASS = 400,
	SERCH_PULSAR_BY_PULSAR_FREQUENSY = 500,
	SERCH_PULSAR_BY_STELLAR_MAGNITUDE = 501,
	SERCH_GALLAXY_BY_COUNT_STAR = 600,
	SERCH_STAR_CLASTER_BY_COUNT_STAR = 700,
};

//strcmp() Для сравнения строк


static int compareByName(const void* uno, const void* duo) {
	return wcscmp(((ObjacteTipe*)(uno))->Objecte->name, ((ObjacteTipe*)(duo))->Objecte->name);
}

static int compareByType(const void* uno, const void* duo) {
	return ((((ObjacteTipe*)(uno))->type) - (((ObjacteTipe*)(duo))->type));
}

static int compereByAscent(const void* uno, const void* duo) {
	return (ascent_to_degrees(((ObjacteTipe*)(uno))->Objecte->Ascent) > ascent_to_degrees(((ObjacteTipe*)(duo))->Objecte->Ascent)) ? -1 : 1;
}

static int compereByDeclination(const void* uno, const void* duo) {
	return ((((ObjacteTipe*)(uno))->Objecte->declination) > (((ObjacteTipe*)(duo))->Objecte->declination)) ? -1 : 1;
}

static int compereByRange(const void* uno, const void* duo) {
	return ((((ObjacteTipe*)(uno))->Objecte->range) > (((ObjacteTipe*)(duo))->Objecte->range)) ? -1 : 1;
}

static int compereByMass(const void* uno, const void* duo) {
	return ((((ObjacteTipe*)(uno))->Objecte->mass) > (((ObjacteTipe*)(duo))->Objecte->mass)) ? -1 : 1;
}


// Сортировка звезд по классу
static int compareStarByClass(const void* a, const void* b) {
	const ObjacteTipe* objA = (const ObjacteTipe*)a;
	const ObjacteTipe* objB = (const ObjacteTipe*)b;

	if (objA->type != OBJ_STAR && objB->type != OBJ_STAR) return 0;
	if (objA->type != OBJ_STAR) return 1;
	if (objB->type != OBJ_STAR) return -1;

	const Star* starA = (const Star*)objA->Objecte;
	const Star* starB = (const Star*)objB->Objecte;
	return wcscmp(starA->starClass, starB->starClass);
}

// Сортировка звезд по звездной величине
static int compareStarByMagnitude(const void* a, const void* b) {
	const ObjacteTipe* objA = (const ObjacteTipe*)a;
	const ObjacteTipe* objB = (const ObjacteTipe*)b;

	if (objA->type != OBJ_STAR && objB->type != OBJ_STAR) return 0;
	if (objA->type != OBJ_STAR) return 1;
	if (objB->type != OBJ_STAR) return -1;

	const Star* starA = (const Star*)objA->Objecte;
	const Star* starB = (const Star*)objB->Objecte;
	return (starA->stellarMagnitude > starB->stellarMagnitude) ? 1 : -1;
}

// Сортировка черных дыр по классу
static int compareBlackHoleByClass(const void* a, const void* b) {
	const ObjacteTipe* objA = (const ObjacteTipe*)a;
	const ObjacteTipe* objB = (const ObjacteTipe*)b;

	if (objA->type != OBJ_BLACKHOLE && objB->type != OBJ_BLACKHOLE) return 0;
	if (objA->type != OBJ_BLACKHOLE) return 1;
	if (objB->type != OBJ_BLACKHOLE) return -1;

	const BlackHole* bhA = (BlackHole*)objA->Objecte;
	const BlackHole* bhB = (BlackHole*)objB->Objecte;
	return wcscmp(bhA->blackHoleClass, bhB->blackHoleClass);
}

// Сортировка туманностей по классу
static int compareNebulaByClass(const void* a, const void* b) {
	const ObjacteTipe* objA = (const ObjacteTipe*)a;
	const ObjacteTipe* objB = (const ObjacteTipe*)b;

	if (objA->type != OBJ_NEBULA && objB->type != OBJ_NEBULA) return 0;
	if (objA->type != OBJ_NEBULA) return 1;
	if (objB->type != OBJ_NEBULA) return -1;

	const Nebula* nebA = (Nebula*)objA->Objecte;
	const Nebula* nebB = (Nebula*)objB->Objecte;
	return wcscmp(nebA->nebulaClass, nebB->nebulaClass);
}

// Сортировка пульсаров по частоте
static int comparePulsarByFreq(const void* a, const void* b) {
	const ObjacteTipe* objA = (const ObjacteTipe*)a;
	const ObjacteTipe* objB = (const ObjacteTipe*)b;

	if (objA->type != OBJ_PULSAR && objB->type != OBJ_PULSAR) return 0;
	if (objA->type != OBJ_PULSAR) return 1;
	if (objB->type != OBJ_PULSAR) return -1;

	const Pulsar* pA = (Pulsar*)objA->Objecte;
	const Pulsar* pB = (Pulsar*)objB->Objecte;
	return (pA->pulsarFrequensy > pB->pulsarFrequensy) ? 1 : -1;
}

// Сортировка пульсаров по звездной величине
static int comparePulsarByMagnitude(const void* a, const void* b) {
	const ObjacteTipe* objA = (const ObjacteTipe*)a;
	const ObjacteTipe* objB = (const ObjacteTipe*)b;

	if (objA->type != OBJ_PULSAR && objB->type != OBJ_PULSAR) return 0;
	if (objA->type != OBJ_PULSAR) return 1;
	if (objB->type != OBJ_PULSAR) return -1;

	const Pulsar* pA = (Pulsar*)objA->Objecte;
	const Pulsar* pB = (Pulsar*)objB->Objecte;
	return (pA->stellarMagnitude > pB->stellarMagnitude) ? 1 : -1;
}

// Сортировка галактик по количеству звезд
static int compareGalaxyByStars(const void* a, const void* b) {
	const ObjacteTipe* objA = (const ObjacteTipe*)a;
	const ObjacteTipe* objB = (const ObjacteTipe*)b;

	if (objA->type != OBJ_GALAXY && objB->type != OBJ_GALAXY) return 0;
	if (objA->type != OBJ_GALAXY) return 1;
	if (objB->type != OBJ_GALAXY) return -1;

	const Galaxy* gA = (Galaxy*)objA->Objecte;
	const Galaxy* gB = (Galaxy*)objB->Objecte;
	return (gA->CountStar > gB->CountStar) ? 1 : -1;
}

// Сортировка скоплений по количеству звезд
static int compareClusterByStars(const void* a, const void* b) {
	const ObjacteTipe* objA = (const ObjacteTipe*)a;
	const ObjacteTipe* objB = (const ObjacteTipe*)b;

	if (objA->type != OBJ_STARCLASTER && objB->type != OBJ_STARCLASTER) return 0;
	if (objA->type != OBJ_STARCLASTER) return 1;
	if (objB->type != OBJ_STARCLASTER) return -1;

	const StarCluster* scA = (StarCluster*)objA->Objecte;
	const StarCluster* scB = (StarCluster*)objB->Objecte;
	return (scA->CountStar > scB->CountStar) ? 1 : -1;
}


void sortOfAtlass(SpaseAtlas* arr, SortType sortType) {
	switch (sortType)
	{
	case SORT_BY_TYPE:
		qsort(arr->unit, arr->copiseti, sizeof(ObjacteTipe), compareByType);
		break;
	case SORT_BY_NAME:
		qsort(arr->unit, arr->copiseti, sizeof(ObjacteTipe), compareByName);
		break;
	case SORT_BY_ASCENT:
		qsort(arr->unit, arr->copiseti, sizeof(ObjacteTipe), compereByAscent);
		break;
	case SORT_BY_DISLINATION:
		qsort(arr->unit, arr->copiseti, sizeof(ObjacteTipe), compereByDeclination);
		break;
	case SORT_BY_RANGE:
		qsort(arr->unit, arr->copiseti, sizeof(ObjacteTipe), compereByRange);
		break;
	case SORT_BY_MASS:
		qsort(arr->unit, arr->copiseti, sizeof(ObjacteTipe), compereByMass);
		break;
	case SORT_STAR_BY_STAR_CLASS:
		qsort(arr->unit, arr->copiseti, sizeof(ObjacteTipe), compareStarByClass);
		break;
	case SORT_STAR_BY_STELLAR_MAGNITUDE:
		qsort(arr->unit, arr->copiseti, sizeof(ObjacteTipe), compareStarByMagnitude);
		break;
	case SORT_BLACK_HOLE_BY_BLACK_HOLE_CLASS:
		qsort(arr->unit, arr->copiseti, sizeof(ObjacteTipe), compareBlackHoleByClass);
		break;
	case SORT_NEBULA_BY_NEBULA_CLASS:
		qsort(arr->unit, arr->copiseti, sizeof(ObjacteTipe), compareNebulaByClass);
		break;
	case SORT_PULSAR_BY_PULSAR_FREQUENSY:
		qsort(arr->unit, arr->copiseti, sizeof(ObjacteTipe), comparePulsarByFreq);
		break;
	case SORT_PULSAR_BY_STELLAR_MAGNITUDE:
		qsort(arr->unit, arr->copiseti, sizeof(ObjacteTipe), comparePulsarByMagnitude);
		break;
	case SORT_GALLAXY_BY_COUNT_STAR:
		qsort(arr->unit, arr->copiseti, sizeof(ObjacteTipe), compareGalaxyByStars);
		break;
	case SORT_STAR_CLASTER_BY_COUNT_STAR:
		qsort(arr->unit, arr->copiseti, sizeof(ObjacteTipe), compareClusterByStars);
		break;
	default:
		break;
	}
}

// Поиск по числовому диапазону
//Функция создает отдельный массив, заполненный значениями которые требуются пользователю
SpaseAtlas* SerchInDiapazone(SpaseAtlas* atl, SerchType serchType, double min, double max) {
	SpaseAtlas* result = createSpaseAtlas(atl->copiseti);
	if (!result) return NULL;

	for (int i = 0; i < atl->copiseti; i++) {
		ObjacteTipe* obj = &atl->unit[i];
		switch (serchType) {
		case SERCH_BY_ASCENT: {
			double ascent = ascent_to_degrees(obj->Objecte->Ascent);
			if (ascent >= min && ascent <= max) {
				push_Back(result, obj->type, obj->Objecte);
			}
			break;
		}
		case SERCH_BY_DISLINATION:
			if (obj->Objecte->declination >= min && obj->Objecte->declination <= max) {
				push_Back(result, obj->type, obj->Objecte);
			}
			break;
		case SERCH_BY_RANGE:
			if (obj->Objecte->range >= min && obj->Objecte->range <= max) {
				push_Back(result, obj->type, obj->Objecte);
			}
			break;
		case SERCH_BY_MASS:
			if (obj->Objecte->mass >= min && obj->Objecte->mass <= max) {
				push_Back(result, obj->type, obj->Objecte);
			}
			break;
		case SERCH_STAR_BY_STELLAR_MAGNITUDE:
			if (obj->type == OBJ_STAR) {//Проверка на тип структуры...
				Star* star = (Star*)obj->Objecte;
				if (star->stellarMagnitude >= min && star->stellarMagnitude <= max) {
					push_Back(result, obj->type, obj->Objecte);
				}
			}
			break;
		case SERCH_PULSAR_BY_PULSAR_FREQUENSY:
			if (obj->type == OBJ_PULSAR) {
				Pulsar* pulsar = (Pulsar*)obj->Objecte;
				if (pulsar->pulsarFrequensy >= min && pulsar->pulsarFrequensy <= max) {
					push_Back(result, obj->type, obj->Objecte);
				}
			}
			break;
		case SERCH_PULSAR_BY_STELLAR_MAGNITUDE:
			if (obj->type == OBJ_PULSAR) {
				Pulsar* pulsar = (Pulsar*)obj->Objecte;
				if (pulsar->stellarMagnitude >= min && pulsar->stellarMagnitude <= max) {
					push_Back(result, obj->type, obj->Objecte);
				}
			}
			break;
		case SERCH_GALLAXY_BY_COUNT_STAR:
			if (obj->type == OBJ_GALAXY) {
				Galaxy* galaxy = (Galaxy*)obj->Objecte;
				if (galaxy->CountStar >= min && galaxy->CountStar <= max) {
					push_Back(result, obj->type, obj->Objecte);
				}
			}
			break;
		case SERCH_STAR_CLASTER_BY_COUNT_STAR:
			if (obj->type == OBJ_STARCLASTER) {
				StarCluster* cluster = (StarCluster*)obj->Objecte;
				if (cluster->CountStar >= min && cluster->CountStar <= max) {
					push_Back(result, obj->type, obj->Objecte);
				}
			}
			break;
		default: break;
		}
	}
	return result;
}

// Поиск по строке
SpaseAtlas* SerchInDiapazone(SpaseAtlas* atl, SerchType serchType, const wchar_t* sign) {
	SpaseAtlas* result = createSpaseAtlas(atl->copiseti);
	if (!result) return NULL;

	for (int i = 0; i < atl->copiseti; i++) {
		ObjacteTipe* obj = &atl->unit[i];
		switch (serchType) {
		case SERCH_BY_NAME:
			if (wcscmp(obj->Objecte->name, sign) == 0) {
				push_Back(result, obj->type, obj->Objecte);
			}
			break;
		case SERCH_STAR_BY_STAR_CLASS:
			if (obj->type == OBJ_STAR) {
				Star* star = (Star*)obj->Objecte;
				if (wcscmp(star->starClass, sign) == 0) {
					push_Back(result, obj->type, obj->Objecte);
				}
			}
			break;
		case SERCH_BLACK_HOLE_BY_BLACK_HOLE_CLASS:
			if (obj->type == OBJ_BLACKHOLE) {
				BlackHole* bh = (BlackHole*)obj->Objecte;
				if (wcscmp(bh->blackHoleClass, sign) == 0) {
					push_Back(result, obj->type, obj->Objecte);
				}
			}
			break;
		case SERCH_NEBULA_BY_NEBULA_CLASS:
			if (obj->type == OBJ_NEBULA) {
				Nebula* nebula = (Nebula*)obj->Objecte;
				if (wcscmp(nebula->nebulaClass, sign) == 0) {
					push_Back(result, obj->type, obj->Objecte);
				}
			}
			break;
		default: break;
		}
	}
	return result;
}

SpaseAtlas* SerchInDiapazone(SpaseAtlas* atl, SerchType serchType, TypeOfObjecte TOO) {
	SpaseAtlas* result = createSpaseAtlas(atl->copiseti);
	if (!result) return NULL;
	for (int i = 0; i < atl->copiseti; i++) {
		ObjacteTipe* obj = &atl->unit[i];
		if (obj->type == TOO) {
			push_Back(result, obj->type, obj->Objecte);
		}
	}
	return result;
}