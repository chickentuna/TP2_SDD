#ifndef __LINKED_LIST_H
#define __LINKED_LIST_H

#define push_into(pile, el) \
	{ pushLPile(&(pile), (el)); }

#define pop_from(pile, var) {			\
	lpile_t* __el = popLPile(&(pile));	\
	var = ((typeof(var))__el->addr);	\
	free(__el);						}	\

#define empty(pile) estVideLPile(pile)

#include "stdio.h"
#include "string.h"
#include "lib.h"

typedef struct llist_s {
	void *addr;
	struct llist_s *next;
} llist_t;

typedef char* (*serialize_t)(void *addr);
typedef void (*fdestroy_t)(void* addr);
typedef char* (*ftostring_t)(llist_t* list);

typedef llist_t lpile_t;

/**
 * Créer une pile chaînée vide contenant un élément.
 * Cet élément contient l'adresse passée en paramètre.
 * Test : OK
 */
llist_t* createLList(void *addr);
void destroyLList(llist_t* head, fdestroy_t destroy);
llist_t** getPrevLList(llist_t** head, llist_t* element);
void removeNextLList(llist_t** prev, fdestroy_t destroy);
void removeLList(llist_t** head, llist_t* element, fdestroy_t destroy);

/** Fonctions qui utilisent la liste comme une pile **/
lpile_t* createLPile(void* addr);
void destroyLPile(lpile_t* pile, fdestroy_t destroy);
boolean_t estVideLPile(lpile_t* pile);
void pushLPile(lpile_t** pile, void* addr);
lpile_t* popLPile(lpile_t** pile);
char* serializeLPile(lpile_t* pile, ftostring_t toString);

#endif
