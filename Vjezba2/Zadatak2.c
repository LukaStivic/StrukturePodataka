#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define EXIT_ERROR -1
#define EXIT_SUCCESS 0
#define MAX_IME 20
#define MAX_PREZIME 20

typedef struct osoba{
	char ime[MAX_IME];
	char prezime[MAX_PREZIME];
	int godinaRodenja;
	struct osoba* Next;
}osoba;


int umetniPocetak(char* uIme, char* uPrezime, int uGodina, osoba* pozicija);
int ispisi(osoba* pozicija);
int umetniKraj(char* uIme, char* uPrezime, int uGodina, osoba* pozicija);
osoba* pronadiPrezime(char* pPrezime, osoba* pozicija);
int brisiElement(char* bPrezime, osoba* pozicija);

int unesiIspredOsobe(char* uIme, char* uPrezime, int uGodina, char* pPrezime, osoba* pozicija);
int unesiIzaOsobe(char* uIme, char* uPrezime, int uGodina, char* pPrezime, osoba* pozicija);
int upisiDatoteku(osoba* pozicija, char* imeDatoteke);
int ispisiDatoteku(char* imeDatoteke);

int main() {

	osoba* Head;
	Head = (osoba*)malloc(sizeof(osoba));
	Head->Next = NULL;

	if (umetniPocetak("Ivo", "Ivic", 2000, Head) == 0)
		printf("Dodavanje je uspjesno!\n");
	if (umetniPocetak("Anita", "Antic", 2002, Head) == 0)
		printf("Dodavanje je uspjesno!\n");
	if (umetniKraj("Josip", "Josipovic", 1999, Head) == 0)
		printf("Dodavanje je uspjesno!\n");
	ispisi(Head->Next);
	if (brisiElement("Antic", Head) == 0)
		printf("Brisanje je uspjesno!");
	ispisi(Head->Next);
	if (unesiIspredOsobe("Josko", "Jozic", 1988, "Josipovic", Head) == 0)
		printf("Dodavanje je uspjesno!");
	if (unesiIzaOsobe("Leo", "Leone", 2001, "Ivic", Head) == 0)
		printf("Dodavanje je uspjesno!");
	ispisi(Head->Next);
	if (upisiDatoteku(Head, "osobe.txt") == 0)
		printf("Upis u datoteku uspio!");
	ispisiDatoteku("osobe.txt");


	return EXIT_SUCCESS;
}

int umetniPocetak(char* uIme, char* uPrezime, int uGodina, osoba* pozicija) {
	osoba* p = (osoba*)malloc(sizeof(osoba));
	if (!p) {
		printf("Unos nije uspio!");
		return EXIT_ERROR;
	}

	strcpy(p->ime, uIme);
	strcpy(p->prezime, uPrezime)
	p->godinaRodenja = uGodina;
	p->Next = pozicija->Next;
	pozicija->Next = p;

	return EXIT_SUCCESS;
}

int ispisi(osoba* pozicija) {
	while (pozicija != NULL) {
		printf("Ime: %s\n", pozicija->ime);
		printf("Prezime: %s\n", pozicija->prezime);
		printf("Godina Rodjenja: %d\n", pozicija->godinaRodenja);
		printf("~~~~~~~~~~~~~~~~~~~~\n");
		pozicija = pozicija->Next;
	}
	return 0;
}

int umetniKraj(char* uIme, char* uPrezime, int uGodina, osoba* pozicija) {
	osoba* p = (osoba*)malloc(sizeof(osoba));

	if (!p) {
		printf("Unos nije uspio!");
		return EXIT_ERROR;
	}

	osoba* t;

	strcpy(p->ime, uIme);
	strcpy(p->prezime, uPrezime);
	p->godinaRodenja = uGodina;
	p->Next = NULL;
	t = pozicija;
	while (t->Next != NULL) {
		t = t->Next;
	}
	t->Next = p;
	return EXIT_SUCCESS;
}

osoba* pronadiPrezime(char* pPrezime, osoba* pozicija) {
	osoba* t;
	t = pozicija;
	while (t!=NULL) {
		if (strcmp(t->prezime, pPrezime) == 0) {
			return t;
		}
		t = t->Next;
	}

	return NULL;
}

int brisiElement(char* pPrezime, osoba* pozicija) {
	osoba* p = pronadiPrezime(pPrezime, pozicija);
	
	if (p == NULL) {
		printf("Osoba ne postoji.");
		return EXIT_ERROR;
	}

	osoba* prosli = pozicija;
	while (prosli->Next != p) {
		prosli = prosli->Next;
	}

	prosli->Next = p->Next;
	free(p);

	return EXIT_SUCCESS;
}

int unesiIspredOsobe(char* uIme, char* uPrezime, int uGodina, char* pPrezime, osoba* pozicija){
	osoba* o = pronadiPrezime(pPrezime, pozicija);

	if (o == NULL) {
		printf("Osoba ne postoji.");
		return EXIT_ERROR;
	}

	osoba* p = (osoba*)malloc(sizeof(osoba));
	if (!p) {
		printf("Unos nije uspio!");
		return EXIT_ERROR;
	}
	strcpy(p->ime, uIme);
	strcpy(p->prezime, uPrezime);
	p->godinaRodenja = uGodina;
	p->Next = o;

	osoba* prosli = pozicija;
	while (prosli->Next != o) {
		prosli = prosli->Next;
	}

	prosli->Next = p;

	return EXIT_SUCCESS;
}


int unesiIzaOsobe(char* uIme, char* uPrezime, int uGodina, char* pPrezime, osoba* pozicija){
	osoba* o = pronadiPrezime(pPrezime, pozicija);

	if (o == NULL) {
		printf("Osoba ne postoji.");
		return EXIT_ERROR;
	}

	osoba* p = (osoba*)malloc(sizeof(osoba));
	if (!p) {
		printf("Unos nije uspio!");
		return EXIT_ERROR;
	}
	strcpy(p->ime, uIme);
	strcpy(p->prezime, uPrezime);
	p->godinaRodenja = uGodina;
	p->Next = o->Next;
	o->Next = p;

	return EXIT_SUCCESS;
}

int upisiDatoteku(osoba* pozicija, char* imeDatoteke){
	FILE* Datoteka = fopen(imeDatoteke, "w");
	if (!Datoteka) {
		printf("Datoteka nije pravilno otvorena!");
		return EXIT_ERROR;
	}

	osoba* t = pozicija->Next;
	while (t != NULL) {
		fprintf(Datoteka, "%s %s %d\n", t->ime, t->prezime, t->godinaRodenja);
	}
	fclose(Datoteka);
	return EXIT_SUCCESS;
}

int ispisiDatoteku(char* imeDaroteke){
	FILE* Datoteka = fopen(imeDatoteke, "r");
	if (!Datoteka) {
		printf("Datoteka nije pravilno otvorena!");
		return EXIT_ERROR;
	}

	osoba* t = (osoba*)malloc(sizeof(osoba));
	if (!t) {
		printf("Memorija nije alocirana!");
		return EXIT_ERROR;
	}

	while (fscanf(Datoteka, "%s %s %d", t->ime, t->prezime, t->godinaRodenja)==3) {
		printf("%s %s %d\n", t->ime, t->prezime, t->godinaRodenja);
	}

	fclose(Datoteka);
	free(t);
	return EXIT_SUCCESS;
}