#ifndef ARBRE_H_
#define ARBRE_H_

#include "lib.h"
#include "list.h"
#include "element.h"

/**************************************************************************************
 *          STRUCTURES & TYPES
 **************************************************************************************/

typedef struct bloc_arbre {
	elem_t valeur;
	struct bloc_arbre * lv;
	struct bloc_arbre * lh;

} arbre_t;

/**************************************************************************************
 *          PROTOTYPES
 **************************************************************************************/
arbre_t * creerArbre(char * str);
elem_t obtenirValeur(char * str, int *c);
char obtenirOperation(char * str, int *c);
char * obtenirSuivant(char * str, int *c);

char * arbreToString(arbre_t * arbre);
void detruireArbre(arbre_t * arbre);

int compterNoeuds(arbre_t* arbre);
int mesurerProfondeur(arbre_t* arbre);
int compterFeuilles(arbre_t* arbre);

#endif
