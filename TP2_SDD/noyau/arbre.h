#ifndef ARBRE_H_
#define ARBRE_H_

/**************************************************************************************
 *          INCLUSIONS
 **************************************************************************************/
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

void arbreSupprimer(arbre_t ** arbre);
void arbreSupprimerValeur(elem_t e, arbre_t ** arbre);
arbre_t ** arbreRecherche(elem_t e, arbre_t ** arbre);

/**
 * Fonction creerArbre :
 * @description
 * 	Initialise un arbre à partir de sa notation algébrique et renvoie son adresse.
 * @param
 * 	str - Chaîne de caractères correspondant à la notation algébrique de l'arbre à créer.
 * @variables locales
 * 	//TODO: Mettre ceci à jour lorsque la fonction est finie.
 * @sortie
 *  Un pointeur sur le nouvel arbre.
 */
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
