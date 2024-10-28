#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_IME 20
#define MAX_PREZIME 20

typedef struct osoba{
	char ime[MAX_IME];
	char prezime[MAX_PREZIME];
	int godinaRodenja;
	struct osoba* Next;
}osoba;


int umetniIspred(char* uIme, char* uPrezime, int uGodina, osoba* pozicija);
void ispisi(osoba* pozicija);
int umetniKraj(char* uIme, char* uPrezime, int uGodina, osoba* pozicija);
osoba* pronadiPrezime(char* pPrezime, osoba* pozicija);
int brisiElement(char* bPrezime, osoba* pozicija);

int main() {

	osoba* Head;
	Head = (osoba*)malloc(sizeof(osoba));
	Head->Next = NULL;

	if (umetniIspred("Ivo", "Ivic", 2000, Head) == 0)
		printf("Dodavanje je uspjesno!\n");
	if (umetniIspred("Anita", "Antic", 2002, Head) == 0)
		printf("Dodavanje je uspjesno!\n");
	if (umetniKraj("Josip", "Josipovic", 1999, Head) == 0)
		printf("Dodavanje je uspjesno!\n");
	ispisi(Head->Next);
	if (brisiElement("Antic", Head) == 0)
		printf("Brisanje je uspjesno!");
	ispisi(Head->Next);


	return 0;
}

int umetniIspred(char* uIme, char* uPrezime, int uGodina, osoba* pozicija) {
	osoba* p = (osoba*)malloc(sizeof(osoba));

	snprintf(p->ime, sizeof(p->ime), "%s", uIme);
	snprintf(p->prezime, sizeof(p->prezime), "%s",  uPrezime);
	p->godinaRodenja = uGodina;
	p->Next = pozicija->Next;
	pozicija->Next = p;

	return 0;
}

void ispisi(osoba* pozicija) {
	while (pozicija) {
		printf("Ime: %s\n", pozicija->ime);
		printf("Prezime: %s\n", pozicija->prezime);
		printf("Godina Rodjenja: %d\n", pozicija->godinaRodenja);
		printf("~~~~~~~~~~~~~~~~~~~~\n");
		pozicija = pozicija->Next;
	}
}

int umetniKraj(char* uIme, char* uPrezime, int uGodina, osoba* pozicija) {
	osoba* p = (osoba*)malloc(sizeof(osoba));
	osoba* t = (osoba*)malloc(sizeof(osoba));

	snprintf(p->ime, sizeof(p->ime), "%s", uIme);
	snprintf(p->prezime, sizeof(p->prezime), "%s", uPrezime);
	p->godinaRodenja = uGodina;
	p->Next = NULL;
	t = pozicija;
	while (t->Next != NULL) {
		t = t->Next;
	}
	t->Next = p;
	free(t);
	return 0;
}

osoba* pronadiPrezime(char* pPrezime, osoba* pozicija) {
	while (pozicija!=NULL) {
		if (strcmp(pozicija->prezime, pPrezime) == 0) {
			return pozicija;
		}
	}

	return NULL;
}

int brisiElement(char* pPrezime, osoba* pozicija) {
	osoba* p = pronadiPrezime(pPrezime, pozicija);
	
	if (p == NULL)
		return 0;

	osoba* prosli = pozicija;
	while (prosli->Next != p) {
		prosli = prosli->Next;
	}

	prosli->Next = p->Next;
	free(p);

	return 0;
}