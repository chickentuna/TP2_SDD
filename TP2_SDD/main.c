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
		if (strcmp(argv[1],"test")!=0) {
			f = fopen(argv[1],"r");
			if (f==NULL) {
				erreur("Fichier introuvable.\n");
			}
			buf = ALLOC(256,char);
			buf = fgets(buf,256,f);
			if (buf==NULL) {
				erreur("Fichier vide ?\n");
			}
			fclose(f);
			
			a = initArbre(buf);
			printf("Arbre chargé: %s\n",buf);
			free(buf);
			buf = arbreToString(a);
			printf("Noeuds de l'arbre (%d noeuds) : %s\n", compterNoeuds(a), buf);
			printf("Feuilles : %d\n", compterFeuilles(a));
			printf("Hauteur : %d\n", mesurerHauteur(a));
			free(buf);
			libererArbre(a);
		} else {
			/*Tests arbre*/
			AJOUTE_TEST(test_head, arbreSupprimer);
			AJOUTE_TEST(test_head, arbreSupprimerValeur);
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
		}
	} else {
		printf("Veuillez ajouter le nom d'un fichier arbre à charger (ou 'test' pour lancer les tests unitaires).\n");
	}
	return EXIT_SUCCESS;
}
