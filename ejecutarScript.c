#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ejecutarScript.h"
#include "removeSpaces.h"
#include "removeJumps.h"
#include "limpiar.h"
#include "analizar.h"

void ejecutarScript(char *path){

    FILE* file = fopen(path, "r");
    char line[256];
    limpiar(line, 256);
    char auxline[256];
    limpiar(auxline, 256);

    if(file){
        while (fgets(line, sizeof(line), file)) {

            if(line[0] == '\n' || line[0] == '\0' || line[0] == '#' || line[0] == ' '){

            }else{
                printf("*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n");
                char *flag = "#";
                strcpy(auxline, line);
                strcat(auxline, flag);
                RemoveJumps(auxline);
                analizar(strtok(auxline, "\n"));
                printf("*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n");
            }

        }

        fclose(file);
    }else{
        printf("********************************************************************\n");
        printf("No se pudo abrir el archivo!\n");
        printf("********************************************************************\n");
    }

}
