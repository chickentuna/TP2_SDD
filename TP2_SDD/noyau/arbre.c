#include "arbre.h"

arbre_t * creerArbre(char * str) {
	arbre_t *nouv = NULL;
	arbre_t *suiv;
	nouv = ALLOC(1,arbre_t);
	int c = 0;
	elem_t val;
	char op;
	char *buf;

	while (str[c] != '\0') {
		if (str[c] == '(' || str[c] == ')') {
			c++;
		}

		val = obtenirValeur(str, &c);
		nouv->valeur = val;
		nouv->lv = NULL;
		nouv->lh = NULL;

		op = obtenirOperation(str, &c);
		if (op == '\0') {
			return nouv;
		}

		buf = obtenirSuivant(str, &c);
		suiv = creerArbre(buf);
		free(buf);
		if (op == '+') {
			nouv->lh = suiv;

		} else if (op == '*') {
			nouv->lv = suiv;
		} else {
			printf("Erreur de chargement d'arbre à la position %d : '%c'", c,
					str[c]);
			printf("String: %s", str);
			exit(EXIT_FAILURE);
		}
	}
	return nouv;
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
	while (str[*c] == ' ')
		(*c)++;
	if (str[(*c)] == '*' || str[(*c)] == '+') {
		return str[(*c)++];
	} else
		return '\0';
}

elem_t obtenirValeur(char * str, int *c) {
	int i = *c;
	int n, k;
	char *buf;
	elem_t res;

	while (str[i] != ')' && str[i] != '+' && str[i] != '*' && str[i] != '\0') {
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
	printf(">%s\n", buf);
	res = stringToElement(buf);
	free(buf);
	return res;
}

