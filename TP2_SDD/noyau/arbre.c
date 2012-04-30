#include "arbre.h"
#include "pile.h"

void arbreSupprimer(arbre_t ** arbre) {
	detruireArbre((*arbre)->lv);
	*arbre = NULL;
}

void arbreSupprimerValeur(elem_t e, arbre_t ** arbre) {
	arbreSupprimer(arbreRecherche(e,arbre));
}

arbre_t ** arbreRecherche(elem_t e, arbre_t ** arbre) {
	arbre_t ** res = NULL;
	arbre_t ** cour;
	pile_t * p;

	cour = arbre; /*Accès à la première racine*/
	p = creerPile(514); /*Création de la pile*/
	while (res == NULL && (!vide(p) || *cour != NULL)) {
		empiler((elem_t) *cour, p); /*Empiler noeud courant*/

		if ((*cour)->valeur == e) {
			res = cour;
		}

		cour = &((*cour)->lv);/*Descendre sur le lien vertical*/
		while (res == NULL && !vide(p) && cour == NULL) {
			*cour = (arbre_t*) depiler(p);/*On dépile*/
			cour = (&(*cour)->lh);/*On part sur le lien horizontal*/
		}
	}
	detruirePile(p);

	return res;
}

//TODO: dérécursifier. + gestion d'erreurs.
arbre_t * creerArbre(char * str) {
	arbre_t *nouv = NULL;
	arbre_t * racine = NULL;
	arbre_t *suiv;
	nouv = ALLOC(1, arbre_t);
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

int compterNoeuds(arbre_t* arbre) {
	int total = 0;

	return total;
}

int mesurerProfondeur(arbre_t* arbre) {
	return 0;
}

int compterFeuilles(arbre_t* arbre) {
	int total = 0;


	return total;
}

//TODO: gestion manque de memoire
void detruireArbre(arbre_t * arbre) {
	arbre_t * cour;
	arbre_t * suiv;
	pile_t * p;

	cour = arbre; /*Accès à la première racine*/
	p = creerPile(514); /*Création de la pile*/
	while (!vide(p) || cour != NULL) {
		empiler((elem_t) cour, p); /*Empiler noeud courant*/

		cour = cour->lv;/*Descendre sur le lien vertical*/
		while (!vide(p) && cour == NULL) {
			cour = (arbre_t*) depiler(p);/*On dépile*/
			suiv = cour;
			cour = cour->lh;/*On part sur le lien horizontal*/
			free(suiv);
		}
	}

}

char* arbreToString(arbre_t * arbre) {
	char* old_buf = NULL;
	char* buf = ALLOC(3, char);
	buf = "[";
	char* el = NULL;
	arbre_t * cour = NULL;

	pile_t * p;

	/* Accès à la première racine. */
	cour = arbre;

	/* Création de la pile. */
	p = creerPile(514);

	while (!vide(p) || cour != NULL) {

		if (pleine(p)) {
			printf("Pile pleine.");
			exit(EXIT_FAILURE);
		}

		/* Empiler noeud courant. */
		empiler((elem_t) cour, p);

		old_buf = buf; /* On sauvegarde l'adresse de l'ancien buffer. */
		el = elementToString(cour->valeur); /* On parse la valeur de l'élément courant. */
		buf = str_join("", buf, " ", el, NULL); /* On la fusionne avec le buffer. */

		/* On supprime l'adresse sauvée et la variable
		 * temporaire de stockage de la valeur de l'élément. */
		free(old_buf);
		free(el);

		/* Descendre sur le lien vertical. */
		cour = cour->lv;

		while (!vide(p) && cour == NULL) {
			cour = (arbre_t*) depiler(p);/*On dépile*/
			cour = cour->lh;/*On part sur le lien horizontal*/
		}
	}
	buf = str_join("", buf, " ]", NULL);
	return buf;
}

