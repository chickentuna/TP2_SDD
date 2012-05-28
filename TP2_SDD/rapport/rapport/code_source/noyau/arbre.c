#include "arbre.h"
#include "pile.h"

arbre_t * initArbre(char * str) {
	/*
	 * str - La chaîne de caractères
	 */

	arbre_t *nouv = NULL; /* nouv - pointeur sur le sous arbre courant */
	arbre_t * racine = NULL; /* racine - pointeur sur la racine de l'arbre à renvoyer */
	arbre_t *suiv; /* suiv - pointeur sur le noeud à lier à la racine */
	int c = 0; /* c - Compteur d'indice de position dans la chaîne de caractères. */
	char val; /* val - Caractère de la valeur du noeud courant */
	char op; /* op - Caractère de l'opération suivante */
	char *buf; /* buf - Chaîne de caractères tampon pour initialiser les sous-arbres*/

	/* Allocation de la racine */
	nouv = ALLOC(1, arbre_t);

	/*On place le compteur au premier caractère de l'arbre*/
	while (str[c] == '(' || str[c] == ')') {
		c++;
	}
	/*S'il n'y a rien, l'arbre est vide*/
	if (str[c] == '\0')
		return NULL;

	/*On lit la racine de l'arbre pour initialiser la structure*/
	val = obtenirValeur(str, &c);
	nouv->valeur = val;
	nouv->lv = NULL;
	nouv->lh = NULL;
	/*On commence la construction des liens à la racine de l'arbre*/
	racine = nouv;

	/*On parcours la chaine de caractères*/
	while (str[c] != '\0') {

		/*On récupère la première opération à effectuer*/
		op = obtenirOperation(str, &c);
		/*Pas d'opérations => le noeud est une feuille*/
		if (op == '\0') {
			/*On renvoi le noued car il n'y pas de liens à construire [correspond à la racine du sous arbre courant]*/
			return nouv;
		}

		/*On récupère maintenant le sous arbre suivant à lier au noeud courant*/
		buf = obtenirSuivant(str, &c);
		suiv = initArbre(buf);
		free(buf);

		/*On construit le lien*/
		if (op == '+') {
			/*Dans le cas d'un lien horizontal, la prochaine opération portera sur le noeud suivant*/
			nouv->lh = suiv;

			/*On change le noeud courant, car on a changé de sous arbre*/
			nouv = suiv;
		} else if (op == '*') {
			/*Dans le cas d'un lien vertical, la prochaine opération portera sur le noeud courant*/
			nouv->lv = suiv;
		} else {
			/*Si l'operation n'est pas reconnue, il y a une erreur dans la chaîne de caractères*/
			printf("Erreur de chargement d'arbre à la position %d : '%c'", c,
					str[c]);
			printf("String: %s", str);
			exit(EXIT_FAILURE);
		}
		/*Le lien a été construit, on doit donc récuperer l'operation suivante*/
	}

	/*La chaîne a été entièrement parcourue, on renvoie la racine de l'arbre*/
	return racine;
}

/* Recuperation de la sous-chaine suivante correspondant au sous-arbre suivant dans la chaine de caractères */
char * obtenirSuivant(char * str, int *c) {
	/*
	 * c - Compteur d'indice de position dans la chaîne de caractères.
	 * str - La chaîne de caractères
	 */
	int i = *c; /* i = compteur de position pour la sous-chaine */
	int n = 0, k; /* n = compteur de parenthèse ouvrante; k = compteur de recopie pour la sous chaine à renvoyer */
	char *buf; /* buf = chaine de caractère tampon pour la sous-chaine à renvoyer */

	i = *c;
	/*On parcours la chaine de caractères tant qu'il porte sur le sous-arbre indiqué par le compteur c*/
	/*Le sous arbre est terminé quand on atteint le lien horizontal de la racine [peut etre NULL] dans la chaîne*/
	while (str[i] != '+' && str[i] != '\0') {

		if (str[i] == '(') {
			/* S'il y a une parenthèse ouvrante, on cherche la parenthèse fermante correspondante */
			n = 1;
			while (n > 0) { /* On continue d'incrémenter tant qu'il reste des parenthèses fermantes à trouver */
				i++;
				if (str[i] == '(')
					n++;
				if (str[i] == ')')
					n--;
			}
		}
		i++;
	}

	/* On alloue une chaine de taille identique à la sous-chaîne [i-c+1] */
	buf = ALLOC(i-*c+1,char);

	/*On recopie la sous-chaine dans la chaîne de caractères tampon*/
	for (k = *c; k < i; k++) {
		buf[k - (*c)] = str[k];
	}
	buf[k - (*c)] = '\0';

	/*On place le compteur de position de la chaîne à la fin du sous arbre*/
	*c = i;
	/* On renvoie la sous-chaine [correspondant au sous arbre suivant] */
	return buf;
}

/* Récupération de l'opération suivante à effectuer sur l'arbre dans une chaine de caractère */
char obtenirOperation(char * str, int *c) {
	/*
	 * c - Compteur d'indice de position dans la chaîne de caractères.
	 * str - La chaîne de caractères
	 */

	/*On test si on se trouve sur une feuille*/
	if (str[(*c)] == '*' || str[(*c)] == '+') {
		/*On renvoie le caractère de l'operation*/
		return str[(*c)++];
	} else {
		/*On renvoi 'fin de chaîne' pour indiquer qu'il n'y a pas d'operation [donc pas de liens] */
		return '\0';
	}
}

/* Récupération de la valeur du noeud suivant de l'arbre dans une chaine de caractère */
char obtenirValeur(char * str, int *c) {
	/*
	 * c - Compteur d'indice de position dans la chaîne de caractères.
	 * str - La chaîne de caractères
	 */

	/*On avance dans la chaîne de caractères jusqu'à dépassement du caractère  [ on survole les '(' ]*/
	while (str[*c] != ')' && str[*c] != '+' && str[*c] != '*' && str[*c] != '\0') {
		(*c)++;
	}
	/*On renvoie le caractère dépassé*/
	return str[(*c) - 1];
}

void arbreSupprimer(arbre_t ** arbre) {
	arbre_t* prec;

	/*Suppresion avec élagage*/
	if (*arbre != NULL) {
		prec = *arbre;
		*arbre = (*arbre)->lh;
		prec->lh = NULL;
	}
	libererArbre(prec);
}

void arbreSupprimerValeur(char e, arbre_t ** arbre) {
	arbre_t ** prec = arbreRecherche(e, arbre);
	if (prec != NULL)
		arbreSupprimer(prec);
}

arbre_t ** arbreRecherche(char e, arbre_t ** arbre) {
	arbre_t ** prec;
	arbre_t * cour;
	pile_t * p;
	int fin = FAUX;

	prec = arbre; /*Accès à la première racine*/
	cour = *arbre;
	p = initPile(514); /*Création de la pile*/
	while (!fin) {
		while (cour != NULL && !fin) {
			if (cour->valeur == e) {
				fin = VRAI;
			} else {
				if (pleine(p)) {
					erreur("Pile pleine.");
				}
				empiler((elem_t) cour, p); /*Empiler noeud courant*/
				prec = &(cour->lv);
				cour = cour->lv;
			}
		}
		if (!vide(p) && !fin) {
			cour = (arbre_t*) depiler(p);/*On dépile*/
			prec = &(cour->lh);
			cour = cour->lh;/*On part sur le lien horizontal*/
		} else {
			fin = VRAI;
		}
	}
	libererPile(p);

	return prec;
}

int similaire(arbre_t* a1, arbre_t* a2) {
	int res = 1;
	arbre_t * cour;
	arbre_t * cour2;
	pile_t * p;
	pile_t * p2;

	cour = a1; /*Accès à la première racine*/
	cour2 = a2;
	p = initPile(514); /*Création de la pile*/
	p2 = initPile(514); /*Création de la pile*/

	while (!vide(p) || cour != NULL) {
		empiler(cour, p); /*Empiler noeud courant*/
		empiler(cour2, p2);
		cour2 = cour2->lv;
		cour = cour->lv;/*Descendre sur le lien vertical*/
		if ((cour==NULL && cour2!=NULL) || (cour2==NULL && cour!=NULL))
					return 0;
		while (!vide(p) && cour == NULL) {
			cour = (arbre_t*) depiler(p);/*On dépile*/
			cour2 = (arbre_t*) depiler(p2);
			cour = cour->lh;/*On part sur le lien horizontal*/
			cour2 = cour2->lh;
			if ((cour==NULL && cour2!=NULL) || (cour2==NULL && cour!=NULL))
								return 0;
		}
	}
	libererPile(p);
	libererPile(p2);
	return res;

}

int compterNoeuds(arbre_t* arbre) {
	int total = 0;
	arbre_t * cour;
	pile_t * p;

	cour = arbre; /*Accès à la première racine*/
	p = initPile(514); /*Création de la pile*/
	while (!vide(p) || cour != NULL) {
		if (pleine(p)) {
			erreur("Pile pleine.");
		}
		empiler(cour, p); /*Empiler noeud courant*/

		total++;

		cour = cour->lv;/*Descendre sur le lien vertical*/
		while (!vide(p) && cour == NULL) {
			cour = (arbre_t*) depiler(p);/*On dépile*/
			cour = cour->lh;/*On part sur le lien horizontal*/
		}
	}
	libererPile(p);
	return total;
}

int mesurerHauteur(arbre_t* arbre) {
	arbre_t * cour;
	pile_t * p;
	int profondeur = 0;
	int res = 0;

	if (arbre == NULL)
		return 0;

	cour = arbre; /*Accès à la première racine*/
	p = initPile(514); /*Création de la pile*/
	while (!vide(p) || cour != NULL) {
		if (pleine(p)) {
			erreur("Pile pleine.");
		}
		empiler((elem_t) cour, p); /*Empiler noeud courant*/

		profondeur++;
		if (res < profondeur)
			res++;

		cour = cour->lv;/*Descendre sur le lien vertical*/
		while (!vide(p) && cour == NULL) {
			cour = (arbre_t*) depiler(p);/*On dépile*/
			profondeur--;
			cour = cour->lh;/*On part sur le lien horizontal*/
		}
	}
	libererPile(p);
	return res - 1;
}

int compterFeuilles(arbre_t* arbre) {
	int total = 0;
	arbre_t * cour;
	pile_t * p;

	if (arbre == NULL)
		return 0;

	cour = arbre; /*Accès à la première racine*/
	p = initPile(514); /*Création de la pile*/
	while (!vide(p) || cour != NULL) {
		if (pleine(p)) {
			erreur("Pile pleine.");
		}
		empiler((elem_t) cour, p); /*Empiler noeud courant*/

		if (cour->lv == NULL)
			total++;

		cour = cour->lv;/*Descendre sur le lien vertical*/
		while (!vide(p) && cour == NULL) {
			cour = (arbre_t*) depiler(p);/*On dépile*/
			cour = cour->lh;/*On part sur le lien horizontal*/
		}
	}
	libererPile(p);
	return total;
}

void libererArbre(arbre_t * arbre) {
	arbre_t * cour;
	arbre_t * suiv;
	pile_t * p;

	cour = arbre; /*Accès à la première racine*/
	p = initPile(514); /*Création de la pile*/
	while (!vide(p) || cour != NULL) {

		if (pleine(p)) {
			erreur("Pile pleine.");
		}

		empiler((elem_t) cour, p); /*Empiler noeud courant*/

		cour = cour->lv;/*Descendre sur le lien vertical*/
		while (!vide(p) && cour == NULL) {
			cour = (arbre_t*) depiler(p);/*On dépile*/
			suiv = cour;
			cour = cour->lh;/*On part sur le lien horizontal*/
			free(suiv);
		}
	}
	libererPile(p);
}

char* arbreToString(arbre_t * arbre) {
	char* old_buf = NULL;
	char* buf = ALLOC(3, char);
	char* el = NULL;
	arbre_t * cour = NULL;
	pile_t * p;

	buf[0] = '[';
	buf[1] = '\0';

	/* Accès à la première racine. */
	cour = arbre;

	/* Création de la pile. */
	p = initPile(514);

	while (!vide(p) || cour != NULL) {
		if (pleine(p)) {
			erreur("Pile pleine");
		}

		/* Empiler noeud courant. */
		empiler(cour, p);

		old_buf = buf; /* On sauvegarde l'adresse de l'ancien buffer. */

		el = ALLOC(2,char);
		el[0] = cour->valeur;
		el[1] = '\0';

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
	old_buf = buf;
	buf = str_join("", buf, " ]", NULL);
	free(old_buf);
	libererPile(p);
	return buf;
}

