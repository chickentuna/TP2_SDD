#ifndef PILE_H_
#define PILE_H_

#include "lib.h"

/**************************************************************************************
 *          STRUCTURES & TYPES
 **************************************************************************************/

typedef struct bloc_arbre {
	/*Lien vertical*/
	struct bloc_arbre * lv;
	/*Lien horizontal*/
	struct bloc_arbre * lh;
	elem valeur;

} arbre_t;

/**************************************************************************************
 *          PROTOTYPES
 **************************************************************************************/
arbre_t * initArbre(char * str);
elem obtenirValeur(char * str, int c);

#endif
