#include "lib.h"
#include <stdlib.h>

pile_t * initPile(int taille) {
	pile_t * nouv;

	nouv = ALLOC(1,pile_t);
	nouv->tab = ALLOC(taille,elem);
	nouv->tete = -1;
	nouv->taille = taille;
	return nouv;
}

void empiler(elem element, pile_t * pile) {
	if (!pleine(pile)) {
		pile->tab[++pile->tete] = element;
	}
}



/*
elem depiler(pile_t * pile);
int vide(pile_t * pile);

void libererPile(pile_t * pile);
*/
