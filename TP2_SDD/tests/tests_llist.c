/*
 * llist_test.c
 *
 *  Created on: 29 avr. 2012
 *      Author: Loup
 */

#include "tests.h"

#define DEBUG_createLList()							\
	llist_t* A = createLList(DEBUG_createPInt(1));	\
	llist_t* B = createLList(DEBUG_createPInt(1));	\
	llist_t* C = createLList(DEBUG_createPInt(1));	\
	A->next = B;									\
	B->next = C;									\

void DEBUG_destroyPInt(void* addr) {
	free(addr);
}

void* DEBUG_createPInt(int i) {
	int* pi = ALLOC(1, int);
	*pi = i;
	return pi;
}

result_t* test_createLList() {
	result_t* r = creerResultat();
	{
		char* chaine = ALLOC(5, char);
		chaine = "blab";

		llist_t* list = createLList(chaine);

		char* res = (char*)list->addr;

		assert_t* a = assertion(r, res == chaine, "Cas général : adresses égales.");
		ajouterDonnee(a, creerDonnee(TYPE_DUMP, str_join("", "Valeur de la chaine : ", res, NULL)));

		free(chaine);
		free(list);
	}
	{
		int* entier = ALLOC(1, int);
		*entier = 547;

		llist_t* list = createLList(entier);

		int* res = (int*)list->addr;

		assert_t* a = assertion(r, res == entier, "Cas général : adresses égales.");
		ajouterDonnee(a, creerDonneeWithInt(TYPE_DUMP, "Valeur de l'entier", *res));

		free(entier);
		free(list);
	}
	return r;
}

result_t* test_destroyLList() {
	result_t* r = creerResultat();
	{
		void* entier = DEBUG_createPInt(574);
		llist_t* list = createLList(entier);

		int* res = (int*)list->addr;

		assert_t* a = assertion(r, res == entier, "Cas général : adresses égales.");
		ajouterDonnee(a, creerDonneeWithInt(TYPE_DUMP, "Valeur de l'entier", *res));

		destroyLList(list, DEBUG_destroyPInt);
	}
	return r;
}

result_t* test_getPrevLList() {
	result_t* r = creerResultat();
	{
		DEBUG_createLList();

		llist_t** prev = getPrevLList(&A, B);

		assertion(r, A->next == *prev, "Cas général : adresses égales.");

		destroyLList(A, DEBUG_destroyPInt);
	}
	{
		llist_t B = {DEBUG_createPInt(2), NULL};

		llist_t** prev = getPrevLList(NULL, &B);

		assertion(r, prev == NULL, "Cas liste vide : adresse nulle.");
	}
	return r;
}

result_t* test_removeLList() {
	result_t* r = creerResultat();
	{
		DEBUG_createLList();

		removeNextLList(&(A->next), DEBUG_destroyPInt);

		assertion(r, A->next == C, "Cas général : adresses égales (A et C).");

		destroyLList(A, DEBUG_destroyPInt);
	}
	{
		removeNextLList(NULL, DEBUG_destroyPInt);
		assertion(r, VRAI, "Cas pointeur null.");
	}
	return r;
}

result_t* test_removeNextLList() {
	result_t* r = creerResultat();
	{
		DEBUG_createLList();

		removeLList(&A, A, DEBUG_destroyPInt);

		assertion(r, A->next == C, "Cas général : adresses égales (A et C).");

		destroyLList(A, DEBUG_destroyPInt);
	}
	return r;
}


