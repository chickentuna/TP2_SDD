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

		res = (a->valeur == '1') && (a->lv->valeur == '2')
				&& (a->lv->lv->valeur == '3') && (a->lv->lv->lh->valeur == '4')
				&& (a->lv->lh->valeur == '5') && (a->lh->valeur == '6');

		assert_t* assert = assertion(r, res, "Cas général");
		
		creerTamponDonnee(s, TYPE_SORTIE, arbreToString(a));
		ajouterDonnee(assert, s);
		libererArbre(a);
	}
	//Cas arbre à un élément
	/*{
		donnee_t* s;
		arbre_t * a = NULL;
		int res;

		a = initArbre("1");
		res = (a->valeur == '1' && a->lv == NULL && a->lh == NULL);
		assert_t* assert = assertion(r, res, "Cas à un seul noeud");
		creerTamponDonnee(s, TYPE_SORTIE, arbreToString(a));
		ajouterDonnee(assert, s);
		libererArbre(a);
	}*/

	return r;
}

result_t* test_arbreRecherche() {
	result_t* r = creerResultat();
	//Cas général
	{
		arbre_t * a = NULL;
		arbre_t ** prec;
		assert_t* assert;
		donnee_t* s;

		a = initArbre("a*(b*(c+d)+e)+f");

		prec = arbreRecherche('e', &a);

		assert = assertion(r, (*prec)->valeur == 'e',
				"Cas général (recherche de e)");

		creerTamponDonnee(s,TYPE_RETOUR, arbreToString(*prec));

		ajouterDonnee(assert, creerDonnee(TYPE_ENTREE, "a*(b*(c+d)+e)+f"));
		ajouterDonnee(assert, s);

		libererArbre(a);
	}
	//Cas introuvable
	{
		arbre_t * a = NULL;
		arbre_t ** prec;
		assert_t* assert;
		donnee_t* s;

		a = initArbre("a*(b*(c+d)+e)+f");

		prec = arbreRecherche('g', &a);

		assert = assertion(r, *prec == NULL, "Cas non trouvé (recherche de g)");

		creerTamponDonnee(s,TYPE_RETOUR, arbreToString(*prec));

		ajouterDonnee(assert, creerDonnee(TYPE_ENTREE, "a*(b*(c+d)+e)+f"));
		ajouterDonnee(assert, s);

		libererArbre(a);
	}
	return r;
}

result_t* test_arbreSupprimerValeur() {
	result_t* r = creerResultat();
	//Cas général
	{
		arbre_t * a = NULL;
		assert_t* assert;
		donnee_t* s;

		a = initArbre("a*(b*(c+d)+e)+f");

		
		arbreSupprimerValeur('b', &a);
		creerTamponDonnee(s, TYPE_RETOUR, arbreToString(a));

		assert = assertion(r, a->lv == NULL, "Cas général (suppresion de b)");

		ajouterDonnee(assert, creerDonnee(TYPE_ENTREE, "a*(b*(c+d)+e)+f"));
		ajouterDonnee(assert, s);

		libererArbre(a);
	}
	return r;
}
result_t* test_arbreSupprimer() {
	result_t* r = creerResultat();
	//Cas général
	{
		arbre_t * a = NULL;
		assert_t* assert;
		donnee_t* s;

		a = initArbre("a*(b*(c+d)+e)+f");

		arbreSupprimer(&(a->lv));
		creerTamponDonnee(s, TYPE_RETOUR, arbreToString(a));

		assert = assertion(r, a->lv == NULL, "Cas général (suppresion de b)");

		ajouterDonnee(assert, creerDonnee(TYPE_ENTREE, "a*(b*(c+d)+e)+f"));
		ajouterDonnee(assert, s);

		libererArbre(a);
	}
	return r;
}

result_t* test_compterNoeuds() {
	result_t* r = creerResultat();
	{
		arbre_t* arbre;
		donnee_t* e;
		DEBUG_creerArbreDroit_static(arbre);
		int size;

		creerTamponDonnee(e, TYPE_ENTREE, "a*(b+c*d)");

		size = compterNoeuds(arbre);
		assert_t* a = assertion(r, size == 4, "Cas général (droit)");
		ajouterDonnee(a, e);
		ajouterDonnee(a,
				creerDonneeWithInt(TYPE_RETOUR, "Nombre de noeuds", size));
	}
	{
		arbre_t* gauche;
		DEBUG_creerArbreGauche_static(gauche);

		int size;

		size = compterNoeuds(gauche);
		assert_t* a = assertion(r, size == 4, "Cas général (gauche)");

		ajouterDonnee(a, creerDonnee(TYPE_ENTREE, "a*(b*d+c)"));
		ajouterDonnee(a,
				creerDonneeWithInt(TYPE_RETOUR, "Nombre de noeuds", size));
	}
	{
		arbre_t* arbre;
		int size;
		DEBUG_creerArbreComplexe_static(arbre);

		size = compterNoeuds(arbre);
		assert_t* a = assertion(r, size == 13, "Cas complexe");
		ajouterDonnee(a,
				creerDonnee(TYPE_ENTREE, "a*(b*(e*(h+i+j)+f)+c+d*g*(k*m+l))"));
		ajouterDonnee(a,
				creerDonneeWithInt(TYPE_RETOUR, "Nombre de noeuds", size));
	}
	{
		int size = compterNoeuds(NULL);

		assert_t* a = assertion(r, size == 0, "Cas arbre vide");
		ajouterDonnee(a, creerDonnee(TYPE_ENTREE, "null"));
		ajouterDonnee(a,
				creerDonneeWithInt(TYPE_RETOUR, "Nombre de noeuds", size));
	}
	return r;
}

result_t* test_mesurerHauteur() {
	result_t* r = creerResultat();
	{
		arbre_t* head;
		DEBUG_creerArbreDroit_static(head);

		int deep = mesurerHauteur(head);

		assert_t* a = assertion(r, deep == 2, "Cas général à droite");
		ajouterDonnee(a, creerDonnee(TYPE_ENTREE, "a*(b+c*d)"));
		ajouterDonnee(a, creerDonneeWithInt(TYPE_RETOUR, "Hauteur", deep));
	}
	{
		arbre_t* head;
		DEBUG_creerArbreGauche_static(head);

		int deep = mesurerHauteur(head);

		assert_t* a = assertion(r, deep == 2, "Cas général à gauche"); //TODO: pas tres clair
		ajouterDonnee(a, creerDonnee(TYPE_ENTREE, "a*(b*d+c)"));
		ajouterDonnee(a, creerDonneeWithInt(TYPE_RETOUR, "Hauteur", deep));
	}
	{
		arbre_t* head;
		DEBUG_creerArbreComplexe_static(head);

		int nb = mesurerHauteur(head);

		assert_t* a = assertion(r, nb == 4, "Cas complexe");
		ajouterDonnee(a,
				creerDonnee(TYPE_ENTREE, "a*(b*(e*(h+i+j)+f)+c+d*g*(k*m+l))"));
		ajouterDonnee(a, creerDonneeWithInt(TYPE_RETOUR, "Hauteur", nb));
	}
	{
		int deep = mesurerHauteur(NULL);
		assert_t* a = assertion(r, deep == 0, "Cas arbre vide");
		ajouterDonnee(a, creerDonnee(TYPE_ENTREE, "null"));
		ajouterDonnee(a, creerDonneeWithInt(TYPE_RETOUR, "Hauteur", deep));
	}
	return r;
}

result_t* test_compterFeuilles() {
	result_t* r = creerResultat();
	{
		arbre_t* head;
		DEBUG_creerArbreDroit_static(head);

		int nb = compterFeuilles(head);

		assert_t* a = assertion(r, nb == 2, "Cas général à droite");
		ajouterDonnee(a, creerDonnee(TYPE_ENTREE, "a*(b+c*d)"));
		ajouterDonnee(a,
				creerDonneeWithInt(TYPE_RETOUR, "Nombre de feuille", nb));
	}
	{
		arbre_t* head;
		DEBUG_creerArbreGauche_static(head);

		int nb = compterFeuilles(head);

		assert_t* a = assertion(r, nb == 2, "Cas général à gauche");
		ajouterDonnee(a, creerDonnee(TYPE_ENTREE, "a*(b*d+c)"));
		ajouterDonnee(a,
				creerDonneeWithInt(TYPE_RETOUR, "Nombre de feuilles", nb));
	}
	{
		arbre_t* head;
		DEBUG_creerArbreComplexe_static(head);

		int nb = compterFeuilles(head);

		assert_t* a = assertion(r, nb == 7, "Cas complexe");
		ajouterDonnee(a,
				creerDonnee(TYPE_ENTREE, "a*(b*(e*(h+i+j)+f)+c+d*g*(k*m+l))"));
		ajouterDonnee(a,
				creerDonneeWithInt(TYPE_RETOUR, "Nombre de feuilles", nb));
	}
	{
		int nb = compterFeuilles(NULL);
		assert_t* a = assertion(r, nb == 0, "Cas arbre vide");
		ajouterDonnee(a, creerDonnee(TYPE_ENTREE, "null"));
		ajouterDonnee(a,
				creerDonneeWithInt(TYPE_RETOUR, "Nombre de feuilles", nb));
	}
	return r;
}

