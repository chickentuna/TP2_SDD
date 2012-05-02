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

/*                SHEMA                         */
/*                                              */
/*             A                                */
/*             |                                */
/*             B---->C---------->D              */
/*             |                 |              */
/*             E---->F           G              */
/*             |                 |              */
/*             H---->I---->J     K---->L        */
/*                               |              */
/*                               M              */
/*                                              */
/*         VALEUR ; VERTICAL ; HORIZONTAL       */
#define DEBUG_creerArbreComplexe_static(var_name) {	\
	arbre_t M = {'m', NULL, NULL};					\
	arbre_t L = {'l', NULL, NULL};					\
	arbre_t K = {'k', &M, &L};						\
	arbre_t J = {'j', NULL, NULL};					\
	arbre_t I = {'i', NULL, &J};					\
	arbre_t H = {'h', NULL, &I};					\
	arbre_t G = {'g', &K, NULL};					\
	arbre_t F = {'f', NULL, NULL};					\
	arbre_t E = {'e', &H, &F};						\
	arbre_t D = {'d', &G, NULL};					\
	arbre_t C = {'c', NULL, &D};					\
	arbre_t B = {'b', &E, &C};						\
	arbre_t A = {'a', &B, NULL};					\
	var_name = &A;								}	\


result_t* test_initArbre() {
	result_t* r = creerResultat();
	//Cas général
	{
		donnee_t* s;
		arbre_t * a = NULL;
		int res;

		a = initArbre("1*(2*(3+4)+5)+6");

		res = (a->valeur == '1') && (a->lv->valeur == '2') && (a->lv->lv->valeur == '3')
				&& (a->lv->lv->lh->valeur == '4') && (a->lv->lh->valeur == '5')
				&& (a->lh->valeur == '6');

		assert_t* assert = assertion(r, res, "Cas général");
		creerTamponDonnee(s, TYPE_SORTIE, arbreToString(a));
		ajouterDonnee(assert, s);

		libererArbre(a);
	}
	//Cas arbre à un élément
	{
		donnee_t* s;
		arbre_t * a = NULL;
		int res;

		a = initArbre("1");
		res = (a->valeur = '1' && a->lv == NULL && a->lh == NULL);
		assert_t* assert = assertion(r, res, "Cas à un seul noeud");
		creerTamponDonnee(s, TYPE_SORTIE, arbreToString(a));
		ajouterDonnee(assert, s);
		libererArbre(a);
	}

	return r;
}

result_t* test_compterNoeuds() {
	result_t* r = creerResultat();
	{
		arbre_t* droit;
		DEBUG_creerArbreDroit_static(droit);

		int size;

		size = compterNoeuds(droit);
		assert_t* a = assertion(r, size == 4, "Cas général (droit)");
		ajouterDonnee(a,
				creerDonneeWithInt(TYPE_DUMP, "Nombre de noeuds (droit)",
						size));
	}
	{
		arbre_t* gauche;
		DEBUG_creerArbreGauche_static(gauche);

		int size;

		size = compterNoeuds(gauche);
		assert_t* a = assertion(r, size == 4, "Cas général (gauche)");
		ajouterDonnee(a,
				creerDonneeWithInt(TYPE_DUMP, "Nombre de noeuds (gauche)",
						size));
	}
	{
		arbre_t* gauche;
		DEBUG_creerArbreComplexe_static(gauche);

		int size;

		size = compterNoeuds(gauche);
		assert_t* a = assertion(r, size == 13, "Cas complexe");
		ajouterDonnee(a,
				creerDonneeWithInt(TYPE_DUMP, "Nombre de noeuds (gauche)",
						size));
	}
	{
		int size = compterNoeuds(NULL);

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

		int deep = mesurerHauteur(head);

		assert_t* a = assertion(r, deep == 3, "Cas général à droite");
		ajouterDonnee(a, creerDonneeWithInt(TYPE_DUMP, "Hauteur", deep));
	}
	{
		arbre_t* head;
		DEBUG_creerArbreGauche_static(head);

		int deep = mesurerHauteur(head);

		assert_t* a = assertion(r, deep == 3, "Cas général à gauche");
		ajouterDonnee(a, creerDonneeWithInt(TYPE_DUMP, "Hauteur", deep));
	}
	{
		arbre_t* head;
		DEBUG_creerArbreComplexe_static(head);

		int nb = mesurerHauteur(head);

		assert_t* a = assertion(r, nb == 4, "Cas complexe");
		ajouterDonnee(a,
				creerDonneeWithInt(TYPE_DUMP, "Nombre de feuille", nb));
	}
	{
		int deep = mesurerHauteur(NULL);
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

		int nb = compterFeuilles(head);

		assert_t* a = assertion(r, nb == 2, "Cas général à droite");
		ajouterDonnee(a,
				creerDonneeWithInt(TYPE_DUMP, "Nombre de feuille", nb));
	}
	{
		arbre_t* head;
		DEBUG_creerArbreGauche_static(head);

		int nb = compterFeuilles(head);

		assert_t* a = assertion(r, nb == 2, "Cas général à gauche");
		ajouterDonnee(a,
				creerDonneeWithInt(TYPE_DUMP, "Nombre de feuille", nb));
	}
	{
		arbre_t* head;
		DEBUG_creerArbreComplexe_static(head);

		int nb = compterFeuilles(head);

		assert_t* a = assertion(r, nb == 7, "Cas complexe");
		ajouterDonnee(a,
				creerDonneeWithInt(TYPE_DUMP, "Nombre de feuille", nb));
	}
	{
		int nb = mesurerHauteur(NULL);
		assert_t* a = assertion(r, nb == 0, "Cas arbre vide");
		ajouterDonnee(a,
				creerDonneeWithInt(TYPE_DUMP, "Nombre de feuille", nb));
	}
	return r;
}
