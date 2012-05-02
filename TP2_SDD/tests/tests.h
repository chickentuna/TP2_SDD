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


result_t* test_initArbre();

result_t* test_compterNoeuds();
result_t* test_mesurerHauteur();
result_t* test_compterFeuilles();

#endif /* TESTS_H_ */
