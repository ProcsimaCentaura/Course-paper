#pragma once
#include "Header.h"
int id = 0;


struct Book {
	char name[50];
	char author[50];
	char genre[52];
	int year;
	int pages;
	int id;
};

void getstr(char* str, int intor) {
	char a;
	for (int i = 0; i < intor; i++)
	{
		a = getchar();
		if (a != '\n' && a != 0) str[i] = a;
		else {
			str[i] = 0;
			return;
		}
	}
}

//Функция заполнения полей структуры Book с помощью scanf

Book scanbook() {
	Book book;
	printf("Enter book name: ");
	rewind(stdin);
	scanf_s("%49[^\n]", book.name, sizeof(book.name));
	printf("Enter author name: ");
	rewind(stdin);
	scanf_s("%49[^\n]", book.author, sizeof(book.author));
	printf("Enter genre: ");
	getstr(book.genre, 49);
	rewind(stdin);
	scanf_s("%49[^\n]", book.genre, sizeof(book.genre));
	printf("Enter year: ");
	scanf_s("%d", &book.year);
	printf("Enter number of pages: ");
	scanf_s("%d", &book.pages);
	book.id = id++;
	return book;
}
//Изменение полей книги
void changeBook(Book& book) {
	printf("Enter book name: ");
	rewind(stdin);
	scanf_s("%49[^\n]", book.name, sizeof(book.name));
	printf("Enter author name: ");
	rewind(stdin);
	scanf_s("%49[^\n]", book.author, sizeof(book.author));
	printf("Enter genre: ");
	getstr(book.genre, 49);
	rewind(stdin);
	scanf_s("%49[^\n]", book.genre, sizeof(book.genre));
	printf("Enter year: ");
	scanf_s("%d", &book.year);
	printf("Enter number of pages: ");
	scanf_s("%d", &book.pages);
}

void getID(int _id) {
	id = _id;
}