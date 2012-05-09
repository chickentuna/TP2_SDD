#include <stdlib.h>
#include <stdio.h>

#include "testlib/testlib.h"
#include "tests/tests.h"

#include "noyau/arbre.h"

int main(int argc, char** argv) {
	test_t* test_head = NULL;
	FILE* f;
	char* buf;
	arbre_t * a;

	if (argc > 1) {
		f = fopen(argv[1],"r");
		if (f==NULL) {
			erreur("Fichier introuvable.");
		}
		buf = ALLOC(256,char);
		buf = fgets(buf,256,f);
		if (buf==NULL) {
			erreur("Fichier vide ?");
		}
		a = initArbre(buf);

		printf("Arbre chargé: %s\n",buf);
		printf("Noeuds de l'arbre (%d noeuds) : %s\n",compterNoeuds(a),arbreToString(a));
		printf("Feuilles : %d\n",compterFeuilles(a));
		printf("Hauteur : %d\n",mesurerHauteur(a));

	} else {

		/*Tests arbre*/
		/*AJOUTE_TEST(test_head, arbreSupprimer);
		AJOUTE_TEST(test_head, arbreSupprimerValeur);
		AJOUTE_TEST(test_head, arbreRecherche);
		AJOUTE_TEST(test_head, mesurerHauteur);
		AJOUTE_TEST(test_head, compterFeuilles);
		AJOUTE_TEST(test_head, compterNoeuds);*/
		AJOUTE_TEST(test_head, initArbre);

		/*Tests pile*/
		/*AJOUTE_TEST(test_head, vide);
		AJOUTE_TEST(test_head, pleine);
		AJOUTE_TEST(test_head, vide);
		AJOUTE_TEST(test_head, depiler);
		AJOUTE_TEST(test_head, empiler);
		AJOUTE_TEST(test_head, initPile);*/

		executerTests(test_head, FLAG_EMPTY);
		detruireTests(test_head);

	}
	return EXIT_SUCCESS;
}
