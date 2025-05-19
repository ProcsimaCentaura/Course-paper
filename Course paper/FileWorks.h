#pragma once
#include "Header.h"
#include "LibrariWorks.h"


//Заголовки функций
void saveLibraryToFileWithCount(Library* library, const char* filename);
Library* loadLibraryFromFile(const char* filename);

//Функция загрузки библиотеки из файла она отправляется в конец файла проверяет id последней книги(последнее поле файла) создает библиотеку соответствующего размера, и загружает туда книги из файла
//Книги загружаются в порядке возрастания индекса
Library* loadLibraryFromFile(const char* filename) {
    FILE* file;
    fopen_s(&file, filename, "r");
    if (file == NULL) {
        printf("Error opening file for reading\n");
        return NULL;
    }

    int count = 0;
    if (fscanf_s(file, "%d", &count) != 1 || count <= 0) {
        printf("Invalid library size or file is empty\n");
        fclose(file);
        return NULL;
    }

    // Пропускаем перевод строки после числа count
    while (fgetc(file) != '\n' && !feof(file));

    Library* library = createLibrary(count+1);
    if (library == NULL) {
        printf("Failed to create library\n");
        fclose(file);
        return NULL;
    }

    for (int i = 0; i < count; i++) {
        Book book;
        if (fscanf_s(file, "%49[^;];%49[^;];%49[^;];%d;%d;%d\n",
            book.name, (unsigned)sizeof(book.name),
            book.author, (unsigned)sizeof(book.author),
            book.genre, (unsigned)sizeof(book.genre),
            &book.year, &book.pages, &book.id) == 6)
        {
            library->books[library->count++] = book;
        }
        else {
            printf("Error reading book data at line %d\n", i + 2);
            break;
        }
    }
    getID(count+1);
    fclose(file);
    printf("Library loaded from %s\n", filename);
    return library;
}

//Функция сохранения библиотеки в файл но, вводящая в начало файла количество книг в библиотеке(чтобы не считать их количество при загрузке из файла)
void saveLibraryToFileWithCount(Library* library, const char* filename) {
	if (library == NULL) {
		printf("Library is empty\n");
		return;
	}
	FILE* file;
	fopen_s(&file, filename, "w");
	if (file == NULL) {
		printf("Error opening file for writing\n");
		return;
	}
	fprintf(file, "%d\n", library->count);
	for (int i = 0; i < library->count; i++) {
		fprintf(file, "%s;%s;%s;%d;%d;%d\n", library->books[i].name,
			library->books[i].author, library->books[i].genre,
			library->books[i].year, library->books[i].pages, library->books[i].id);
	}
	fclose(file);
	printf("Library saved to %s\n", filename);
}