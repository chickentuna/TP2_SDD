#include <stdlib.h>
#include <stdio.h>

#include "testlib/testlib.h"
#include "tests/tests.h"

#include "noyau/arbre.h"

int main(int argc, char** argv) {

	test_t* test_head = NULL;

	AJOUTE_TEST(test_head, creerArbre);
	AJOUTE_TEST(test_head, countNodes);
//	AJOUTE_TEST(test_head, deepSizeTree);
//	AJOUTE_TEST(test_head, countLeafTree);

	executerTests(test_head, FLAG_EMPTY);
	detruireTests(test_head);

	return EXIT_SUCCESS;
}
