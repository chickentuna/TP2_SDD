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
char* treeElementToString(elema_t el);
char* stackElementToString(elemp_t el);
elemp_t stringToStackElement(char* value);
elema_t stringToTreeElement(char* value);

#endif /* ELEMENT_H_ */
