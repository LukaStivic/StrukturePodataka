#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define BUFFER_SIZE 20

struct stog;
typedef struct stog* pozicija;
typedef struct stog {
    int el;
    pozicija Next;
} stog;

int umetniElement(pozicija P, int noviEl);
int izbaciElement(pozicija P);
int racunajPostfix(pozicija P, char* fileName);

int main() {

    pozicija Head = (pozicija)malloc(sizeof(stog));
    Head->Next = NULL;

    int p;

    if ((p = racunajPostfix(Head, "postfix.txt")) != EXIT_FAILURE) {
        printf("Rezultat je %d\n", p);
    }
    else {
        printf("Greska u racunu!\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

int racunajPostfix(pozicija P, char* fileName) {

    int rezultat = 0;
    int noviBr, a, b;
    char s[BUFFER_SIZE];
    char* visak;

    FILE* fp = fopen(fileName, "r");
    if (!fp) {
        printf("File nije pravilno otvoren!\n");
        return EXIT_FAILURE;
    }

    while (fscanf(fp, "%s", s) != EOF) {
        if (isdigit(s[0])) {
            noviBr = strtol(s, &visak, 10);
            if (umetniElement(P, noviBr) != EXIT_SUCCESS) {
                printf("Broj nije pravilno unesen!\n");
                return EXIT_FAILURE;
            }
        }
        else {
            a = izbaciElement(P);
            if (a == EXIT_FAILURE) {
                printf("Broj nije pravilno ucitan!\n");
                return EXIT_FAILURE;
            }
            b = izbaciElement(P);
            if (b == EXIT_FAILURE) {
                printf("Broj nije pravilno ucitan!\n");
                return EXIT_FAILURE;
            }

            if (strcmp(s, "+") == 0) {
                rezultat = b + a;
            }
            else if (strcmp(s, "*") == 0) {
                rezultat = b * a;
            }
            else if (strcmp(s, "-") == 0) {
                rezultat = b - a;
            }
            else {
                printf("Znak nije moguce prepoznati!\n");
                return EXIT_FAILURE;
            }

            if (umetniElement(P, rezultat) != EXIT_SUCCESS) {
                printf("Broj nije pravilno unesen!\n");
                return EXIT_FAILURE;
            }
        }
    }

    fclose(fp);
    rezultat = P->Next->el;
    return rezultat;
}

int umetniElement(pozicija P, int noviEl) {
    pozicija t = (pozicija)malloc(sizeof(stog));

    t->Next = P->Next;
    P->Next = t;
    t->el = noviEl;
    return EXIT_SUCCESS;
}

int izbaciElement(pozicija P) {
    if (P->Next == NULL) {
        return EXIT_FAILURE;
    }

    pozicija t = P->Next;
    P->Next = t->Next;
    int izbEl = t->el;
    free(t);
    return izbEl;
}
