#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ERROR_OF -1;
#define BUFFER_SIZE 1024;

typedef struct {
	char ime[20];
	char prezime[20];
	int bodovi[3];
}student;

int count_rows(char* filename);

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

	


	printf("Hello world!\n");
	return 0;
}

int count_rows(char* filename) {

	FILE* fp = NULL;
	char* buffer[BUFFER_SIZE] = { 0 };
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

	return 0;
}