#ifndef ARBRE_H_
#define ARBRE_H_

/**************************************************************************************
 *          INCLUSIONS
 **************************************************************************************/
#include "lib.h"

/**************************************************************************************
 *          STRUCTURES & TYPES
 **************************************************************************************/

typedef struct bloc_arbre {
	char valeur;
	struct bloc_arbre * lv;
	struct bloc_arbre * lh;

} arbre_t;

/**************************************************************************************
 *          PROTOTYPES
 **************************************************************************************/

/**
 * Fonction initArbre :
 * @description
 * 	Initialise un arbre à partir de sa notation algébrique et renvoie son adresse.
 * @param
 * 	str - Chaîne de caractères correspondant à la notation algébrique de l'arbre à créer.
 * @variables locales
 * 	//TODO: Mettre ceci à jour lorsque la fonction est finie.
 * @sortie
 *  Un pointeur sur le nouvel arbre.
 */
arbre_t * initArbre(char * str);

/**
 * Fonctions obtenirValeur, obtenirOperation, obtenirSuivant :
 * @description
 *  Utilisées dans initArbre pour lire la chaine de caractères correspondant à
 *  la notation algébrique d'un arbre.
 * @param
 * 	str - Chaîne de caractères correspondant à la notation algébrique de l'arbre à créer.
 * 	c - position actuel dans la chaine de caractères.
 */
char obtenirValeur(char * str, int *c);
char obtenirOperation(char * str, int *c);
char * obtenirSuivant(char * str, int *c);

/**
 * Fonction arbreSupprimer :
 * @description
 *  Supprime le sous arbre donné en paramètre.
 * @param
 *  arbre - pointeur de pointeur sur l'arbre.
 * @variables locales
 *  prec - pointeur sur le sous arbre à libérer une fois supprimé.
 */
void arbreSupprimer(arbre_t ** arbre);

/**
 * Fonction arbreSupprimerValeur :
 * @description
 *  Supprime le premier sous arbre trouvé dont la valeur de la racine est celle donné en paramètre.
 * @param
 *  e - valeur à trouver dans l'arbre.
 *  arbre - pointeur de pointeur sur l'arbre.
 * @variables locales
 *  prec - pointeur de pointeur sur l'arbre trouvé.
 */
void arbreSupprimerValeur(char e, arbre_t ** arbre);

/**
 * Fonction arbreRecherche :
 * @description
 *  Recherche dans un arbre un sous arbre dont la valeur de la racine est celle donné en paramètre.
 * @param
 *  e - valeur à trouver dans l'arbre.
 *  arbre - pointeur de pointeur sur l'arbre.
 * @variables locales
 *  prec - pointeur de pointeur sur le sous arbre trouvé.
 *  cour - pointeur sur le sous arbre courant.
 *  p - pointeur sur la pile utilisé pour le parcours de l'arbre.
 *  fin - booléèn de fin de boucle.
 * @sortie
 *  pointeur de pointeur sur le sous arbre trouvé.
 */
arbre_t ** arbreRecherche(char e, arbre_t ** arbre);

/**
 * Fonction compterNoeuds :
 * @description
 *  Compte le nombre de noeuds dans un arbre.
 * @param
 *  arbre - l'arbre.
 * @variables locales
 *  total - entier correspondant au nombre de noeuds trouvé.
 *  cour - pointeur sur le sous arbre courant.
 *  p - pointeur sur la pile utilisé pour le parcours de l'arbre.
 * @sortie
 *  Le nombre de noeuds rencontré pendant le parcours de l'arbre.
 */
int compterNoeuds(arbre_t* arbre);
/**
 * Fonction mesurerHauteur :
 * @description
 *  Récupère la hauteur d'un arbre.
 * @param
 *  arbre - l'arbre.
 * @variables locales
 *  profondeur - niveau courant dans l'arbre.
 *  res - profondeur maximum atteinte.
 *  cour - pointeur sur le sous arbre courant.
 *  p - pointeur sur la pile utilisé pour le parcours de l'arbre.
 * @sortie
 *  Le nombre maximal de noeuds rencontré en descendant sur l'arbre, c'est à dire sa hauteur.
 *  Retourne 0 si l'arbre est vide.
 */
int mesurerHauteur(arbre_t* arbre);

/**
 * Fonction compterFeuilles :
 * @description
 *  Compte le nombre de feuilles dans un arbre.
 * @param
 *  arbre - l'arbre.
 * @variables locales
 *  total - entier correspondant au nombre de feuilles trouvé.
 *  cour - pointeur sur le sous arbre courant.
 *  p - pointeur sur la pile utilisé pour le parcours de l'arbre.
 * @sortie
 *  Le nombre de feuilles rencontré pendant le parcours de l'arbre.
 */
int compterFeuilles(arbre_t* arbre);

/**
 * Fonction arbreToString():
 * @description
 *  Convertit un arbre en une chaine de caractères.
 *  Utilisée pour les sorties des fonctions de tests.
 * @param
 *  arbre - arbre à convertir.
 */
char * arbreToString(arbre_t * arbre);

/**
 * Fonction libererPile :
 * @description
 *  Libère la mémoire utilisée par un arbre.
 * @param
 *  arbre - arbre à libérer.
 */
void libererArbre(arbre_t * arbre);

#endif
