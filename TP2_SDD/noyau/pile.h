/**************************************************************************************
 *          CONSTANTES & MACROS
 **************************************************************************************/

#ifndef LIB_H_
#define LIB_H_

/* Constantes booléennes classiques. */
#define VRAI 1
#define FAUX 0

/**
 * Macro ALLOC :
 * @description
 *  Macro d'allocation mémoire.
 * @param
 *  _n - taille du tableau d'éléments
 *  _t - type des éléments
 * @sortie
 * 	Un pointeur vers une mémoire de taille adéquate.
 */
#define ALLOC(N,T) (T*) malloc(N*sizeof(T))

/**************************************************************************************
 *          STRUCTURES & TYPES
 **************************************************************************************/
typedef int elem;

typedef struct bloc_pile {
	elem * tab;
	int taille;
	int tete;
} pile_t;

/**************************************************************************************
 *          PROTOTYPES
 **************************************************************************************/

/**
 * Fonction initPile :
 * @description
 * 	Initialise une pile en mémoire et renvoie son adresse.
 * @param
 * 	taille - nombre éléments maximums dans la liste.
 * @variables locales
 * 	nouv - pointeur sur la nouvelle pile.
 * @sortie
 *  Un pointeur sur la nouvelle pile.
 */
pile_t * initPile(int taille);

/**
 * Fonction empiler :
 * @description
 *  Empile un élément (Sauf si la pile est pleine).
 * @param
 * 	element - élément à empiler.
 * 	pile - pile sur laquelle on empile.
 */
void empiler(elem element, pile_t * pile);

/**
 * Fonction depiler :
 * @description
 *  Dépile un élément. Si la pile est vide, renvoie une valeur arbitraire.
 * @param
 *  pile dans laquelle on dépile.
 * @sortie
 *  L'élément dépilé.
 */
elem depiler(pile_t * pile);

/**
 * Fonction vide :
 * @description
 *  Verifie si une pile est vide.
 * @param
 *  pile - pile à vérifier. *
 * @sortie
 *  Booléen indiquant si la pile est vide.
 */
int vide(pile_t * pile);

/**
 * Fonction pleine :
 * @description
 *  Verifie si une pile est pleine.
 * @param
 *  pile - pile à vérifier.
 * @sortie
 *  Booléen indiquant si la pile est pleine.
 */
int pleine(pile_t * pile);

/**
 * Fonction libererPile :
 * @description
 *  Libère la mémoire utilisée par une pile.
 * @param
 *  pile - pile à libérer.
 */
void libererPile(pile_t * pile);

char * pileToString(pile_t * pile);

#endif

