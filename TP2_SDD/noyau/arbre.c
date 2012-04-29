#include "arbre.h"

arbre_t * creerArbre(char * str) {
	arbre_t *nouv;
	arbre_t *suiv;
	nouv = ALLOC(1,arbre_t);
	int c = 0;
	elem_t val;
	char op;
	char *buf;

	/*if (str[c] == '(') {

	} else*/ if (str[c]!='\0') {
		val = obtenirValeur(str, &c);
		nouv->valeur = val;
		nouv->lv = NULL;
		nouv->lh = NULL;

		op = obtenirOperation(str, &c);
		buf = obtenirSuivant(str, &c);
		suiv = creerArbre(buf);
		free(buf);
		if (op == '+') {
			nouv->lh = suiv;

		} else if (op == '*') {
			nouv->lv = suiv;
		} else {
			printf("Erreur de chargement d'arbre à la position %d", c);
			exit(EXIT_FAILURE);
		}

		return nouv;
	}
	return NULL;
}


char * obtenirSuivant(char * str, int *c) {
	int i = *c;
	int n = 0, k;
	char *buf;

	while (str[*c] == ' ')
		(*c)++;

	i = *c;
	while (str[i] != '+' && str[i] != '\0') {

		if (str[i] == '(') {
			n = 1;
			while (n > 0) {
				i++;
				if (str[i] == '(')
					n++;
				if (str[i] == ')')
					n--;
			}
			i++;
		}
		i++;

	}

	buf = ALLOC(i-*c+1,char);
	n = 0;
	for (k = *c; k < i; k++) {
		if (str[k] != ' ')
			buf[n++] = str[k];
	}
	buf[n] = '\0';
	*c = i;

	return buf;
}

char obtenirOperation(char * str, int *c) {
	while (str[*c] != '*' && str[*c] != '+')
		(*c)++;

	return str[(*c)++];
}

elem_t obtenirValeur(char * str, int *c) {
	int i = *c;
	int n, k;
	char *buf;
	elem_t res;

	while (str[i] != ')' && str[i] != '+' && str[i] != '*') {
		i++;
	}
	buf = ALLOC(i-*c+1,char);
	n = 0;
	for (k = *c; k < i; k++) {
		if (str[k] != ' ')
			buf[n++] = str[k];
	}
	buf[n] = '\0';
	*c = i;
	res = stringToElement(buf);
	free(buf);
	return res;
}

int countNodes(arbre_t* arbre) {
	int c = 1;
	arbre_t* cur;
	for (cur = arbre->lv ; cur != NULL ; cur = cur->lh) {
		c += countNodes(cur);
	}
	return c;
}
