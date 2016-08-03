#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "analizar.h"
#include "leecad.h"

#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

int x = 9;

int main(int argc, char **argv){

	char entrada[200];

	printf("%s***BIENVENIDO AL CREADOR Y PARTICIONADOR DE DISCOS***\n\n", ANSI_COLOR_CYAN);

	while(x != 0)
	{
        printf("%sIngresa tu sentencia:\n%s", ANSI_COLOR_CYAN, ANSI_COLOR_RESET);
        leecad(entrada, 200);
		printf("--------------------------------------------------------------------\n");
    }

	return 0;
}
