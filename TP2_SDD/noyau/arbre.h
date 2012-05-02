#ifndef ARBRE_H_
#define ARBRE_H_

#include "lib.h"
#include "element.h"

/**************************************************************************************
 *          STRUCTURES & TYPES
 **************************************************************************************/
typedef void* elema_t;

typedef struct bloc_arbre {
	elema_t valeur;
	struct bloc_arbre * lv;
	struct bloc_arbre * lh;

} arbre_t;

/**************************************************************************************
 *          PROTOTYPES
 **************************************************************************************/
arbre_t * initArbre(char * str);
elema_t obtenirValeur(char * str, int *c);
char obtenirOperation(char * str, int *c);
char * obtenirSuivant(char * str, int *c);

char * arbreToString(arbre_t * arbre);
void libererArbre(arbre_t * arbre);

int compterNoeuds(arbre_t* arbre);
int mesurerProfondeur(arbre_t* arbre);
int compterFeuilles(arbre_t* arbre);

#endif
