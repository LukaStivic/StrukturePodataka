#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ERROR_OF -1
#define BUFFER_SIZE 1024
#define MAX_BR_BODOVA 30

typedef struct {
	char ime[20];
	char prezime[20];
	int bodovi[2];
}student;

int count_rows(char* fileName);
void read_file(char* fileName, student* popisStudenata, int rows);
void print_students(student* popisStudenata, int rows);

/*
int openFile(char* fileName) {
	FILE* fp = NULL;
	fp = fopen(fileName, "r");
	if (fp == NULL) {
		printf("File se nije otvorio pravilno.");
		return ERROR_OF;
	}
	return 0;
}*/

int main() {

	char* fileName = "studenti.txt";
	student* popisStudenata;
	int rows = count_rows(fileName);
	popisStudenata = malloc(sizeof(student)*rows);

	read_file(fileName, popisStudenata, rows);
	print_students(popisStudenata, rows);

	free(popisStudenata);
	return 0;
}

int count_rows(char* fileName) {

	FILE* fp = NULL;
	char buffer[BUFFER_SIZE] = {0};
	int count = 0;

	fp = fopen(fileName, "r");
	if (fp == NULL) {
		printf("File se nije otvorio pravilno.");
		return ERROR_OF;
	}

	while (!feof(fp)) {
		fgets(buffer, BUFFER_SIZE, fp);
		++count;
	}

	fclose(fp);

	return count;
}

void read_file(char* fileName, student* popisStudenata, int rows) {
	FILE* fp = NULL;

	fp = fopen(fileName, "r");
	if (fp == NULL) {
		printf("File se nije otvorio pravilno.");
		return;
	}

	int i;

	for (i = 0; i < rows; i++) {
		fscanf(fp, "%s", popisStudenata[i].ime);
		fscanf(fp, "%s", popisStudenata[i].prezime);
		fscanf(fp, "%d", &popisStudenata[i].bodovi[0]);
		popisStudenata[i].bodovi[1] = popisStudenata[i].bodovi[0] / MAX_BR_BODOVA;
		popisStudenata[i].bodovi[1] *= 100;
	}

	fclose(fp);
}

void print_students(student* popisStudenata, int rows) {

	int i;

	for (i = 0; i < rows; i++) {
		printf("%s %s %d %d\n", popisStudenata[i].ime, popisStudenata[i].prezime, popisStudenata[i].bodovi[0], popisStudenata[i].bodovi[1]);
	}

}