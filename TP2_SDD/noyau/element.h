#ifndef ELEMENT_H_
#define ELEMENT_H_

#include "stdio.h"
#include "lib.h"

/**
 * Pointeur vers la fonction qui va permettre de serializer un élément.
 */
typedef char* (*strel_f)(elem_t);

/**
 * Fonction qui permet de sérialiser un élément.
 */
char* elementToString(elem_t el);
elem_t stringToElement(char* value);

#endif /* ELEMENT_H_ */
