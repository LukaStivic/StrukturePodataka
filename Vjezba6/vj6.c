#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_SIZE 64
#define MAX_DATE_SIZE 20

struct artikl;
typedef struct artikl* pozA;
typedef struct artikl {
	char imeA[MAX_NAME_SIZE];
	int kolicina;
	float cijena;
	pozA NextA;
}artikl;

struct racun;
typedef struct racun* pozR;
typedef struct racun {
	char datum[MAX_DATE_SIZE];
	pozR NextR;
	pozA NextA;
}racun;


int unosRacuna(char* fileName, pozR HeadR);
int umetniRacunUNiz(pozR HeadR, pozR noviR);
int umetniArtikl(char* ime, int k, float c, pozA HeadA);

int provjera(pozR HeadR);


int main() {

	FILE* fp = fopen("racuni.txt", "r");
	if (!fp) {
		printf("Pocetni file nije ucitan!\n");
		return EXIT_FAILURE;
	}

	char fileName[MAX_NAME_SIZE];

	pozR HeadR = (pozR)malloc(sizeof(racun));
	HeadR->NextR = NULL;

	while (fscanf(fp, "%s", fileName) == 1) {
		
		if (unosRacuna(fileName, HeadR) != EXIT_SUCCESS) {
			printf("Racun nije pravilno ucitan!\n");
			return EXIT_FAILURE;
		}
	}

	fclose(fp);

	int i = 2;

	while (i != 0) {
		printf("Unesite sljedecu akciju:\n");
		printf("1 - provjera troska artikla na vremenskom periodu\n");
		printf("0 - zavrsi program\n");

		scanf("%d", &i);
		if (i == 1) {
			provjera(HeadR);
		}
		if (i != 1 && i != 0) {
			printf("Pogresan unos, molimo unesite jednu od ponudenih opcija!\n");
		}

	}

	return EXIT_SUCCESS;
}

int unosRacuna(char* fileName, pozR HeadR) {
	FILE* fr = fopen(fileName, "r");
	if (!fr) {
		printf("File racuna nije otvoren!\n");
		return EXIT_FAILURE;
	}

	pozR noviR = (pozR)malloc(sizeof(racun));
	fscanf(fr, "%s", noviR->datum);

	if (umetniRacunUNiz(HeadR, noviR) != EXIT_SUCCESS) {
		printf("Racun nije pravilno umetnut!\n");
		return EXIT_FAILURE;
	}

	pozA HeadA = (pozA)malloc(sizeof(artikl));
	noviR->NextA = HeadA;
	HeadA->NextA = NULL;

	char imeArtikla[MAX_NAME_SIZE];
	int kolicinaA;
	float cijenaA;

	while (fscanf(fr, "%s %d %f", imeArtikla, &kolicinaA, &cijenaA) == 3) {
		if (umetniArtikl(imeArtikla, kolicinaA, cijenaA, HeadA) != EXIT_SUCCESS) {
			printf("Artikl nije pravilno postavljen u racun!\n");
			return EXIT_FAILURE;
		}
	}

	fclose(fr);

	return EXIT_SUCCESS;
}

int umetniRacunUNiz(pozR HeadR, pozR noviR) {

	pozR t;
	t = HeadR->NextR;

	while (t != NULL && strcmp(t->datum, noviR->datum) < 0) {
		
		t = t->NextR;
		HeadR = HeadR->NextR;

	}

	noviR->NextR = t;
	HeadR->NextR = noviR;
	
	return EXIT_SUCCESS;
}

int umetniArtikl(char* ime, int k, float c, pozA HeadA) {

	pozA noviA = (pozA)malloc(sizeof(artikl));
	strcpy(noviA->imeA, ime);
	noviA->kolicina = k;
	noviA->cijena = c;

	while (HeadA->NextA != NULL && strcmp(HeadA->NextA->imeA, noviA->imeA) > 0) {
		HeadA = HeadA->NextA;
	}

	noviA->NextA = HeadA->NextA;
	HeadA->NextA = noviA;

	return EXIT_SUCCESS;
}

int provjera(pozR HeadR) {

	char ime[MAX_NAME_SIZE];
	char datumP[MAX_DATE_SIZE];
	char datumK[MAX_DATE_SIZE];
	int kolicinaA = 0;
	float cijenaA = 0;

	printf("Unesite naziv artikla (Prvo slovo veliko, ime artikla je spojeno):\n");
	scanf("%s", ime);

	printf("Unesite datum od kojeg pocinje pretraga u formatu GGGG-MM-DD:\n");
	scanf("%s", datumP);

	int check = 0;

	while (check != 1) {
		printf("Unesite datum do kojeg zavrsava pretraga u formatu GGGG-MM-DD:\n");
		scanf("%s", datumK);

		if (strcmp(datumK, datumP) < 0) {
			printf("Neispravan unos datuma zavrsetka pretrage!\n");
		}
		else {
			check = 1;
		}
	}

	pozR tp;
	tp = HeadR->NextR;

	if (tp == NULL) {
		printf("Ne postoje racuni u listi!\n");
		return EXIT_FAILURE;
	}

	while (tp != NULL && strcmp(tp->datum, datumP) < 0) {
		tp = tp->NextR;
	}

	if (tp == NULL) {
		printf("Ne postoji racun poslije tog datuma!\n");
		return EXIT_SUCCESS;
	}

	pozR tk;

	tk = tp;

	while (tk->NextR != NULL && strcmp(tk->datum, datumK) < 0) {
		tk = tk->NextR;
	}

	pozA currentA;
	
	while (tp != NULL && tp != tk->NextR) {
		currentA = tp->NextA->NextA;
		while (currentA != NULL) {
			if (strcmp(currentA->imeA, ime) == 0) {
				kolicinaA += currentA->kolicina;
				cijenaA += currentA->cijena;
			}
			currentA = currentA->NextA;
		}
		tp = tp->NextR;
	}

	if (kolicinaA == 0) {
		printf("Artikl nije kupljen!\n");
	}
	else {
		printf("Artikl %s je kupljen %d puta, a ukupno je potroseno %f eura.\n", ime, kolicinaA, cijenaA);
	}

	return EXIT_SUCCESS;
}