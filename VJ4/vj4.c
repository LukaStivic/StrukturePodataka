#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct polinom;
typedef struct polinom* pozicija;
typedef struct polinom {
	int koef;
	int exp;
	pozicija Next;
}polinom;

int ucitajPolinom(pozicija P, char* fileName);
int zbrojiPolinome(pozicija P1, pozicija P2);
int mnoziPolinome(pozicija P1, pozicija P2);
int umetniElement(pozicija P, pozicija unos);

pozicija nadiProsli(pozicija P, pozicija t);

int main() {

	pozicija Head1 = (pozicija)malloc(sizeof(polinom));
	pozicija Head2 = (pozicija)malloc(sizeof(polinom));
	Head1->Next = NULL;
	Head2->Next = NULL;

	if (ucitajPolinom(Head1, "polinom1.txt") != EXIT_SUCCESS) {
		printf("Polinom nije pravilno ucitan!");
		return EXIT_FAILURE;
	}
	if (ucitajPolinom(Head2, "polinom2.txt") != EXIT_SUCCESS) {
		printf("Polinom nije pravilno ucitan!");
		return EXIT_FAILURE;
	}

	if (zbrojiPolinome(Head1->Next, Head2->Next) != EXIT_SUCCESS) {
		printf("Zbroj polinoma nije pravilno izvrsen!");
		return EXIT_FAILURE;
	}

	if (mnoziPolinome(Head1->Next, Head2->Next) != EXIT_SUCCESS) {
		printf("Monozenje polinoma nije pravilno izvrseno!");
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}

int ucitajPolinom(pozicija P, char* fileName) {

	FILE* f;
	f = fopen(fileName, "r");
	if (f == NULL) {
		printf("Nije otovoren file!");
		return EXIT_FAILURE;
	}

	pozicija t = (pozicija)malloc(sizeof(polinom));
	t->Next = NULL;
	while (fscanf(f, "%d %d", &t->koef, &t->exp)==2) {
		if (umetniElement(P, t) == EXIT_SUCCESS) {
			continue;
		}
		else {
			printf("Greska pri upisu elementa u polinom!");
			return EXIT_FAILURE;
		}
	}

	free(t);
	fclose(f);
	return EXIT_SUCCESS;
}

int umetniElement(pozicija P, pozicija unos) {

	pozicija noviElement = (pozicija)malloc(sizeof(polinom));
	noviElement = unos;
	pozicija temp = P->Next;

	while (temp != NULL && noviElement->exp > temp->exp) {
		temp = temp->Next;
	}

	if (temp != NULL && noviElement->exp == temp->exp) {
		temp->koef += noviElement->koef;
		if (temp->koef == 0) {
			pozicija prosli = nadiProsli(P, temp);
			prosli->Next = temp->Next;
			free(temp);
		}
		free(noviElement);
	}
	else {
		noviElement->Next = temp;
		pozicija prosli = nadiProsli(P, temp);
		prosli->Next = noviElement;
	}

	return EXIT_SUCCESS;
}

pozicija nadiProsli(pozicija P, pozicija t) {
	pozicija prosli = P;
	while (prosli->Next != NULL && prosli->Next != t) {
		prosli = prosli->Next;
	}
	return prosli;
}

int zbrojiPolinome(pozicija P1, pozicija P2) {

	pozicija HeadZ = (pozicija)malloc(sizeof(polinom));
	pozicija t1, t2;
	t1 = P1->Next;
	t2 = P2->Next;

	while (t1 != NULL) {
		if (umetniElement(HeadZ, t1) != EXIT_SUCCESS) {
			printf("Element 1 nije pravilno unesen u zbroj!");
			return EXIT_FAILURE;
		}
		t1 = t1->Next;
	}
	while (t2 != NULL) {
		if (umetniElement(HeadZ, t2) != EXIT_SUCCESS) {
			printf("Element 2 nije pravilno unesen u zbroj!");
			return EXIT_FAILURE;
		}
		t2 = t2->Next;
	}

	printf("Zbroj polinoma: ");
	pozicija p;
	p = HeadZ->Next;
	while (p!=NULL) {
		printf("%d %d", p->koef, p->exp);
		if (p->Next != NULL) {
			printf(" + ");
		}
		p = p->Next;
	}

	pozicija temp;
	while (HeadZ != NULL) {
		temp = HeadZ;
		HeadZ = HeadZ->Next;
		free(temp);
	}

	return EXIT_SUCCESS;
}

int mnoziPolinome(pozicija P1, pozicija P2) {

	pozicija HeadM = (pozicija)malloc(sizeof(polinom));
	pozicija t1, t2;
	t1 = P1->Next;
	t2 = P2->Next;

	if (t1 == NULL || t2 == NULL) {
		printf("Jedan od elemenata ne postoji, polinom je 0!");
		return EXIT_SUCCESS;
	}

	pozicija p = (pozicija)malloc(sizeof(polinom));
	pozicija brojac;
	while (t1 != NULL) {
		brojac = t2;
		while (brojac != NULL) {
			p->koef = t1->koef * brojac->koef;
			p->exp = t1->exp * brojac->exp;
			if (umetniElement(HeadM, p) != EXIT_SUCCESS) {
				printf("Element nije pravilno unesen u umnozak!");
				return EXIT_FAILURE;
			}
			brojac = brojac->Next;
		}
		t1 = t1->Next;
	}

	printf("Umnozak polinoma: ");
	pozicija b = HeadM->Next;
	while (b != NULL) {
		printf("%d %d", b->koef, b->exp);
		if (b->Next != NULL) {
			printf(" + ");
		}
		b = b->Next;
	}

	pozicija temp;
	while (HeadM != NULL) {
		temp = HeadM;
		HeadM = HeadM->Next;
		free(temp);
	}

	free(p);

	return EXIT_SUCCESS;
}