#include "arbre.h"
#include "pile.h"

arbre_t * creerArbre(char * str) {
	arbre_t *nouv = NULL;
	arbre_t * racine = NULL;
	arbre_t *suiv;
	nouv = ALLOC(1,arbre_t);
	int c = 0;
	elem_t val;
	char op;
	char *buf;

	while (str[c] == '(' || str[c] == ')') {
		c++;
	}
	if (str[c] == '\0')
		return NULL;

	val = obtenirValeur(str, &c);
	nouv->valeur = val;
	nouv->lv = NULL;
	nouv->lh = NULL;
	racine = nouv;

	while (str[c] != '\0') {

		op = obtenirOperation(str, &c);
		if (op == '\0') {
			return nouv;
		}

		buf = obtenirSuivant(str, &c);
		suiv = creerArbre(buf);
		free(buf);
		if (op == '+') {
			nouv->lh = suiv;
			nouv = suiv;

		} else if (op == '*') {
			nouv->lv = suiv;
		} else {
			printf("Erreur de chargement d'arbre à la position %d : '%c'", c,
					str[c]);
			printf("String: %s", str);
			exit(EXIT_FAILURE);
		}

	}
	return racine;
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
	res = stringToElement(buf);
	free(buf);
	return res;
}


int countNodes(arbre_t* arbre) {
	int c = 0;
	arbre_t* cur;

	if (arbre != NULL) {
		for (cur = arbre; cur != NULL; cur = cur->lh) {
			c += countNodes(cur->lv) + 1;
		}
	}

	return c;
}

int deepSizeTree(arbre_t* arbre) {
	int size = 0;
	int total = 0;
	arbre_t* cur_lv;
	arbre_t* cur_lh;

	for (cur_lh = arbre; cur_lh != NULL; cur_lh = cur_lh->lh) {
		size = 1;
		for (cur_lv = cur_lh; cur_lv != NULL; cur_lv = cur_lv->lv) {
			size++;
		}
		if (size > total) {
			total = size;
		}
	}

	return total;
}

int countLeafTree(arbre_t* arbre) {
	int total = 0;
	arbre_t* cur_lv;
	arbre_t* cur_lh;

	for (cur_lh = arbre; cur_lh != NULL; cur_lh = cur_lh->lh) {
		cur_lv = cur_lh;
		while (cur_lv != NULL) {
			cur_lv = cur_lv->lv;
		}
		total++;
	}

	return total;
}

void detruireArbre(arbre_t * arbre) {
	/*TODO:Parcours d'un arbre en itératif avec free() dans l'ordre postfixe*/
}

char * arbreToString(arbre_t * arbre) {
	char * buf;
	arbre_t * cour;
	int n;

	n = countNodes(arbre);
	buf = ALLOC(n*5+3,char);
	sprintf(buf,"{ ");
	pile_t * p; //TODO:Ceci est une pile d'arbre.

	cour = arbre; /*Accès à la première racine*/
	p = creerPile(514); /*Création de la pile*/
	while (!vide(p) || cour != NULL) {
		empiler((elem_t)cour,p); /*Empiler noeud courant*/

		sprintf(buf,"%s%d ",buf,cour->valeur);

		cour = cour->lv;/*Descendre sur le lien vertical*/
		while (!vide(p) && cour == NULL) {
			cour = (arbre_t*) depiler(p);/*On dépile*/
			cour = cour->lh;/*On part sur le lien horizontal*/
		}
	}
	sprintf(buf,"%s}",buf);
	return buf;
}




