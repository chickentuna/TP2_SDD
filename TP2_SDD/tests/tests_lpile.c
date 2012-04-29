#include "tests.h"

result_t* test_createLPile() {
	result_t* r = creerResultat();
	{
		lpile_t* pile = NULL;
		assertion(r, pile == NULL, "Création d'une pile vide");
	}
	return r;
}

result_t* test_pushLPile() {
	result_t* r = creerResultat();

	//Cas général
	{
		lpile_t* pile = NULL;
		int i;

		for (i = 1; i < 4; i++) {
			int *pi = ALLOC(1, int);
			*pi = i;
			pushLPile(&pile, pi);
		}

		int *a;
		pop_from(pile, a);
		int *b;
		pop_from(pile, b);
		int *c;
		pop_from(pile, c);

		assertion(r, *a == 3 && *b == 2 && *c == 1,
				"Cas général (empilement de 1,2,3)");

		destroyLList(pile, free);
	}

	//Cas de la pile vide
	{
		lpile_t* pile = NULL;

		lpile_t* head = popLPile(&pile);

		assertion(r, head == NULL, "Cas de la pile vide");

		destroyLList(pile, free);
	}

	return r;
}

result_t* test_estVideLPile() {
	result_t* r = creerResultat();

	//Cas pile vide
	{
		int* i = ALLOC(1, int);
		*i = 5;

		lpile_t* pile = createLPile(i);

		assertion(r, estVideLPile(pile), "Cas de la pile vide");

		destroyLList(pile, free);
	}

	//Cas de la pile non vide
	{
		lpile_t* pile = NULL;

		int i;
		int* pi;
		for (i = 1; i < 4; i++) {
			pi = ALLOC(1, int);
			*pi = i;
			pushLPile(&pile, pi);
		}

		assertion(r, !estVideLPile(pile), "Cas de la pile non vide");

		destroyLList(pile, free);
	}
	return r;
}
