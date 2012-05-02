/*
 * element.c
 *
 *  Created on: 28 avr. 2012
 *      Author: Loup
 */

#include "element.h"

char* stackElementToString(elemp_t el) {
	char* buffer = NULL;
	buffer = ALLOC(25, char);
	sprintf(buffer, "%d", el);
	return buffer;
}

char* treeElementToString(elema_t el) {
	char* buffer = NULL;
	buffer = ALLOC(25, char);
	sprintf(buffer, "%d", el);
	return buffer;
}

elemp_t stringToStackElement(char* value) {
	return atoi(value);
}

elema_t stringToTreeElement(char* value) {
	return atoi(value);
}

