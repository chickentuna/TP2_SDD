/**************************************************************************************
 *          CONSTANTES & MACROS
 **************************************************************************************/

/* Constantes bool�ennes classiques. */
#define VRAI 1
#define FAUX 0

/**
 * Macro ALLOC :
 * @description
 *  Macro d'allocation m�moire.
 * @param
 *  _n - taille du tableau d'�l�ments
 *  _t - type des �l�ments
 * @sortie
 * 	Un pointeur vers une m�moire de taille ad�quate.
 */
#define ALLOC(_n,_t) (_t*) malloc(_n*sizeof(_t))

/**************************************************************************************
 *          STRUCTURES & TYPES
 **************************************************************************************/
typedef int elem;

typedef struct bloc_pile {
	elem * tab;
	int taille;
	int deb;
	int fin;
} pile_t;

/**************************************************************************************
 *          PROTOTYPES
 **************************************************************************************/

void empiler(elem element, pile_t * pile);
elem depiler(pile_t * pile);
int vide(pile_t * pile);
pile_t * initPile();
void libererPile(pile_t * pile);

