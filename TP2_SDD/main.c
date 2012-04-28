#include <stdlib.h>
#include <stdio.h>

#include "noyau/pile.h"
#include "testlib/testlib.h"
#include "tests/tests.h"

int main(int argc, char** argv) {

	test_t* test_head = NULL;

	AJOUTE_TEST(test_head, pleine);
	AJOUTE_TEST(test_head, vide);
	AJOUTE_TEST(test_head, depiler);
	AJOUTE_TEST(test_head, empiler);
	AJOUTE_TEST(test_head, creerPile);

	executerTests(test_head, FLAG_EMPTY);
	detruireTests(test_head);

	return EXIT_SUCCESS;
}
