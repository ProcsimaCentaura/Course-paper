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

/*int compereByDeclination(const void* uno, const void* duo) {
	return ((((ObjacteTipe*)(uno))->Objecte->declination) - (((ObjacteTipe*)(duo))->Objecte->declination));
}*/
//Другие типы сортировки более сложные, займусь ими позже...

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
		break;
	case SORT_STAR_BY_STELLAR_MAGNITUDE:
		break;
	case SORT_BLACK_HOLE_BY_BLACK_HOLE_CLASS:
		break;
	case SORT_NEBULA_BY_NEBULA_CLASS:
		break;
	case SORT_PULSAR_BY_PULSAR_FREQUENSY:
		break;
	case SORT_PULSAR_BY_STELLAR_MAGNITUDE:
		break;
	case SORT_GALLAXY_BY_COUNT_STAR:
		break;
	case SORT_STAR_CLASTER_BY_COUNT_STAR:
		break;
	default:
		break;
	}
}

//Поиск по диапазону значений.
/*SpaseAtlas* SerchInDiapazone(SpaseAtlas atl, SerchType serchType,
	double min, double max) 
{
	switch (serchType)
	{
	case SERCH_BY_ASCENT:
		break;
	case SERCH_BY_DISLINATION:
		break;
	case SERCH_BY_RANGE:
		break;
	case SERCH_BY_MASS:
		break;
	case SERCH_STAR_BY_STELLAR_MAGNITUDE:
		break;
	case SERCH_NEBULA_BY_NEBULA_CLASS:
		break;
	case SERCH_PULSAR_BY_PULSAR_FREQUENSY:
		break;
	case SERCH_PULSAR_BY_STELLAR_MAGNITUDE:
		break;
	case SERCH_GALLAXY_BY_COUNT_STAR:
		break;
	case SERCH_STAR_CLASTER_BY_COUNT_STAR:
		break;
	default:
		break;
	}
}

SpaseAtlas* SerchInDiapazone(SpaseAtlas atl, SerchType serchType,
	const wchar_t* sign)
{
	switch (serchType)
	{
	case SERCH_BY_NAME:
		break;
	case SERCH_STAR_BY_STAR_CLASS:
		break;
	case SERCH_BLACK_HOLE_BY_BLACK_HOLE_CLASS:
		break;
	case SERCH_NEBULA_BY_NEBULA_CLASS:
		break;
	default:
		break;
	}
}*/

//SpaseAtlas* SerchInDiapazone(SpaseAtlas atl, SerchType serchType,
//	TypeOfObjecte* type)
//{
//	
//
//}