#include <stdio.h>
#include "removerDisco.h"

void removerDisco(char * path){

    char entrada;
    printf("¿Esta seguro de que desea borrar el disco? (Y/N) \n");
    scanf(" %c", &entrada);

    if(entrada == 'Y'){

        int status;

        status = remove(path);

        if( status == 0 ){
            printf("********************************************************************\n");
            printf("%s borrado exitosamente.\n",path);
            printf("********************************************************************\n");
        }
        else
        {
            printf("********************************************************************\n");
            printf("No se puede borrar el archivo indicado.\n");
            perror("Error");
            printf("********************************************************************\n");
        }

    }else{

        printf("********************************************************************\n");
        printf("No se ha realizado ninguna operación.\n");
        printf("********************************************************************\n");

    }



}
