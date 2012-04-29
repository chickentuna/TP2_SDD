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

result_t* test_countNodes() {
	result_t* r = creerResultat();
	{
		arbre_t C = {'c', NULL, NULL};
		arbre_t B = {'b', NULL, &C};
		arbre_t A = {'a', &B, NULL};

		arbre_t* head = &A;

		int size = countNodes(head);

		assert_t* a = assertion(r, size == 3, "Cas général");
		ajouterDonnee(a, creerDonneeWithInt("Info", "taille arbre", size));
	}
	return r;
}
