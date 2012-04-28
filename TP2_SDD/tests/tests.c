/**************************************************************************************
 * Ce fichier contient l'implémentation de tous les tests du programme.
 **************************************************************************************/

#include "tests.h"

//result_t* test_initPile() {
//
//	result_t* r = creerResultat();
//
//	// Création de la pile.
//	{
//		pile_t* pile = initPile(5);
//		assertion(r, pile->taille == 0, "Pile vide => taille 0");
//		assertion(r, pile->tete == 0, "Pile vide => tete 0");
//	}
//
//	return r;
//
//}

result_t* test_initPile() {

	result_t* r = creerResultat();

	// Création de la pile.
	{
		donnee_t* s;
		pile_t* pile = initPile(3);

		OUTPUT(s, SORTIE, pileToString(pile));

		ajouterDonnee(assertion(r, pile->tete == -1, "Création d'une pile vide"), s);
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
		int i;

		OUTPUT(e, ENTREE, pileToString(pile));

		for (i = 1; i < 4; i++) {
			empiler(i, pile);
		}

		assert_t* assert = assertion(r,
				pile->tete == 2 && pile->tab[0] == 1 && pile->tab[1] == 2
						&& pile->tab[2] == 3,
				"Cas général (empilement de 1,2,3)");

		OUTPUT(s, SORTIE, pileToString(pile));

		ajouterDonnee(assert, e);
		ajouterDonnee(assert, s);

		libererPile(pile);
	}

	//Cas de la pile pleine
	{
		pile_t* pile = initPile(3);
		donnee_t* e;
		donnee_t* s;
		int i;

		for (i = 1; i < 4; i++) {
			empiler(i, pile);
		}
		OUTPUT(e, ENTREE, pileToString(pile));

		empiler(4, pile);
		assert_t* assert = assertion(r,
				pile->tete == 2 && pile->tab[0] == 1 && pile->tab[1] == 2
						&& pile->tab[2] == 3,
				"Cas de la pile pleine (empilement de 4)");

		OUTPUT(s, SORTIE, pileToString(pile));

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
		int i;
		int elems[3];
		char *buf;

		for (i = 1; i < 4; i++) {
			empiler(i, pile);
		}
		OUTPUT(e, ENTREE, pileToString(pile));

		for (i = 0; i < 3; i++)
			elems[i] = depiler(pile);

		assert_t* assert = assertion(r, pile->tete = -1,
				"Cas général (3 depilements)");

		OUTPUT(s, SORTIE, pileToString(pile));
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
		pile_t* pile = initPile(3);
		donnee_t* e;
		donnee_t* s;

		OUTPUT(e, ENTREE, pileToString(pile));

		depiler(pile);
		assert_t* assert = assertion(r, pile->tete == -1,
				"Cas de la pile vide");

		OUTPUT(s, SORTIE, pileToString(pile));

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
		char *buf;

		OUTPUT(e, ENTREE, pileToString(pile));

		res = vide(pile);
		assert_t* assert = assertion(r, res, "Cas de la pile vide");

		if (res)
			buf = "VRAI";
		else
			buf = "FAUX";
		s = creerDonnee("Retour", buf);
		free(buf);

		ajouterDonnee(assert, e);
		ajouterDonnee(assert, s);
		libererPile(pile);
	}

	//Cas de la pile non vide
	{
		pile_t* pile = initPile(3);
		donnee_t* e;
		donnee_t* s;
		int res, i;
		char *buf;

		for (i = 1; i < 4; i++)
			empiler(i, pile);

		OUTPUT(e, ENTREE, pileToString(pile));

		res = vide(pile);
		assert_t* assert = assertion(r, !res, "Cas de la pile non vide");

		if (res)
			buf = "VRAI";
		else
			buf = "FAUX";
		s = creerDonnee("Retour", buf);
		free(buf);

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
		int res, i;
		char *buf;

		for (i = 1; i < 4; i++)
			empiler(i, pile);

		OUTPUT(e, ENTREE, pileToString(pile));

		res = pleine(pile);
		assert_t* assert = assertion(r, res, "Cas de la pile pleine");

		if (res)
			buf = "VRAI";
		else
			buf = "FAUX";
		s = creerDonnee("Retour", buf);
		free(buf);

		ajouterDonnee(assert, e);
		ajouterDonnee(assert, s);
		libererPile(pile);
	}

	//Cas pile non pleine
	{
		pile_t* pile = initPile(3);
		donnee_t* e;
		donnee_t* s;
		int res, i;
		char *buf;

		for (i = 1; i < 3; i++)
					empiler(i, pile);
		OUTPUT(e, ENTREE, pileToString(pile));

		res = pleine(pile);
		assert_t* assert = assertion(r, !res, "Cas de la pile non pleine");

		if (res)
			buf = "VRAI";
		else
			buf = "FAUX";
		s = creerDonnee("Retour", buf);
		free(buf);

		ajouterDonnee(assert, e);
		ajouterDonnee(assert, s);
		libererPile(pile);
	}
	return r;
}
