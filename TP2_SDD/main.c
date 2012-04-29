#include <stdlib.h>
#include <stdio.h>

#include "testlib/testlib.h"
#include "tests/tests.h"

#include "noyau/arbre.h"
#include "noyau/list.h"


int main(int argc, char** argv) {

	test_t* test_head = NULL;

	AJOUTE_TEST(test_head, createLList);
	AJOUTE_TEST(test_head, destroyLList);
	AJOUTE_TEST(test_head, removeLList);
	AJOUTE_TEST(test_head, removeNextLList);
	AJOUTE_TEST(test_head, getPrevLList);

	AJOUTE_TEST(test_head, pushLPile);
	AJOUTE_TEST(test_head, createLPile);

	AJOUTE_TEST(test_head, countNodes);
	AJOUTE_TEST(test_head, deepSizeTree);
	AJOUTE_TEST(test_head, countLeafTree);

	executerTests(test_head, FLAG_EMPTY);
	detruireTests(test_head);

	return EXIT_SUCCESS;
}
