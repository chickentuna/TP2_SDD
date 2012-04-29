#include "list.h"

llist_t* createLList(void *addr) {
	llist_t* list = ALLOC(1, struct llist_s);
	list->addr = addr;
	list->next = NULL;
	return list;
}

void destroyLList(llist_t* head, fdestroy_t destroy) {
	if (head != NULL) {
		destroyLList(head->next, destroy);
		(*destroy)(head->addr);
		free(head);
	}
}

llist_t** getPrevLList(llist_t** head, llist_t* element) {
	if (head == NULL) {
		return NULL;
	}
	llist_t** prev = head;
	llist_t* cur = (*head);
	while (cur != NULL && cur != element) {
		prev = &cur;
		cur = cur->next;
	}
	return prev;
}

void removeNextLList(llist_t** prev, fdestroy_t destroy) {
	if (prev != NULL) {
		llist_t* removed = (*prev);
		*prev = (*prev)->next;
		removed->next = NULL;
		destroyLList(removed, destroy);
	}
}

void removeLList(llist_t** head, llist_t* element, fdestroy_t destroy) {
	llist_t** prev = getPrevLList(head, element);
	removeNextLList(prev, destroy);
}

void insertNextLList(llist_t** prev, void* addr) {
	llist_t* added = createLList(addr);
	if (prev != NULL) {
		added->next = (*prev)->next;
	}
	*prev = added;
}
