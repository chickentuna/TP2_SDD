#include <stdlib.h>
#include <stdio.h>

#include "noyau/pile.h"
#include "testlib/testlib.h"
#include "tests/tests.h"
#include "noyau/arbre.h"


int main(int argc, char** argv) {

//  TODO: pourquoi tu mets tes tests ici alors que j'ai développé un super sytème ?
//	arbre_t * a = NULL;
//	printf("test\n");
//
//	a = creerArbre("1*(2+3)");
//	printf("%d\n",(int)a->valeur);
//	printf("%d\n",(int)a->lv->valeur);
//	printf("%d\n",(int)a->lv->lh->valeur);
//
//	a = creerArbre("1*(2+3+4*5*(6+7))");
//	printf("%d\n",(int)a->valeur);
//	printf("%d\n",(int)a->lv->valeur);
//	printf("%d\n",(int)a->lv->lh->valeur);

	test_t* test_head = NULL;

	AJOUTE_TEST(test_head, pleine);
	AJOUTE_TEST(test_head, vide);
	AJOUTE_TEST(test_head, depiler);
	AJOUTE_TEST(test_head, empiler);
	AJOUTE_TEST(test_head, creerPile);

	AJOUTE_TEST(test_head, countNodes);
	AJOUTE_TEST(test_head, deepSizeTree);
	AJOUTE_TEST(test_head, countLeafTree);

	executerTests(test_head, FLAG_EMPTY);
	detruireTests(test_head);

	return EXIT_SUCCESS;
}
