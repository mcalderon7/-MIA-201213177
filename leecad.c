#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "leecad.h"
#include "analizar.h"
#include "limpiar.h"

char cadena[100];
char nuevaCadena[100];

int leecad(char *cad, int n) {

   int i, c;

    c=getchar();
    if (c == EOF) {
        cad[0] = '\0';
        return 0;
    }

    if (c == '\n')
        i = 0;
    else {
        cad[0] = c;
        i = 1;
    }

    for (; i < n-1 && (c=getchar())!=EOF && c!='\n'; i++)
       cad[i] = c;

    cad[i] = '\0';

    if (c != '\n' && c != EOF)
        while ((c = getchar()) != '\n' && c != EOF);

	/*Mando al analizador la cadena ingresada para que verifique si es valida*/

	/*Le agrego el # al final para el analizador*/
	char *flag = "#";
	char sentencia[100];
	limpiar(sentencia, 100);
    strcpy(sentencia, cad);
    strcpy(&sentencia[ strlen(cad) ], flag);
    //printf("%s\n", sentencia);
	analizar(sentencia);

    return 1;
}
