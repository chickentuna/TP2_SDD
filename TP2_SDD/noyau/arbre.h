#ifndef ARBRE_H_
#define ARBRE_H_

#include "lib.h"
#include "element.h"

/**************************************************************************************
 *          STRUCTURES & TYPES
 **************************************************************************************/

typedef struct bloc_arbre {
	/*Lien vertical*/
	struct bloc_arbre * lv;
	/*Lien horizontal*/
	struct bloc_arbre * lh;
	elem_t valeur;

} arbre_t;

/**************************************************************************************
 *          PROTOTYPES
 **************************************************************************************/
arbre_t * creerArbre(char * str);
elem_t obtenirValeur(char * str, int *c);
char obtenirOperation(char * str, int *c);
char * obtenirSuivant(char * str, int *c);

#endif
