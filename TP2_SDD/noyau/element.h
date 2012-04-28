/*
 * element.h
 *
 *  Created on: 28 avr. 2012
 *      Author: Loup
 */

#ifndef ELEMENT_H_
#define ELEMENT_H_

#include "stdio.h"
#include "lib.h"

typedef int elem_t;

/**
 * Pointeur vers la fonction qui va permettre de serializer un élément.
 */
typedef char* (*strel_f)(elem_t);

/**
 * Fonction qui permet de sérialiser un élément.
 */
char* elementToString(elem_t el);

#endif /* ELEMENT_H_ */
