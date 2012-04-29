#include <stdlib.h>
#include <stdio.h>

#include "noyau/pile.h"
#include "testlib/testlib.h"
#include "tests/tests.h"
#include "noyau/arbre.h"


int main(int argc, char** argv) {
	arbre_t * a = NULL;
	printf("test\n");

	a = creerArbre("1*(2+3)");
	printf("%d\n",(int)a->valeur);
	printf("%d\n",(int)a->lv->valeur);
	printf("%d\n",(int)a->lv->lh->valeur);

	a = creerArbre("1*(2+3+4*5*(6+7))");
	printf("%d\n",(int)a->valeur); //1
	printf("%d\n",(int)a->lv->valeur); //2
	printf("%d\n",(int)a->lv->lh->valeur); //3
	printf("%d\n",(int)a->lv->lh->lh->valeur); //4
	printf("%d\n",(int)a->lv->lh->lh->lv->valeur); //5
	printf("%d\n",(int)a->lv->lh->lh->lv->lv->valeur); //6
	printf("%d\n",(int)a->lv->lh->lh->lv->lv->lh->valeur); //7




	exit(0);



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
