#ifndef LIB_H_
#define LIB_H_

/**************************************************************************************
 *          INCLUSIONS
 **************************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

/**************************************************************************************
 *          CONSTANTES & MACROS
 **************************************************************************************/

/* Constantes booléennes classiques. */
#define VRAI 1
#define FAUX 0



/**
 * Macro ALLOC :
 * @description
 *  Macro d'allocation mémoire.
 * @param
 *  _n - taille du tableau d'éléments
 *  _t - type des éléments
 * @sortie
 * 	Un pointeur vers une mémoire de taille adéquate.
 */
#define ALLOC(N,T) (T*) malloc(N*sizeof(T))

char* str_join(char *cs, ...);

#endif

