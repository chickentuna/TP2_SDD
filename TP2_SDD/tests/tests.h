/**************************************************************************************
 * Ce fichier contient tous les prototypes de test.
 **************************************************************************************/

#ifndef TESTS_H_
#define TESTS_H_

/**************************************************************************************
 *          INCLUSIONS
 **************************************************************************************/
#include "../noyau/arbre.h"
#include "../noyau/pile.h"
#include "../testlib/testlib.h"

/**************************************************************************************
 *          PROTOTYPES TESTS
 **************************************************************************************/

/* Toutes les fonctions qui suivent contiennent des tests systématiques
 * permettant de vérifier si le comportement de la fonction cible
 * est cohérent.
 */

/*Tests pile*/
result_t* test_initPile();
result_t* test_empiler();
result_t* test_depiler();
result_t* test_vide();
result_t* test_pleine();

/*Tests arbre*/
result_t* test_initArbre();
result_t* test_arbreRecherche();
result_t* test_compterNoeuds();
result_t* test_mesurerHauteur();
result_t* test_compterFeuilles();
result_t* test_arbreSupprimerValeur();

#endif /* TESTS_H_ */
