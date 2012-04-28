#include "pile.h"

pile_t * creerPile(int taille) {
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
	return (elem) 0;
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

char * pileToString(pile_t * pile) {
	char * buf;
	int i;

	if (vide(pile)) {
		buf = ALLOC(5,char);
		strcpy(buf,"vide");
	} else {
	buf = ALLOC((pile->tete+1)*5+1,char);
		sprintf(buf,"[");
		for (i=0;i<pile->tete+1;i++) {
			sprintf(buf,"%s%d",buf,pile->tab[i]);
			if (i==pile->tete)
				sprintf(buf,"%s]",buf);
			else
				sprintf(buf,"%s|",buf);
		}
	}
	return buf;
}

