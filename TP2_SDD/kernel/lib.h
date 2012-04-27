/**************************************************************************************
 *          CONSTANTES & MACROS
 **************************************************************************************/

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

pile_t * initPile(int taille);
void empiler(elem element, pile_t * pile);
elem depiler(pile_t * pile);
int vide(pile_t * pile);
int pleine(pile_t * pile);
void libererPile(pile_t * pile);

