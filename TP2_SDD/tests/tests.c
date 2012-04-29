/**************************************************************************************
 *  Ce fichier contient l'implémentation de tous les tests du programme.
 **************************************************************************************/

#include "tests.h"


result_t* test_creerPile() {
	result_t* r = creerResultat();

	// Création de la pile.
	{
		donnee_t* s;
		pile_t* pile = creerPile(3);

		creerTamponDonnee(s, TYPE_SORTIE, pileToString(pile));

		ajouterDonnee(
				assertion(r, pile->tete == -1, "Création d'une pile vide"), s);
		libererPile(pile);
	}
	return r;
}

result_t* test_empiler() {
	result_t* r = creerResultat();

	//Cas général
	{
		pile_t* pile = creerPile(10);
		donnee_t* e;
		donnee_t* s;
		int i;

		creerTamponDonnee(e, TYPE_ENTREE, pileToString(pile));

		for (i = 1; i < 4; i++) {
			empiler(i, pile);
		}

		assert_t* assert = assertion(r,
				pile->tete == 2 && pile->tab[0] == 1 && pile->tab[1] == 2
						&& pile->tab[2] == 3,
				"Cas général (empilement de 1,2,3)");

		creerTamponDonnee(s, TYPE_SORTIE, pileToString(pile));

		ajouterDonnee(assert, e);
		ajouterDonnee(assert, s);

		libererPile(pile);
	}

	//Cas de la pile pleine
	{
		pile_t* pile = creerPile(3);
		donnee_t* e;
		donnee_t* s;
		int i;

		for (i = 1; i < 4; i++) {
			empiler(i, pile);
		}
		creerTamponDonnee(e, TYPE_ENTREE, pileToString(pile));

		empiler(4, pile);
		assert_t* assert = assertion(r,
				pile->tete == 2 && pile->tab[0] == 1 && pile->tab[1] == 2
						&& pile->tab[2] == 3,
				"Cas de la pile pleine (empilement de 4)");

		creerTamponDonnee(s, TYPE_SORTIE, pileToString(pile));

		ajouterDonnee(assert, e);
		ajouterDonnee(assert, s);

		libererPile(pile);
	}

	return r;
}

result_t* test_depiler() {
	result_t* r = creerResultat();

	//Cas général
	{
		pile_t* pile = creerPile(10);
		donnee_t* e;
		donnee_t* s;
		donnee_t* l;
		int i;
		int elems[3];
		char* buf;

		for (i = 1; i < 4; i++) {
			empiler(i, pile);
		}
		creerTamponDonnee(e, TYPE_ENTREE, pileToString(pile));

		for (i = 0; i < 3; i++)
			elems[i] = depiler(pile);

		assert_t* assert = assertion(r, pile->tete = -1,
				"Cas général (3 depilements)");

		creerTamponDonnee(s, TYPE_SORTIE, pileToString(pile));

		buf = ALLOC(6,char);
		sprintf(buf, "%d,%d,%d", elems[0], elems[1], elems[2]);
		l = creerDonnee("Retour", buf);
		free(buf);

		ajouterDonnee(assert, e);
		ajouterDonnee(assert, s);
		ajouterDonnee(assert, l);

		libererPile(pile);
	}

	//Cas de la pile vide
	{
		pile_t* pile = creerPile(3);
		donnee_t* e;
		donnee_t* s;

		creerTamponDonnee(e, TYPE_ENTREE, pileToString(pile));

		depiler(pile);
		assert_t* assert = assertion(r, pile->tete == -1,
				"Cas de la pile vide");

		creerTamponDonnee(s, TYPE_SORTIE, pileToString(pile));

		ajouterDonnee(assert, e);
		ajouterDonnee(assert, s);

		libererPile(pile);
	}

	return r;
}

result_t* test_vide() {
	result_t* r = creerResultat();

	//Cas pile vide
	{
		pile_t* pile = creerPile(3);
		donnee_t* e;
		donnee_t* s;
		int res;

		creerTamponDonnee(e, TYPE_ENTREE, pileToString(pile));

		res = vide(pile);
		assert_t* assert = assertion(r, res, "Cas de la pile vide");

		creerBoolDonnee(s, TYPE_RETOUR, res);

		ajouterDonnee(assert, e);
		ajouterDonnee(assert, s);

		libererPile(pile);
	}

	//Cas de la pile non vide
	{
		pile_t* pile = creerPile(3);
		donnee_t* e;
		donnee_t* s;
		int res, i;

		for (i = 1; i < 4; i++)
			empiler(i, pile);

		creerTamponDonnee(e, TYPE_ENTREE, pileToString(pile));

		res = vide(pile);
		assert_t* assert = assertion(r, !res, "Cas de la pile non vide");

		creerBoolDonnee(s, TYPE_RETOUR, res);

		ajouterDonnee(assert, e);
		ajouterDonnee(assert, s);
		libererPile(pile);
	}
	return r;
}

result_t* test_pleine() {
	result_t* r = creerResultat();

	//Cas de la pile pleine
	{
		pile_t* pile = creerPile(3);
		donnee_t* e;
		donnee_t* s;
		int res, i;

		for (i = 1; i < 4; i++)
			empiler(i, pile);

		char* buf = pileToString(pile);
		creerTamponDonnee(e, TYPE_ENTREE, buf);

		res = pleine(pile);

		assert_t* assert = assertion(r, res, "Cas de la pile pleine");

		creerBoolDonnee(s, TYPE_RETOUR, res);

		ajouterDonnee(assert, e);
		ajouterDonnee(assert, s);
		libererPile(pile);
	}

	//Cas pile non pleine
	{
		pile_t* pile = creerPile(3);
		donnee_t* e;
		donnee_t* s;
		int res, i;

		for (i = 1; i < 3; i++)
			empiler(i, pile);

		creerTamponDonnee(e, TYPE_ENTREE, pileToString(pile));

		res = pleine(pile);
		assert_t* assert = assertion(r, !res, "Cas de la pile non pleine");

		creerBoolDonnee(s, TYPE_RETOUR, res);

		ajouterDonnee(assert, e);
		ajouterDonnee(assert, s);

		libererPile(pile);
	}
	return r;
}

/***
 *          A
 *         /
 *        B---C
 *            |
 *            D
 */
#define DEBUG_creerArbreDroit(var_name) {	\
	arbre_t D = {'d', NULL, NULL};					\
	arbre_t C = {'c', &D, NULL};					\
	arbre_t B = {'b', NULL, &C};					\
	arbre_t A = {'a', &B, NULL};					\
	var_name = &A;									\
}

/***
 *          A
 *         /
 *        B---C
 *        |
 *        D
 */
#define DEBUG_creerArbreGauche(var_name) {	\
	arbre_t D = {'d', NULL, NULL};					\
	arbre_t C = {'c', NULL, NULL};					\
	arbre_t B = {'b', &D, &C};						\
	arbre_t A = {'a', &B, NULL};					\
	var_name = &A;									\
}

result_t* test_countNodes() {
	result_t* r = creerResultat();
	{
		arbre_t* droit;
		DEBUG_creerArbreDroit(droit);

		int size;

		size = countNodes(droit);
		assert_t* a = assertion(r, size == 4, "Cas général (droit)");
		ajouterDonnee(a, creerDonneeWithInt(TYPE_DUMP, "Nombre de noeuds (droit)", size));
	}
	{
		arbre_t* gauche;
		DEBUG_creerArbreGauche(gauche);

		int size;

		size = countNodes(gauche);
		assert_t* a = assertion(r, size == 4, "Cas général (gauche)");
		ajouterDonnee(a, creerDonneeWithInt(TYPE_DUMP, "Nombre de noeuds (gauche)", size));
	}
	{
		int size = countNodes(NULL);

		assert_t* a = assertion(r, size == 0, "Cas arbre vide");
		ajouterDonnee(a, creerDonneeWithInt(TYPE_DUMP, "Nombre de noeuds", size));
	}
	return r;
}

result_t* test_deepSizeTree() {
	result_t* r = creerResultat();
	{
		arbre_t* head;
		DEBUG_creerArbreDroit(head);

		int deep = deepSizeTree(head);

		assert_t* a = assertion(r, deep == 3, "Cas général à droite");
		ajouterDonnee(a, creerDonneeWithInt(TYPE_DUMP, "Hauteur", deep));
	}
	{
		arbre_t* head;
		DEBUG_creerArbreGauche(head);

		int deep = deepSizeTree(head);

		assert_t* a = assertion(r, deep == 3, "Cas général à gauche");
		ajouterDonnee(a, creerDonneeWithInt(TYPE_DUMP, "Hauteur", deep));
	}
	{
		int deep = deepSizeTree(NULL);
		assert_t* a = assertion(r, deep == 0, "Cas arbre vide");
		ajouterDonnee(a, creerDonneeWithInt(TYPE_DUMP, "Hauteur", deep));
	}
	return r;
}

result_t* test_countLeafTree() {
	result_t* r = creerResultat();
	{
		arbre_t* head;
		DEBUG_creerArbreDroit(head);

		int nb = countLeafTree(head);

		assert_t* a = assertion(r, nb == 2, "Cas général à droite");
		ajouterDonnee(a, creerDonneeWithInt(TYPE_DUMP, "Nombre de feuille", nb));
	}
	{
		arbre_t* head;
		DEBUG_creerArbreGauche(head);

		int nb = countLeafTree(head);

		assert_t* a = assertion(r, nb == 2, "Cas général à gauche");
		ajouterDonnee(a, creerDonneeWithInt(TYPE_DUMP, "Nombre de feuille", nb));
	}
	{
		int nb = deepSizeTree(NULL);
		assert_t* a = assertion(r, nb == 0, "Cas arbre vide");
		ajouterDonnee(a, creerDonneeWithInt(TYPE_DUMP, "Nombre de feuille", nb));
	}
	return r;
}
