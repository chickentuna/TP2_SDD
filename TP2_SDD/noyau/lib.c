/*
 * lib.c
 *
 *  Created on: 28 avr. 2012
 *      Author: Loup
 */

#include "lib.h"

/**
 * Permet de fusionner deux chaine de caractère.
 * ATTENTION : terminer la liste de paramètre par NULL.
 */
char* str_join(char *cs, ...) {

	va_list va; // Liste des éléments.
	const char *ct; // Variable stockant l'itération.
	char *s = NULL; // Variable stockant la chaine finale.
	size_t size = 0; // Taille de la nouvelle chaine pour chaque itération.

	va_start(va, cs); // Démarrage de l'itération sur les éléments.

	// Tant que le paramètre n'est pas NULL.
	while ((ct = va_arg(va, char*)) != NULL) {

		void *tmp = NULL;

		// On calcule la taille de la chaine résultant de la fusion
		// En comprenant le séparateur éventuel.
		size += strlen(ct) + strlen(cs);

		// Réallocation de la mémoire pour contenir la nouvelle chaine.
		tmp = realloc(s, sizeof(*s) * (size + 1));

		// Test de la mémoire restante.
		if (tmp != NULL) {
			// On copie la nouvelle chaine.
			if (s == NULL) {
				// Si s est nulle ça veut dire qu'on est à la première itération
				// donc on ne copie pas le séparateur.
				s = tmp;
				strcpy(s, ct);
			} else {
				// On copie le séparateur avec la chaine ajoutée.
				s = tmp;
				strcat(s, cs);
				strcat(s, ct);
			}
		} else {
			// Gestion du manque de mémoire.
			fprintf(stderr, "ERREUR : mémoire insuffisante\n");
			free(s);
			s = NULL;
			exit(EXIT_FAILURE);
		}
	}
	return s;
}


