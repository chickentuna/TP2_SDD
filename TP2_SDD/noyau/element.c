/*
 * element.c
 *
 *  Created on: 28 avr. 2012
 *      Author: Loup
 */

#include "element.h"

char* elementToString(elem_t el) {
	char* buffer = NULL;
	buffer = ALLOC(255, char);

	sprintf(buffer, "%d", el);

	return buffer;
}

elem_t stringToElement(char* value) {
	return atoi(value);
}

