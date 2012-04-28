#include "arbre.h"
#include "element.h"

arbre_t * initArbre(char * str) {
	arbre_t *nouv;
	nouv = ALLOC(1,arbre_t);
	int c = 0;
	elem_t val;

	val = obtenirValeur(str,c);
	nouv->valeur = val;




	return NULL;
}

elem_t obtenirValeur(char * str, int c) {
	int i=c;
	int n,k;
	char *buf;
	elem_t res;

	while (str[i]!='(' && str[i]!=')' && str[i]!='+' && str[i]!='*') {
		i++;
	}
	buf = ALLOC(i-c+1,char);
	n=0;
	for (k=c;k<i;k++) {
		if (str[k]!=' ')
			buf[n++] = str[k];
	}
	buf[n]='\0';
	res = stringToElement(buf);
	free(buf);
	return res;
}

