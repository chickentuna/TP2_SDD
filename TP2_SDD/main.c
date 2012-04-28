#include <stdlib.h>
#include <stdio.h>

#include "kernel/lib.h"
#include "testlib/testlib.h"
#include "tests/tests.h"

int main(int argc, char** argv) {

	test_t* test_head = NULL;

	AJOUTE_TEST(&test_head, empiler);

	executerTests(test_head, FLAG_EMPTY);
	detruireTests(test_head);

	return EXIT_SUCCESS;
}
