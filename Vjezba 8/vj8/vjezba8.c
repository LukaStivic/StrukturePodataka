#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

struct stablo;
typedef struct stablo* Stablo;
typedef struct stablo {
	int el;
	Stablo left;
	Stablo right;
}s;

struct cvor;
typedef struct cvor* poz;
typedef struct cvor {
	poz next;
	Stablo stb;
}cvor;

int unosElementa(Stablo root);
Stablo brisiElement(Stablo root, int eb);
int traziElement(Stablo root);

int inorderIspis(Stablo root);
int preorderIspis(Stablo root);
int postorderIspis(Stablo root);
int levelOrderIspis(Stablo root);

int provjera(Stablo root);
int postaviNaKraj(poz Head, poz x);
Stablo traziMin(Stablo root);

int main() {

	Stablo Stablo1 = (Stablo)malloc(sizeof(s));
	Stablo1->left = NULL;
	Stablo1->right = NULL;
	int check = -1;
	int b;

	printf("Odeberite funkciju za binarno stablo:\n");
	printf("1 - novi element u binarno stablo\n");
	printf("2 - brisanje elementa iz binarnog stabla\n");
	printf("3 - inorder ispis stabla\n");
	printf("4 - preorder ispis stabla\n");
	printf("5 - postorder ispis stabla\n");
	printf("6 - level order ispis stabla\n");
	printf("7 - pronalazenje elementa u stablu\n");
	printf("0 - zavrsi program\n");

	while (check != 0) {
		printf("Unesite odabranu funkciju:\n");
		scanf("%d", &check);

		if (check == 1) {
			if (unosElementa(Stablo1) != EXIT_SUCCESS) {
				printf("Greska pri unosu elementa.\n");
				return EXIT_FAILURE;
			}
		}
		else if (check == 2) {
			if (provjera(Stablo1) != EXIT_SUCCESS) {
				printf("Stablo je prazno!\n");
			}
			else {
				printf("Unesi element koji treba obrisati:\n");
				scanf("%d", &b);
				brisiElement(Stablo1->right, b);
			}
		}
		else if (check == 3) {
			if (provjera(Stablo1) != EXIT_SUCCESS) {
				printf("Stablo je prazno!\n");
			}
			else {
				if (inorderIspis(Stablo1->right) != EXIT_SUCCESS) {
					printf("Neispravan ispis stabla!\n");
					return EXIT_FAILURE;
				}
			}
		}
		else if (check == 4) {
			if (provjera(Stablo1) != EXIT_SUCCESS) {
				printf("Stablo je prazno!\n");
			}
			else {
				if (preorderIspis(Stablo1->right) != EXIT_SUCCESS) {
					printf("Neispravan ispis stabla!\n");
					return EXIT_FAILURE;
				}
			}
		}
		else if (check == 5) {
			if (provjera(Stablo1) != EXIT_SUCCESS) {
				printf("Stablo je prazno!\n");
			}
			else {
				if (postorderIspis(Stablo1->right) != EXIT_SUCCESS) {
					printf("Neispravan ispis stabla!\n");
					return EXIT_FAILURE;
				}
			}
		}
		else if (check == 6) {
			if (provjera(Stablo1) != EXIT_SUCCESS) {
				printf("Stablo je prazno!\n");
			}
			else {
				if (levelOrderIspis(Stablo1->right) != EXIT_SUCCESS) {
					printf("Neispravan ispis stabla!\n");
					return EXIT_FAILURE;
				}
			}
		}
		else if (check == 7) {
			if (traziElement(Stablo1->right) != EXIT_SUCCESS) {
				printf("Greska u pretrazivanju!\n");
				return EXIT_FAILURE;
			}
		}
		else if (check == 0) {
			break;
		}
		else {
			printf("Neispravan unos, molim ponovite.\n");
		}
		check = -1;

	}


	return EXIT_SUCCESS;
}

int unosElementa(Stablo root) {

	Stablo novaGrana = (Stablo)malloc(sizeof(s));
	novaGrana->left = NULL;
	novaGrana->right = NULL;


	printf("Unesite element:\n");
	scanf("%d", &novaGrana->el);

	if (root->left == NULL && root->right == NULL) {
		root->right = novaGrana;
		return EXIT_SUCCESS;
	}

	root = root->right;
	while (root != NULL) {
		if (root->el > novaGrana->el && root->left != NULL) {
			root = root->left;
		}
		else if (root->el <= novaGrana->el && root->right != NULL){
			root = root->right;
		}
		else if(root->el > novaGrana->el){
			root->left = novaGrana;
			break;
		}
		else {
			root->right = novaGrana;
			break;
		}
	}

	return EXIT_SUCCESS;
}

int inorderIspis(Stablo root) {

	if (root == NULL) {
		return EXIT_SUCCESS;
	}

	inorderIspis(root->left);
	printf("%d\n", root->el);
	inorderIspis(root->right);
	return EXIT_SUCCESS;
}

int preorderIspis(Stablo root) {

	if (root == NULL) {
		return EXIT_SUCCESS;
	}

	printf("%d\n", root->el);
	preorderIspis(root->left);
	preorderIspis(root->right);
	return EXIT_SUCCESS;
}

int postorderIspis(Stablo root) {
	if (root == NULL) {
		return EXIT_SUCCESS;
	}

	postorderIspis(root->left);
	postorderIspis(root->right);
	printf("%d\n", root->el);
	return EXIT_SUCCESS;
}

int levelOrderIspis(Stablo root) {
	
	if (root == NULL) {
		return EXIT_SUCCESS;
	}

	poz Head = (poz)malloc(sizeof(cvor));
	Head->next = NULL;

	poz nE = (poz)malloc(sizeof(cvor));
	Head->next = nE;
	nE->stb = root;
	nE->next = NULL;

	while (Head->next != NULL) {

		poz t = Head->next;
		printf("%d\n", t->stb->el);


		if (t->stb->left != NULL) {
			poz l = (poz)malloc(sizeof(cvor));
			l->stb = t->stb->left;
			postaviNaKraj(Head, l);
		}
		if (t->stb->right != NULL) {
			poz r = (poz)malloc(sizeof(cvor));
			r->stb = t->stb->right;
			postaviNaKraj(Head, r);
		}

		Head->next = Head->next->next;
		free(t);
	}

	return EXIT_SUCCESS;
}

int postaviNaKraj(poz Head, poz x) {

	while (Head->next != NULL) {
		Head = Head->next;
	}

	x->next = Head->next;
	Head->next = x;

	return EXIT_SUCCESS;
}

int provjera(Stablo root) {
	if (root->right == NULL) {
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}

int traziElement(Stablo root) {

	int et;
	printf("Upisi element koji zelis pronaci u stablu:\n");
	scanf("%d", &et);

	if (root == NULL) {
		printf("Stablo je prazno!");
		return EXIT_SUCCESS;
	}

	while (root != NULL) {
		if (root->el == et) {
			printf("Element %d postoji u stablu!\n", et);
			return EXIT_SUCCESS;
		}
		else if (root->el > et) {
			root = root->left;
		}
		else {
			root = root->right;
		}
	}

	printf("Ne postoji element %d u stablu!\n", et);
	return EXIT_SUCCESS;
}

Stablo brisiElement(Stablo root, int eb) {

	Stablo t;

	if (root == NULL) {
		printf("Element nije u stablu!\n");
	}
	else if (eb < root->el) {
		root->left = brisiElement(root->left, eb);
	}
	else if (eb > root->el) {
		root->right = brisiElement(root->right, eb);
	}
	else if (root->left != NULL && root->right != NULL) {
		t = traziMin(root->right);
		root->el = t->el;
		root->right = brisiElement(root->right, root->el);
	}
	else {
		t = root;
		if (root->left == NULL) {
			root = root->right;
		}
		else {
			root = root->left;
		}
		free(t);
	}

	return root;
}

Stablo traziMin(Stablo root) {

	while (root->left != NULL) {
		root = root->left;
	}

	return root;
}
