#pragma once
#include "FileWorks.h"
//������� �������� ���������� �� ����� ��� ������������ � ����� ����� ��������� id ��������� �����(��������� ���� �����) ������� ���������� ���������������� �������, � ��������� ���� ����� �� �����
//����� ����������� � ������� ����������� �������
Library* loadLibraryFromFile(const char* filename) {
	FILE* file;
	fopen_s(&file, filename, "r");
	if (file == NULL) {
		printf("Error opening file for reading\n");
		return NULL;
	}

	// ���������� ���������� ����� � ����� (���������� ����)
	int count = 0;
	if (fscanf_s(file, "%d", &count) != 1 || count <= 0) {
		printf("Invalid library size or file is empty\n");
		fclose(file);
		return NULL;
	}

	Library* libreary_byFile = NULL;

	// ������� ���������� ���������������� �������
	libreary_byFile = createLibrary(count);

	// ������������ � ������ �����
	rewind(file);

	// ��������� ������ �� �����
	for (int i = 0; i < count; i++) {
		Book book;
		if (fscanf_s(file, "%49[^;];%49[^;];%49[^;];%d;%d;%d\n",
			book.name, book.author, book.genre,
			&book.year, &book.pages, &book.id) == 6) {
			libreary_byFile->books[libreary_byFile->count++] = book;
		}
		else {
			printf("Error reading book data at line %d\n", i + 2);
			break;
		}
	}

	fclose(file);
	printf("Library loaded from %s\n", filename);
	return libreary_byFile;
}

//������� ���������� ���������� � ���� ��, �������� � ������ ����� ���������� ���� � ����������(����� �� ������� �� ���������� ��� �������� �� �����)
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