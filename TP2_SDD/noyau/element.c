#include "element.h"

char* elementToString(elem_t el) {
	char* buffer = NULL;
	buffer = ALLOC(25, char);
	sprintf(buffer, "%d", (int)el);
	return buffer;
}


elem_t stringToElement(char* value) {
	return (elem_t)atoi(value);
}


