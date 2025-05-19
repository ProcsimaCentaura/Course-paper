#pragma once
#include "Header.h"



enum FieldsOfBooks
{
	base, name, autor, genre, year, pages
};

struct tipesort
{
	FieldsOfBooks field;
	int type;//�� ����������� ��� �� �������� 1/0
};


struct Library {
	Book* books;
	tipesort sort;
	int size;
	int count;
};
//��������� �������
void printLibrary(Library* library);
void removeBook(Library* library, int index);
void destroyLibrary(Library* library);
void sortLibrary(Library* library, FieldsOfBooks field, int type);
void searchBook(Library* library);
//�����
int searchByName(Library* library, const char* name);
int searchByAutor(Library* library, const char* autor);
int searchByGenre(Library* library, const char* genre);
int searchByYear(Library* library, int year);
int searchByPages(Library* library, int pages);
int searchById(Library* library, int id);
//�������� ����������
Library* createLibrary(int size);
void push_Back(Library* library, Book book);
void changeBook(Book& book);
//����������
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

//�������:

//������� �������� ����������
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



//������� ���������� ����� � ����������
void push_Back(Library* library, Book book) {
	if (library->count < library->size) {
		library->books[library->count] = book;
		library->count++;
	}
	//E��� Count ������ 3/4 �� ������� Size, �� ����������� ������ ������� � 2 ����
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

//������� �������� ��������� ����� �� ����������
void pop_Back(Library* library) {
	if (library->count > 0) {
		library->count--;
	}
	//������ ���������� ������������� �������, ���� Count ������ 1/4 �� ������� Size
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


//������� ��������� ����� �� �������
Book* get_Book(Library* library, int index) {
	if (index >= 0 && index < library->count) {
		return &library->books[index];
	}
	else {
		printf("Index out of bounds\n");
		return NULL;
	}
}

//������� ��������� ����� � ����������
void set_Book(Library* library, int index, Book book) {
	if (index >= 0 && index < library->count) {
		library->books[index] = book;
	}
	else {
		printf("Index out of bounds\n");
	}
}

//������� �������� ����� �� ����������, ���� ��� ����� ����� �� � ����� �������, �� ��� ����� ����� ��� ����� �������� �� ���� ������� �����
void removeBook(Library* library, int index) {
	//���������, ���������� �� ����� ����������?
	//���������, ��� ���� �������������� ����������
	FieldsOfBooks field = library->sort.field;
	if (library->sort.field != FieldsOfBooks::base) {
		sortLibrary(library, FieldsOfBooks::base, library->sort.type);
	}
	if (library == NULL) {
		printf("Library is empty\n");
		return;
	}
	//���������, ���������� �� ����� �����?
	if (index < 0 || index >= library->count) {
		printf("Book not found\n");
		return;
	}
	//������� �����
	if (index >= 0 && index < library->count) {
		for (int i = index; i < library->count - 1; i++) {
			//���� �������� id � �����, ������� ���� �� ����� ���������
			library->books[i] = library->books[i + 1];
			library->books[i].id = library->books[i].id - 1;
		}
		library->count--;
	}
	//���������� �������� ����������
	if (field != FieldsOfBooks::base) {
		sortLibrary(library, field, library->sort.type);
	}

	else {
		printf("Index out of bounds\n");
	}
	//���������� ����� ������ ����
	printLibrary(library);
}


//������� �������� ����������
void destroyLibrary(Library* library) {
	if (library != NULL) {
		free(library->books);
		free(library);
	}
}

//������� ������ ����������
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





//��������� �� �����
int compareByNameAsc(const void* a, const void* b) {
	return strcmp(((Book*)a)->name, ((Book*)b)->name);
}
int compareByNameDesc(const void* a, const void* b) {
	return strcmp(((Book*)b)->name, ((Book*)a)->name);
}
//��������� �� ������
int compareByAutorAsc(const void* a, const void* b) {
	return strcmp(((Book*)a)->author, ((Book*)b)->author);
}
int compareByAutorDesc(const void* a, const void* b) {
	return strcmp(((Book*)b)->author, ((Book*)a)->author);
}
//��������� �� �����
int compareByGenreAsc(const void* a, const void* b) {
	return strcmp(((Book*)a)->genre, ((Book*)b)->genre);
}
int compareByGenreDesc(const void* a, const void* b) {
	return strcmp(((Book*)b)->genre, ((Book*)a)->genre);
}
//��������� �� ����
int compareByYearAsc(const void* a, const void* b) {
	return ((Book*)a)->year - ((Book*)b)->year;
}
int compareByYearDesc(const void* a, const void* b) {
	return ((Book*)b)->year - ((Book*)a)->year;
}
//��������� �� ���������� �������
int compareByPagesAsc(const void* a, const void* b) {
	return ((Book*)a)->pages - ((Book*)b)->pages;
}
int compareByPagesDesc(const void* a, const void* b) {
	return ((Book*)b)->pages - ((Book*)a)->pages;
}
//��������� �� id
int compareByIdAsc(const void* a, const void* b) {
	return ((Book*)a)->id - ((Book*)b)->id;
}
int compareByIdDesc(const void* a, const void* b) {
	return ((Book*)b)->id - ((Book*)a)->id;
}



//���������� ���������� �� ������ �����
void sortLibrary(Library* library, FieldsOfBooks field, int type) {
	//���������, ���������� �� ����� ����������?
	if (library == nullptr)
	{
		printf("Library is empty\n");
		return;
	}
	//���������, ������������� �� ���������� �� ����� ����
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
		//���� �� ������ ��� ����������, �� ��������� ���������� �� id
		if (type == 1) {
			qsort(library->books, library->count, sizeof(Book), compareByIdAsc);
		}
		else {
			qsort(library->books, library->count, sizeof(Book), compareByIdDesc);
		}
		break;
	}
}



//������� ������ �� ����������, ����� ������� ����������� ���������(���� ��� ��� �� ������������� �� ����� ����) ����� ���� ��������� � ��� �������� �����.
//����� �� �����
int searchByName(Library* library, const char* name) {
	// ����������� ���������� � ������� �����������
	sortLibrary(library, FieldsOfBooks::name, 1); // 1 - ���������� �� �����������

	// ������� ���� ��� ������
	Book key = {};
	strcpy_s(key.name, name);

	// ��������� �������� �����
	Book* result = (Book*)bsearch(&key, library->books, library->count, sizeof(Book), compareByNameAsc);

	// ���������� ������ ��������� ����� ��� -1, ���� �� �������
	if (result != NULL) {
		return result - library->books;
	}
	else {
		return -1;
	}
}
//����� �� ������
int searchByAutor(Library* library, const char* autor) {
	// ����������� ���������� � ������� �����������
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


//����� �� �����
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
//����� �� ����
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

//����� �� ���������� �������
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

//����� �� id
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

//���� ������ �����
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