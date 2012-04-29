/**************************************************************************************
 * Ce fichier contient tous les prototypes de test.
 **************************************************************************************/

#ifndef TESTS_H_
#define TESTS_H_

/**************************************************************************************
 *          INCLUSIONS
 **************************************************************************************/
#include "../noyau/pile.h"
#include "../noyau/arbre.h"
#include "../testlib/testlib.h"

/**************************************************************************************
 *          PROTOTYPES TESTS
 **************************************************************************************/

/* Toutes les fonctions qui suivent contiennent des tests systématiques
 * permettant de vérifier si le comportement de la fonction cible
 * est cohérent.
 */

result_t* test_creerPile();
result_t* test_empiler();
result_t* test_depiler();
result_t* test_vide();
result_t* test_pleine();

result_t* test_countNodes();
result_t* test_deepSizeTree();
result_t* test_countLeafTree();

#endif /* TESTS_H_ */
