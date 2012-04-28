#include "pile.h"

pile_t * creerPile(int taille) {
	pile_t * nouv;

	nouv = ALLOC(1, pile_t);
	nouv->tab = ALLOC(taille, elem_t);
	nouv->tete = -1;
	nouv->taille = taille;
	return nouv;
}

void empiler(elem_t element, pile_t* pile) {
	if (!pleine(pile)) {
		pile->tab[++pile->tete] = element;
	}
}

elem_t depiler(pile_t* pile) {
	if (!vide(pile)) {
		return pile->tab[pile->tete--];
	}
	return (elem_t) 0;
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

char* pileToString(pile_t * pile, strel_f to_string) {
	char* buf = NULL;
	char* old_buf = NULL;
	int i;

	if (vide(pile)) {
		buf = ALLOC(5, char);
		strcpy(buf, "vide");
	} else {
		buf = ALLOC(2, char);
		strcpy(buf, "[");
		for (i = 0; i < pile->tete + 1; i++) {

			old_buf = buf;

			char* el = (*to_string)(pile->tab[i]);
			buf = str_join("", buf, " ", el, NULL);

			free(old_buf);
			free(el);

		}
		old_buf = buf;
		buf = str_join("", buf, " ]", NULL);
		free(old_buf);
	}

	return buf;
}

