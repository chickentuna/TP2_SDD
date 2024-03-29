#include "tests.h"

result_t* test_initPile() {
	result_t* r = creerResultat();

	// Création de la pile.
	{
		donnee_t* s;
		pile_t* pile = initPile(3);

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
		pile_t* pile = initPile(10);
		donnee_t* e;
		donnee_t* s;
		long i;

		creerTamponDonnee(e, TYPE_ENTREE, pileToString(pile));

		for (i = 1; i < 4; i++) {
			empiler((elem_t)i, pile);
		}

		assert_t* assert = assertion(
				r,
				pile->tete == 2 && pile->tab[0] == (elem_t)1 && pile->tab[1] == (elem_t)2
						&& pile->tab[2] == (elem_t)3,
				"Cas général (empilement de 1,2,3)");

		creerTamponDonnee(s, TYPE_SORTIE, pileToString(pile));

		ajouterDonnee(assert, e);
		ajouterDonnee(assert, s);

		libererPile(pile);
	}

	//Cas de la pile pleine
	{
		pile_t* pile = initPile(3);
		donnee_t* e;
		donnee_t* s;
		long i;

		for (i = 1; i < 4; i++) {
			empiler((elem_t)i, pile);
		}creerTamponDonnee(e, TYPE_ENTREE, pileToString(pile));

		empiler((elem_t)4, pile);
		assert_t* assert = assertion(
				r,
				pile->tete == 2 && pile->tab[0] == (elem_t)1 && pile->tab[1] == (elem_t)2
						&& pile->tab[2] == (elem_t)3,
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
		pile_t* pile = initPile(10);
		donnee_t* e;
		donnee_t* s;
		donnee_t* l;
		long i;
		long elems[3];
		char* buf;

		for (i = 1; i < 4; i++) {
			empiler((elem_t)i, pile);
		}creerTamponDonnee(e, TYPE_ENTREE, pileToString(pile));

		for (i = 0; i < 3; i++)
			elems[i] = (long)depiler(pile);

		assert_t* assert = assertion(r, pile->tete = -1,
				"Cas général (3 depilements)");

		creerTamponDonnee(s, TYPE_SORTIE, pileToString(pile));

		buf = ALLOC(6,char);
		sprintf(buf, "%ld,%ld,%ld", elems[0], elems[1], elems[2]);
		l = creerDonnee("Retour", buf);
		free(buf);

		ajouterDonnee(assert, e);
		ajouterDonnee(assert, s);
		ajouterDonnee(assert, l);

		libererPile(pile);
	}

	//Cas de la pile vide
	{
		pile_t* pile = initPile(3);
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
		pile_t* pile = initPile(3);
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
		pile_t* pile = initPile(3);
		donnee_t* e;
		donnee_t* s;
		int res;
		long i;

		for (i = 1; i < 4; i++)
			empiler((elem_t)i, pile);

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
		pile_t* pile = initPile(3);
		donnee_t* e;
		donnee_t* s;
		int res;
		long i;

		for (i = 1; i < 4; i++)
			empiler((elem_t)i, pile);

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
		pile_t* pile = initPile(3);
		donnee_t* e;
		donnee_t* s;
		int res;
		long i;

		for (i = 1; i < 3; i++)
			empiler((elem_t)i, pile);

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
