/**************************************************************************************
 *  Ce fichier contient toutes les fonctions qui servent à tester le programme.
 **************************************************************************************/

#ifndef TESTLIB_H_
#define TESTLIB_H_

/**************************************************************************************
 *          INCLUSIONS
 **************************************************************************************/

#include "stdio.h"
#include "stdlib.h"
#include "string.h"

/**************************************************************************************
 *          MACROS
 **************************************************************************************/

#undef ALLOC
#define ALLOC(_n,_t) (_t*) malloc(_n*sizeof(_t))

#define FOR_EACH(list, size, el, actions) {					\
	int compteur;											\
	if (list != NULL && size > 0) {							\
		for (compteur = 0 ; compteur < size ; compteur++) {	\
			typeof(list[0]) el = list[compteur];			\
			actions											\
		}													\
	}														\
}

#define OUTPUT(var,data,str) {		\
	char *buf = str;				\
	var = creerDonnee(data, buf);	\
	free(buf);						\
}

#define creerTamponDonnee(donnee, type, texte) {	\
	char *tampon = texte;							\
	donnee = creerDonnee(type, tampon);				\
	free(tampon);									\
}

#define ENTREE "Entrée"
#define SORTIE "Sortie"

#define VRAI 1
#define FAUX 0

#define REUSSI 1
#define ECHOUE 0

#define ASSERTION_LIST_MAX_SIZE 10
#define DATA_LIST_MAX_SIZE 10

typedef unsigned char flag_t;

#define FLAG_EMPTY					0
#define FLAG_HIDE_ASSERTS			1
#define FLAG_HIDE_DATAS				2

/**************************************************************************************
 *          STRUCTURES & TYPES
 **************************************************************************************/

typedef struct donnee_s {
	char* type;
	char* texte;
} donnee_t;

typedef struct assert_s {
	int result;
	char* nom;
	donnee_t** donnees;
	int size;
} assert_t;

typedef struct result_s {
	assert_t** asserts;
	int size;
} result_t;

/* Pointeur de fonction pour les tests. */
typedef result_t*(*fonction_test)(void);

typedef struct test_s {
	fonction_test fonction;
	char* nom;
	struct test_s* suiv;
} test_t;

/**
 * Ce template permet d'appeller la fonction de test qui correspond à la
 * fonction passée en paramètre.
 * @param
 * 	__func : nom de la fonction à tester.
 * @renvoie
 * 	Un pointeur vers test_t.
 */
#define AJOUTE_TEST(__head, __func) creerTest(__head, test_##__func, #__func)

/**************************************************************************************
 *          PROTOTYPES
 **************************************************************************************/

donnee_t* creerDonnee(const char* type, const char* texte);
void detruireDonnee(donnee_t* d);
assert_t* creerAssertion(int condition, const char* nom);
void detruireAssertion(assert_t* a);
result_t* creerResultat();
void detruireResultat(result_t* r);

void ajouterDonnee(assert_t* a, donnee_t* d);
void ajouterAssertion(result_t* res, assert_t* a);
assert_t* assertion(result_t* res, int condition, const char* nom);

void creerTest(test_t** prec, fonction_test f, const char* name);
void detruireTests(test_t* head);
void executerTests(test_t* test, flag_t f);

#endif
