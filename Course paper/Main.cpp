//Курсовая работа, СУБД(система управления базой данных)
//Заголовочные файлы

#include "Header.h"
#include "LibrariWorks.h"
#include "FileWorks.h"



//В main будет меню. Сначала будет просьба ввести файл из которого будет загружаться библиотека, затем будет меню с выбором действий над библиотекой(добавление книги, удаление книги, изменение книги, сортировка книг, поиск книги по автору и т.д.)
//1 Открыть файл
//2 Загрузить библиотеку из файла
//3 Сохранить библиотеку в файл
//4 Добавить книгу в библиотеку
//5 Удалить книгу из библиотеки
//6 Изменить книгу в библиотеке
//7 Сортировать библиотеку
//8 Поиск книги в библиотеке
//9 Вывести библиотеку на экран
//10 Выход из программы
int main() {
	//Русская раскладка
	system("chcp 1251");
	Library* librari_byFile = NULL;
	char filename[100];
	//Меню с 10 вариантами
	int choice = 12, flag = 1;
	int coutn = 0;
	printf("menu:\n");
	printf("1. Load library from file\n");
	printf("2. Save library to file\n");
	printf("3. Add book to library\n");
	printf("4. Remove book from library\n");
	printf("5. Change book in library\n");
	printf("6. Sort library\n");
	printf("7. Search book in library\n");
	printf("8. Print library\n");;
	printf("9. Exit\n");
	while (flag)
	{
		fflush(stdin);
		printf("Enter your choice: ");
		rewind(stdin);
		scanf_s("%d", &choice);
		if (coutn++ == 10) { 
			coutn = 0;
			system("cls"); }
		switch (choice)
		{
		case 1:
			printf("Enter the name of the file to load the library: ");
			rewind(stdin);
			scanf_s("%99s", filename, sizeof(filename));
			librari_byFile = loadLibraryFromFile(filename);
			if (librari_byFile == NULL) {
				printf("Error loading library from file\n");
				continue;
			}
			//Очищаем консоль
			system("cls");
			break;
		case 2:
			printf("Enter the name of the file to save the library: ");
			rewind(stdin);
			scanf_s("%99s", filename, sizeof(filename));
			saveLibraryToFileWithCount(librari_byFile, filename);
			break;
		case 3:
			push_Back(librari_byFile, scanbook());
			break;
		case 4:
			int index;
			printf("Enter the index of the book to remove: ");
			scanf_s("%d", &index);
			removeBook(librari_byFile, index);
			break;
		case 5:
			int index2;
			printf("Enter the index of the book to change: ");
			scanf_s("%d", &index2);
			changeBook(librari_byFile->books[index2]);
			break;
		case 6:
			int field, type;
			printf("Enter the field to sort by (0 - name, 1 - author, 2 - genre, 3 - year, 4 - pages): ");
			scanf_s("%d", &field);
			printf("Enter the type of sorting (0 - ascending, 1 - descending): ");
			scanf_s("%d", &type);
			sortLibrary(librari_byFile, (FieldsOfBooks)field, type);
			break;
		case 7:
			searchBook(librari_byFile);
			break;
		case 8:
			printLibrary(librari_byFile);
			break;
		case 9:
			destroyLibrary(librari_byFile);
			printf("Library destroyed\n");
			librari_byFile = NULL;
			flag = 0;
			break;
		default:
			printf("menu:\n");
			printf("1. Load library from file\n");
			printf("2. Save library to file\n");
			printf("3. Add book to library\n");
			printf("4. Remove book from library\n");
			printf("5. Change book in library\n");
			printf("6. Sort library\n");
			printf("7. Search book in library\n");
			printf("8. Print library\n");;
			printf("9. Exit\n");
			break;
		}
	}
}