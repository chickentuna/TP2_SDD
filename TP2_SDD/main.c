#include <stdlib.h>
#include <stdio.h>

#include "testlib/testlib.h"
#include "tests/tests.h"

#include "noyau/arbre.h"

int main(int argc, char** argv) {

	test_t* test_head = NULL;

	/*Tests arbre*/
	AJOUTE_TEST(test_head, arbreRecherche);
	AJOUTE_TEST(test_head, mesurerHauteur);
	AJOUTE_TEST(test_head, compterFeuilles);
	AJOUTE_TEST(test_head, compterNoeuds);
	AJOUTE_TEST(test_head, initArbre);

	/*Tests pile*/
	AJOUTE_TEST(test_head, vide);
	AJOUTE_TEST(test_head, pleine);
	AJOUTE_TEST(test_head, vide);
	AJOUTE_TEST(test_head, depiler);
	AJOUTE_TEST(test_head, empiler);
	AJOUTE_TEST(test_head, initPile);

	executerTests(test_head, FLAG_EMPTY);
	detruireTests(test_head);

	return EXIT_SUCCESS;
}
