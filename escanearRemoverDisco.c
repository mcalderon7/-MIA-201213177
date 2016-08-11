#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "escanearRemoverDisco.h"
#include "removeSpaces.h"
#include "limpiar.h"
#include "removerDisco.h"
#include "vaciarArreglo.h"

int rx = 0;

void escanearRemoverDisco(char *ingreso){
	/*Remuevo los espacios en blanco de la sentencia*/
    RemoveSpaces(ingreso);

    int x = strlen(ingreso);
    int i;
    int estado = 0;
    char c;

    char path[200];
    char auxlex[200];
    limpiar(auxlex, 200);

    for(i = 0; i < x; i++)
    {
        c = ingreso[i];

        switch(estado){

            case 0:

                if(isalpha(c)){
                    estado = 1;
                    auxlex[rx] = c;
                    rx++;
                    break;
                }else if(c == '/'){
                    auxlex[rx] = c;
                    rx++;
                    estado = 0;
                    break;
                }else{
                    if(c == '#'){

                        printf("Analisis realizado satisfactoriamente!\n");
                        printf("********************************************************************\n");
                        printf("Informacion recopilada:\n");
                        printf("%s %s %s", "Path: ", path, "\n");
                        printf("********************************************************************\n");

                        /*Ahora mando a crear el archivo con sus parametros especificos*/
                        rx = 0;
                        removerDisco(path);

                        break;
                    }
                }

            case 1:

                if(isalpha(c)){

                    estado = 1;
                    auxlex[rx] = c;
                    rx++;
                    break;

                }else if(c == '-'){

                    int j = 0;
                    for(j = 0; auxlex[j]; j++){
                      auxlex[j] = tolower(auxlex[j]);
                    }

                    if(strcmp(auxlex, "rmdisk") == 0){
                        /*Esto signfica que lo recien leido es valido, por lo que procedemos con el analisis*/
                        estado = 0;
                        vaciarArreglo(auxlex);
                        printf("encontro el rmdisk\n");
                        rx = 0;
                        break;
                    }

                }else if(c == ':'){

                    int j = 0;
                    for(j = 0; auxlex[j]; j++){
                      auxlex[j] = tolower(auxlex[j]);
                    }

                    if(ingreso[i+1] == ':'){

                        estado = 1;
                        break;

                    }else{

                        if(strcmp(auxlex, "path") == 0){
                            /*Esto signfica que lo recien leido es valido, por lo que procedemos con el analisis*/
                            estado = 0;
                            vaciarArreglo(auxlex);
                            printf("encontro el path\n");
                            rx = 0;
                            break;
                        }

                    }

                }else if(c == '/'){

                    estado = 0;
                    auxlex[rx] = c;
                    rx++;
                    break;

                }else if(isdigit(c)){

                    estado = 1;
                    auxlex[rx] = c;
                    rx++;
                    break;

                }else if(c == '.'){

                    estado = 1;
                    auxlex[rx] = c;
                    rx++;
                    break;

                }else if(c == '#'){

                    strcpy(path, auxlex);
                    vaciarArreglo(auxlex);
                    rx = 0;
                    estado = 0;
                    i--;
                    break;

                }else{
                    printf("%s %c", "Error lexico con: ", c);
                }

        }

    }
}
