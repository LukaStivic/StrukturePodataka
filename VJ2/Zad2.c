#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_IME 20
#define MAX_PREZIME 20

typedef struct {
	char ime[MAX_IME];
	char prezime[MAX_PREZIME];
	int godinaRodenja;
	osoba* Next;
}osoba;

int umetniIspred(char uIme, char uPrezime, int uGodina, osoba* pozicija);
void ispisi(osoba* pozicija);
int umetniKraj(char uIme, char uPrezime, int uGodina, osoba* pozicija);
//osoba* pronadiPrezime();
//int brisiElement();
 
int main() {

	osoba* Head;
	Head = (osoba*)malloc(sizeof(osoba));
	Head->Next = NULL;

	if (umetniIspred("Ivo", "Ivic", 2000, Head) == 0)
		printf("Dodavanje je uspješno!\n");
	if (umetniIspred("Anita", "Antic", 2002, Head) == 0)
		printf("Dodavanje je uspješno!\n");
	if (umetniKraj("Josip", "Josipovic", 1999, Head) == 0)
		printf("Dodavanje je uspješno!\n");
	ispisi(Head.Next);


}

int umetniIspred(char uIme, char uPrezime, int uGodina, osoba* pozicija) {
	osoba* p = (osoba*)malloc(sizeof(osoba));
	
	p->ime = uIme;
	p->prezime = uPrezime;
	p->godinaRodenja = uGodina;
	p->Next = pozicija->Next;
	pozicija->Next = p;

	return 0;
}

void ispisi(osoba* pozicija) {
	osoba* t;
	t->Next = pozicija;
	while (t != NULL) {
		printf("Ime: %s\n", t.ime);
		printf("Prezime: %s\n", t.prezime);
		printf("Godina Rodjenja: %d\n", t.godinaRodjenja);
		printf("~~~~~~~~~~~~~~~~~~~~\n");
		t->Next = t->Next->Next;
	}
}

int umetniKraj(char uIme, char uPrezime, int uGodina, osoba* pozicija) {
	osoba* p = (osoba*)malloc(sizeof(osoba));
	osoba* t;

	p->ime = uIme;
	p->prezime = uPrezime;
	p->godinaRodenja = uGodina;
	t->Next = pozicija->Next;
	while (t->Next != NULL) {
		t->Next = t->Next->Next;
	}
	p->Next = NULL;
	t->Next = p;

	return 0;
}