/**************************************************************************************
 * Ce fichier contient l'implémentation de tous les tests du programme.
 **************************************************************************************/

#include "tests.h"

result_t* test_empiler() {

	result_t* r = creerResultat();

	// Création de la pile.
	{
		pile_t* pile = initPile(5);
		assertion(r, pile->taille == 0, "Pile vide => taille 0");
		assertion(r, pile->tete == 0, "Pile vide => tete 0");
	}

	return r;

}


