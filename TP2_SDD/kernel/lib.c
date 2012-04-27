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

elem depiler(pile_t * pile) {
	if (!vide(pile)) {
		return pile->tab[pile->tete--];
	}
	return (elem) NULL;
}

int vide(pile_t * pile) {
	return pile->tete == -1;
}

int pleine(pile_t * pile) {
	return pile->tete == pile->taille - 1;
}

void libererPile(pile_t * pile) {
	free(pile->tab);
	free(pile);
}
