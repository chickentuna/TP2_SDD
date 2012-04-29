/**************************************************************************************
 * Implémentation des fonctions de test.
 **************************************************************************************/

/**************************************************************************************
 *          INCLUSIONS
 **************************************************************************************/

#include "testlib.h"

/**************************************************************************************
 *          IMPLEMENTATIONS
 **************************************************************************************/

donnee_t* creerDonnee(const char* type, const char* texte) {

	CHECK_PARAMETER(type, "Erreur : l'assertion n'a pas de type défini (type == NULL).");
	CHECK_PARAMETER(texte, "Erreur : l'assertion n'a pas de commentaire défini (texte == NULL).");

	donnee_t* d = ALLOC(1, donnee_t);
	d->texte = ALLOC(strlen(texte) + 1, char);
	d->type = ALLOC(strlen(type) + 1, char);

	strcpy(d->texte, texte);
	strcpy(d->type, type);

	return d;
}

donnee_t* creerDonneeWithInt(const char* type, const char* texte, int v) {
	char* res = ALLOC(MAX_NBCAR_INT + strlen(texte) + 1, char);
	sprintf(res, "%s (v=%d)", texte, v);
	donnee_t* d = creerDonnee(type, res);
	free(res);
	return d;
}

void detruireDonnee(donnee_t* d) {

	CHECK_PARAMETER(d, "Destruction de donnée impossible : donnée nulle.");

	free(d->texte);
	free(d->type);
	free(d);
}

#define ANONYME "anonyme"

assert_t* creerAssertion(int condition, const char* nom) {

	CHECK_PARAMETER(nom, "Erreur : l'assertion n'a pas de nom défini (nom == NULL).");

	assert_t* a = ALLOC(1, assert_t);
	a->nom = ALLOC(strlen(nom) + 1, char);
	strcpy(a->nom, nom);
	a->result = condition;
	a->donnees = ALLOC(DATA_LIST_MAX_SIZE, donnee_t*);
	a->size = 0;
	return a;
}

void detruireAssertion(assert_t* a) {

	CHECK_PARAMETER(a, "Tentative de destruction d'une assertion nulle.");

	int i;
	for (i = 0; i < a->size; i++) {
		detruireDonnee(a->donnees[i]);
	}
	free(a->donnees);
	free(a->nom);
	free(a);
}

result_t* creerResultat() {
	result_t* r = ALLOC(1, result_t);
	r->asserts = ALLOC(ASSERTION_LIST_MAX_SIZE, assert_t*);
	r->size = 0;
	return r;
}

void detruireResultat(result_t* r) {

	CHECK_PARAMETER(r, "Tentative de destruction d'un resultat nulle.");

	int i;
	for (i = 0; i < r->size; i++) {
		detruireAssertion(r->asserts[i]);
	}
	free(r->asserts);
	free(r);
}

void creerTest(test_t** prec, fonction_test f, const char* name) {

	test_t* t = ALLOC(1, test_t);

	t->fonction = f;
	t->nom = ALLOC(strlen(name) + 1, char);
	strcpy(t->nom, name);

	t->suiv = *prec;
	*prec = t;
}

void detruireTests(test_t* head) {
	if (head != NULL) {
		detruireTests(head->suiv);
		free(head->nom);
		free(head);
	}
}

void ajouterDonnee(assert_t* a, donnee_t* d) {
	if (a != NULL && d != NULL && a->size < DATA_LIST_MAX_SIZE) {
		a->donnees[a->size++] = d;
	} else {
		//TODO: gestion de l'erreur ?
	}
}

void ajouterAssertion(result_t* res, assert_t* a) {
	if (res != NULL && a != NULL && res->size < ASSERTION_LIST_MAX_SIZE) {
		res->asserts[res->size++] = a;
	} else {
		//TODO: gestion de l'erreur ?
	}
}

assert_t* assertion(result_t* res, int condition, const char* nom) {
	assert_t* a = creerAssertion(condition, nom);
	ajouterAssertion(res, a);
	return a;
}

int executerAssertions(result_t* r, flag_t f) {
	int result = VRAI;
	FOR_EACH(r->asserts, r->size, a,
			char jeton = a->result ? ' ' : 'X'; result &= a->result; if (!(f & FLAG_HIDE_ASSERTS)) printf("  %c %d] \"%s\" => %s\n", jeton, compteur + 1, a->nom, a->result ? "réussi" : "échoué"); FOR_EACH(a->donnees, a->size, d, if (!(f & FLAG_HIDE_DATAS)) printf("      [%s] %s\n", d->type, d->texte); ))
	detruireResultat(r);
	return result;
}

void executerTests(test_t* test, flag_t f) {
	static int i = 1;

	if (test != NULL) {
		printf("++ ----------------- TEST n°%d [%s] ----------------- ++\n",
				i++, test->nom);

		if (executerAssertions((*test->fonction)(), f)) {
			printf("    ETAT FINAL : SUCCES\n");
		} else {
			printf("  X ETAT FINAL : ECHEC\n");
		}

		executerTests(test->suiv, f);
	}
}
