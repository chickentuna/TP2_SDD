#include "arbre.h"
#include "pile.h"

//TODO: dérécursifier. + gestion d'erreurs.
arbre_t * creerArbre(char * str) {
	arbre_t *nouv = NULL;
	arbre_t * racine = NULL;
	arbre_t *suiv;
	nouv = ALLOC(1,arbre_t);
	int c = 0;
	elema_t val;
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

elema_t obtenirValeur(char * str, int *c) {
	int i = *c;
	int n, k;
	char *buf;
	elema_t res;

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
	res = stringToTreeElement(buf);
	free(buf);
	return res;
}

#define BEGIN_DFS(arbre) {									\
	if (arbre != NULL) {									\
															\
		lpile_t* _pile = createLPile(arbre);				\
															\
		while (!empty(_pile)) {								\
			arbre_t* _node;									\
			pop_from(_pile, _node);							\
			while (_node != NULL) {							\
				if (_node->lh != NULL) {					\
					push_into(_pile, _node->lh);			\
				}											\

#define END_DFS()											\
				_node = _node->lv;							\
			}												\
		}													\
	}														\
}

//TODO: gestion manque de memoire
void libererArbre(arbre_t * arbre) {
	arbre_t * cour;
	arbre_t * suiv;
	pile_t * p;

	cour = arbre; /*Accès à la première racine*/
	p = initPile(514); /*Création de la pile*/
	while (!vide(p) || cour != NULL) {
		empiler((elemp_t) cour, p); /*Empiler noeud courant*/

		cour = cour->lv;/*Descendre sur le lien vertical*/
		while (!vide(p) && cour == NULL) {
			cour = (arbre_t*) depiler(p);/*On dépile*/
			suiv = cour;
			cour = cour->lh;/*On part sur le lien horizontal*/
			free(suiv);
		}
	}

}

//TODO: gestion manque de memoire
char * arbreToString(arbre_t * arbre) {
	char * buf;
	arbre_t * cour;
	int n;

	//n = compterNoeuds(arbre);
	n = 25;
	buf = ALLOC(n*5+3,char);
	sprintf(buf, "{ ");
	pile_t * p;

	cour = arbre; /*Accès à la première racine*/
	p = initPile(514); /*Création de la pile*/
	while (!vide(p) || cour != NULL) {
		empiler((elemp_t) cour, p); /*Empiler noeud courant*/

		sprintf(buf, "%s%d ", buf, (int)cour->valeur);

		cour = cour->lv;/*Descendre sur le lien vertical*/
		while (!vide(p) && cour == NULL) {
			cour = (arbre_t*) depiler(p);/*On dépile*/
			cour = cour->lh;/*On part sur le lien horizontal*/
		}
	}
	sprintf(buf, "%s}", buf);
	return buf;
}

