#include "list.h"

lpile_t* createLPile(void* addr) {
	return createLList(addr);
}

void destroyLPile(lpile_t* pile, fdestroy_t destroy) {
	destroyLList(pile, destroy);
}

boolean_t estVideLPile(lpile_t* pile) {
	return pile == NULL;
}

void pushLPile(lpile_t** pile, void* addr) {
	lpile_t* added = createLList(addr);
	added->next = *pile;
	*pile = added;
}

lpile_t* popLPile(lpile_t** pile) {
	if (pile == NULL || *pile == NULL) {
		return NULL;
	}
	lpile_t* removed = *pile;
	*pile = (*pile)->next;
	removed->next = NULL;
	return removed;
}

char* serializeLPile(lpile_t* pile, ftostring_t toString) {
	char* buf = NULL;
	char* old_buf = NULL;

	if (estVideLPile(pile)) {
		buf = ALLOC(5, char);
		strcpy(buf, "vide");
	} else {
		buf = ALLOC(2, char);
		strcpy(buf, "[");
		lpile_t* cur;
		for (cur = pile; cur != NULL; cur = cur->next) {

			old_buf = buf;

			char* el = (*toString)(cur);
			buf = str_join("", buf, " ", el, NULL);

			free(old_buf);
			free(el);

		}
		old_buf = buf;
		buf = str_join("", buf, " ]", NULL);
		free(old_buf);
	}

	return buf;
}
