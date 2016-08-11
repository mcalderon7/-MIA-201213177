#include <string.h>
#include "vaciarArreglo.h"

void vaciarArreglo(char* entrada){

    int w = strlen(entrada);
    int i;

    for(i = 0; i < w; i++){
        entrada[i] = '\0';
    }
}