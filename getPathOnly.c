#include <string.h>
#include "getPathOnly.h"

char * getPathOnly(char *path){

    int tam = strlen(path);
    char *nueva;
    strcpy(nueva, path);
    char caracter = '\0';

    while(caracter != '/'){
        nueva[tam] = '\0';
        tam--;
        caracter = nueva[tam];
    }

    return nueva;

}