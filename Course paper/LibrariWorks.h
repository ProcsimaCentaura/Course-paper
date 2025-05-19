#pragma once
#include "Header.h"



enum FieldsOfBooks
{
	base, name, autor, genre, year, pages
};

struct tipesort
{
	FieldsOfBooks field;
	int type;//По возрастанию или по убыванию 1/0
};


struct Library {
	Book* books;
	tipesort sort;
	int size;
	int count;
};
//Заголовки функций
void printLibrary(Library* library);
void removeBook(Library* library, int index);
void destroyLibrary(Library* library);
void sortLibrary(Library* library, FieldsOfBooks field, int type);
void searchBook(Library* library);
//Поиск
int searchByName(Library* library, const char* name);
int searchByAutor(Library* library, const char* autor);
int searchByGenre(Library* library, const char* genre);
int searchByYear(Library* library, int year);
int searchByPages(Library* library, int pages);
int searchById(Library* library, int id);
//Создание библиотеки
Library* createLibrary(int size);
void push_Back(Library* library, Book book);
void changeBook(Book& book);
//Сортировка
void sortLibrary(Library* library, FieldsOfBooks field, int type);
int compareByNameAsc(const void* a, const void* b);
int compareByNameDesc(const void* a, const void* b);	
int compareByAutorAsc(const void* a, const void* b);
int compareByAutorDesc(const void* a, const void* b);
int compareByGenreAsc(const void* a, const void* b);
int compareByGenreDesc(const void* a, const void* b);
int compareByYearAsc(const void* a, const void* b);
int compareByYearDesc(const void* a, const void* b);
int compareByPagesAsc(const void* a, const void* b);
int compareByPagesDesc(const void* a, const void* b);
int compareByIdAsc(const void* a, const void* b);
int compareByIdDesc(const void* a, const void* b);
void searchBook(Library* library);

//Функции:

//Функция создания библиотеки
Library* createLibrary(int size) {
	Library* library = (Library*)malloc(sizeof(Library));
	if (library == NULL) {
		printf("Memory allocation failed\n");
		return NULL;
	}
	library->books = (Book*)malloc(size * sizeof(Book));
	if (library->books == NULL) {
		printf("Memory allocation failed\n");
		free(library);
		return NULL;
	}
	library->sort.field = base;
	library->size = size;
	library->count = 0;
	return library;
}



//Функция добавления книги в библиотеку
void push_Back(Library* library, Book book) {
	if (library->count < library->size) {
		library->books[library->count] = book;
		library->count++;
	}
	//Eсли Count больше 3/4 от размера Size, то увеличиваем размер массива в 2 раза
	if (library->count > library->size * 3 / 4) {
		library->size *= 2;
		library->books = (Book*)realloc(library->books, library->size * sizeof(Book));
		if (library->books == NULL) {
			printf("Memory reallocation failed\n");
			free(library);
			return;
		}
	}
	else {
		printf("Library is full\n");
	}
}

//Функция удаления последней книги из библиотеки
void pop_Back(Library* library) {
	if (library->count > 0) {
		library->count--;
	}
	//Введем уменьшение динамического массива, если Count меньше 1/4 от размера Size
	if (library->count < library->size / 4) {
		library->size /= 2;
		library->books = (Book*)realloc(library->books, library->size * sizeof(Book));
		if (library->books == NULL) {
			printf("Memory reallocation failed\n");
			free(library);
			return;
		}
	}
	else {
		printf("Library is empty\n");
	}
}


//Функция получения книги по индексу
Book* get_Book(Library* library, int index) {
	if (index >= 0 && index < library->count) {
		return &library->books[index];
	}
	else {
		printf("Index out of bounds\n");
		return NULL;
	}
}

//Функция установки книги в библиотеке
void set_Book(Library* library, int index, Book book) {
	if (index >= 0 && index < library->count) {
		library->books[index] = book;
	}
	else {
		printf("Index out of bounds\n");
	}
}

//Функция удаления книги из библиотеки, если эта книга будет не в конце массива, то все книги после нее будут сдвинуты на одну позицию влево
void removeBook(Library* library, int index) {
	//Проверяем, существует ли такая библиотека?
	//Проверяем, как была отсортированна библиотека
	FieldsOfBooks field = library->sort.field;
	if (library->sort.field != FieldsOfBooks::base) {
		sortLibrary(library, FieldsOfBooks::base, library->sort.type);
	}
	if (library == NULL) {
		printf("Library is empty\n");
		return;
	}
	//Проверяем, существует ли такая книга?
	if (index < 0 || index >= library->count) {
		printf("Book not found\n");
		return;
	}
	//Удаляем книгу
	if (index >= 0 && index < library->count) {
		for (int i = index; i < library->count - 1; i++) {
			//Надо изменить id у книги, которая была на месте удаленной
			library->books[i] = library->books[i + 1];
			library->books[i].id = library->books[i].id - 1;
		}
		library->count--;
	}
	//Возвращаем исходную сортировку
	if (field != FieldsOfBooks::base) {
		sortLibrary(library, field, library->sort.type);
	}

	else {
		printf("Index out of bounds\n");
	}
	//Показываем новый массив книг
	printLibrary(library);
}


//Функция удаления библиотеки
void destroyLibrary(Library* library) {
	if (library != NULL) {
		free(library->books);
		free(library);
	}
}

//Функция вывода библиотеки
void printLibrary(Library* library) {
	if (library != NULL) {
		for (int i = 0; i < library->count; i++) {
			printf("Book %d: %s, %s, %s, %d, %d, %d\n", i + 1, library->books[i].name,
				library->books[i].author, library->books[i].genre,
				library->books[i].year, library->books[i].pages, library->books[i].id);
		}
	}
	else {
		printf("Library is empty\n");
	}
}





//Сравнение по имени
int compareByNameAsc(const void* a, const void* b) {
	return strcmp(((Book*)a)->name, ((Book*)b)->name);
}
int compareByNameDesc(const void* a, const void* b) {
	return strcmp(((Book*)b)->name, ((Book*)a)->name);
}
//Сравнение по автору
int compareByAutorAsc(const void* a, const void* b) {
	return strcmp(((Book*)a)->author, ((Book*)b)->author);
}
int compareByAutorDesc(const void* a, const void* b) {
	return strcmp(((Book*)b)->author, ((Book*)a)->author);
}
//Сравнение по жанру
int compareByGenreAsc(const void* a, const void* b) {
	return strcmp(((Book*)a)->genre, ((Book*)b)->genre);
}
int compareByGenreDesc(const void* a, const void* b) {
	return strcmp(((Book*)b)->genre, ((Book*)a)->genre);
}
//Сравнение по году
int compareByYearAsc(const void* a, const void* b) {
	return ((Book*)a)->year - ((Book*)b)->year;
}
int compareByYearDesc(const void* a, const void* b) {
	return ((Book*)b)->year - ((Book*)a)->year;
}
//Сравнение по количеству страниц
int compareByPagesAsc(const void* a, const void* b) {
	return ((Book*)a)->pages - ((Book*)b)->pages;
}
int compareByPagesDesc(const void* a, const void* b) {
	return ((Book*)b)->pages - ((Book*)a)->pages;
}
//Сравнение по id
int compareByIdAsc(const void* a, const void* b) {
	return ((Book*)a)->id - ((Book*)b)->id;
}
int compareByIdDesc(const void* a, const void* b) {
	return ((Book*)b)->id - ((Book*)a)->id;
}



//Сортировка библиотеки по разным полям
void sortLibrary(Library* library, FieldsOfBooks field, int type) {
	//Проверяем, существует ли такая библиотека?
	if (library == nullptr)
	{
		printf("Library is empty\n");
		return;
	}
	//Проверяем, отсортирована ли библиотека по этому полю
	if (library->sort.field == field && library->sort.type == type) {
		return;
	}

	library->sort.field = field;
	library->sort.type = type;
	switch (field) {
	case name:
		if (type == 1) {
			qsort(library->books, library->count, sizeof(Book), compareByNameAsc);
		}
		else {
			qsort(library->books, library->count, sizeof(Book), compareByNameDesc);
		}
		break;
	case autor:
		if (type == 1) {
			qsort(library->books, library->count, sizeof(Book), compareByAutorAsc);
		}
		else {
			qsort(library->books, library->count, sizeof(Book), compareByAutorDesc);
		}
		break;
	case genre:
		if (type == 1) {
			qsort(library->books, library->count, sizeof(Book), compareByGenreAsc);
		}
		else {
			qsort(library->books, library->count, sizeof(Book), compareByGenreDesc);
		}
		break;
	case year:
		if (type == 1) {
			qsort(library->books, library->count, sizeof(Book), compareByYearAsc);
		}
		else {
			qsort(library->books, library->count, sizeof(Book), compareByYearDesc);
		}
		break;
	case pages:
		if (type == 1) {
			qsort(library->books, library->count, sizeof(Book), compareByPagesAsc);
		}
		else {
			qsort(library->books, library->count, sizeof(Book), compareByPagesDesc);
		}
		break;
	default:
		//Если не указан тип сортировки, по умолчанию сортировка по id
		if (type == 1) {
			qsort(library->books, library->count, sizeof(Book), compareByIdAsc);
		}
		else {
			qsort(library->books, library->count, sizeof(Book), compareByIdDesc);
		}
		break;
	}
}



//Функции поиска по библиотеке, будет сначала сортировать библитеку(если она еще не отсортирована по этому типу) после чего проводить в ней бинарный поиск.
//Поиск по имени
int searchByName(Library* library, const char* name) {
	// Гарантируем сортировку в порядке возрастания
	sortLibrary(library, FieldsOfBooks::name, 1); // 1 - сортировка по возрастанию

	// Создаем ключ для поиска
	Book key = {};
	strcpy_s(key.name, name);

	// Выполняем бинарный поиск
	Book* result = (Book*)bsearch(&key, library->books, library->count, sizeof(Book), compareByNameAsc);

	// Возвращаем индекс найденной книги или -1, если не найдено
	if (result != NULL) {
		return result - library->books;
	}
	else {
		return -1;
	}
}
//Поиск по автору
int searchByAutor(Library* library, const char* autor) {
	// Гарантируем сортировку в порядке возрастания
	if (library->sort.field != FieldsOfBooks::autor) {
		sortLibrary(library, FieldsOfBooks::autor, 1);
	}

	Book key = {};
	strcpy_s(key.author, autor);
	Book* result = (Book*)bsearch(&key, library->books, library->count, sizeof(Book), compareByAutorAsc);
	if (result != NULL) {
		return result - library->books;
	}
	else {
		return -1;
	}
}


//Поиск по жанру
int searchByGenre(Library* library, const char* genre) {
	if (library->sort.field != FieldsOfBooks::genre) {
		sortLibrary(library, FieldsOfBooks::genre, 1);
	}
	Book key = {};
	strcpy_s(key.genre, genre);
	Book* result = (Book*)bsearch(&key, library->books, library->count, sizeof(Book), compareByGenreAsc);
	if (result != NULL) {
		return result - library->books;
	}
	else {
		return -1;
	}
}
//Поиск по году
int searchByYear(Library* library, int year) {
	if (library->sort.field != FieldsOfBooks::year) {
		sortLibrary(library, FieldsOfBooks::year, library->sort.type);
	}
	Book key;
	key.year = year;
	Book* result = (Book*)bsearch(&key, library->books, library->count, sizeof(Book), compareByYearAsc);
	if (result != NULL) {
		return result - library->books;
	}
	else {
		return -1;
	}
}

//Поиск по количеству страниц
int searchByPages(Library* library, int pages) {
	if (library->sort.field != FieldsOfBooks::pages) {
		sortLibrary(library, FieldsOfBooks::pages, library->sort.type);
	}
	Book key;
	key.pages = pages;
	Book* result = (Book*)bsearch(&key, library->books, library->count, sizeof(Book), compareByPagesAsc);
	if (result != NULL) {
		return result - library->books;
	}
	else {
		return -1;
	}
}

//Поиск по id
int searchById(Library* library, int id) {
	if (library->sort.field != FieldsOfBooks::base) {
		sortLibrary(library, FieldsOfBooks::base, library->sort.type);
	}
	Book key;
	key.id = id;
	Book* result = (Book*)bsearch(&key, library->books, library->count, sizeof(Book), compareByIdAsc);
	if (result != NULL) {
		return result - library->books;
	}
	else {
		return -1;
	}
}

//Меню поиска книги
void searchBook(Library* library) {
	int choice = 0;
	char name[50];
	char autor[50];
	char genre[50];
	int year;
	int pages;
	int id;
	int index;
	printf("Enter search criteria:\n");
	printf("1. Name\n");
	printf("2. Autor\n");
	printf("3. Genre\n");
	printf("4. Year\n");
	printf("5. Pages\n");
	printf("6. Id\n");
	scanf_s("%d", &choice);
	switch (choice) {
	case 1:
		printf("Enter name: ");
		rewind(stdin);
		scanf_s("%49[^\n]", name, sizeof(name));
		index = searchByName(library, name);
		if (index != -1) {
			printf("Book found: %s, %s, %s, %d, %d, %d\n", library->books[index].name,
				library->books[index].author, library->books[index].genre,
				library->books[index].year, library->books[index].pages, library->books[index].id);
		}
		else {
			printf("Book not found\n");
		}
		break;
	case 2:
		printf("Enter autor: ");
		rewind(stdin);
		scanf_s("%49[^\n]", autor, sizeof(autor));
		index = searchByAutor(library, autor);
		if (index != -1) {
			printf("Book found: %s, %s, %s, %d, %d, %d\n", library->books[index].name,
				library->books[index].author, library->books[index].genre,
				library->books[index].year, library->books[index].pages, library->books[index].id);
		}
		else {
			printf("Book not found\n");
		}
		break;
	case 3:
		printf("Enter genre: ");
		rewind(stdin);
		scanf_s("%49[^\n]", genre, sizeof(genre));
		index = searchByGenre(library, genre);
		if (index != -1) {
			printf("Book found: %s, %s, %s, %d, %d, %d\n", library->books[index].name,
				library->books[index].author, library->books[index].genre,
				library->books[index].year, library->books[index].pages, library->books[index].id);
		}
		else {
			printf("Book not found\n");
		}
		break;
	case 4:
		printf("Enter year: ");
		scanf_s("%d", &year);
		index = searchByYear(library, year);
		if (index != -1) {
			printf("Book found: %s, %s, %s, %d, %d, %d\n", library->books[index].name,
				library->books[index].author, library->books[index].genre,
				library->books[index].year, library->books[index].pages, library->books[index].id);
		}
		else {
			printf("Book not found\n");
		}
		break;
	case 5:
		printf("Enter pages: ");
		scanf_s("%d", &pages);
		index = searchByPages(library, pages);
		if (index != -1) {
			printf("Book found: %s, %s, %s, %d, %d, %d\n", library->books[index].name,
				library->books[index].author, library->books[index].genre,
				library->books[index].year, library->books[index].pages, library->books[index].id);
		}
		else {
			printf("Book not found\n");
		}
		break;
	case 6:
		printf("Enter id: ");
		scanf_s("%d", &id);
		index = searchById(library, id);
		if (index != -1) {
			printf("Book found: %s, %s, %s, %d, %d, %d\n", library->books[index].name,
				library->books[index].author, library->books[index].genre,
				library->books[index].year, library->books[index].pages, library->books[index].id);
		}
		else {
			printf("Book not found\n");
		}
		break;
	default:
		printf("Invalid choice\n");
		break;
	}
}