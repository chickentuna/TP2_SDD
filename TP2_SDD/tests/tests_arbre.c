/**************************************************************************************
 *  Ce fichier contient l'implémentation de tous les tests du programme.
 **************************************************************************************/

#include "tests.h"

#define DEBUG_creerArbreGauche_static(var_name) {	\
	arbre_t D = {'d', NULL, NULL};					\
	arbre_t C = {'c', NULL, NULL};					\
	arbre_t B = {'b', &D, &C};						\
	arbre_t A = {'a', &B, NULL};					\
	var_name = &A;									\
}

#define DEBUG_creerArbreDroit_static(var_name) {	\
	arbre_t D = {'d', NULL, NULL};					\
	arbre_t C = {'c', &D, NULL};					\
	arbre_t B = {'b', NULL, &C};					\
	arbre_t A = {'a', &B, NULL};					\
	var_name = &A;									\
}

result_t* test_countNodes() {
	result_t* r = creerResultat();
	{
		arbre_t* droit;
		DEBUG_creerArbreDroit_static(droit);

		int size;

		size = countNodes(droit);
		assert_t* a = assertion(r, size == 4, "Cas général (droit)");
		ajouterDonnee(a,
				creerDonneeWithInt(TYPE_DUMP, "Nombre de noeuds (droit)",
						size));
	}
	{
		arbre_t* gauche;
		DEBUG_creerArbreGauche_static(gauche);

		int size;

		size = countNodes(gauche);
		assert_t* a = assertion(r, size == 4, "Cas général (gauche)");
		ajouterDonnee(a,
				creerDonneeWithInt(TYPE_DUMP, "Nombre de noeuds (gauche)",
						size));
	}
	{
		int size = countNodes(NULL);

		assert_t* a = assertion(r, size == 0, "Cas arbre vide");
		ajouterDonnee(a,
				creerDonneeWithInt(TYPE_DUMP, "Nombre de noeuds", size));
	}
	return r;
}

result_t* test_deepSizeTree() {
	result_t* r = creerResultat();
	{
		arbre_t* head;
		DEBUG_creerArbreDroit_static(head);

		int deep = deepSizeTree(head);

		assert_t* a = assertion(r, deep == 3, "Cas général à droite");
		ajouterDonnee(a, creerDonneeWithInt(TYPE_DUMP, "Hauteur", deep));
	}
	{
		arbre_t* head;
		DEBUG_creerArbreGauche_static(head);

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
		DEBUG_creerArbreDroit_static(head);

		int nb = countLeafTree(head);

		assert_t* a = assertion(r, nb == 2, "Cas général à droite");
		ajouterDonnee(a,
				creerDonneeWithInt(TYPE_DUMP, "Nombre de feuille", nb));
	}
	{
		arbre_t* head;
		DEBUG_creerArbreGauche_static(head);

		int nb = countLeafTree(head);

		assert_t* a = assertion(r, nb == 2, "Cas général à gauche");
		ajouterDonnee(a,
				creerDonneeWithInt(TYPE_DUMP, "Nombre de feuille", nb));
	}
	{
		int nb = deepSizeTree(NULL);
		assert_t* a = assertion(r, nb == 0, "Cas arbre vide");
		ajouterDonnee(a,
				creerDonneeWithInt(TYPE_DUMP, "Nombre de feuille", nb));
	}
	return r;
}
