#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "removeSpaces.h"
#include "limpiar.h"
#include "vaciarArreglo.h"
#include "escanearFormatearParticion.h"
#include "formatearParticion.h"
#include "montarParticion.h"

int jnx = 0;
int _banderaError = 0;

void escanearFormatearParticion(char *ingreso){

    /*Remuevo los espacios en blanco de la sentencia*/
    RemoveSpaces(ingreso);

    int x = strlen(ingreso);
    int i;
    int estado = 0;
    char c;

    char id[10];
    char type[5];
    limpiar(id, 10);
    limpiar(type, 5);


    char auxlex[200];
    limpiar(auxlex, 200);

    for(i = 0; i < x; i++)
    {
        c = ingreso[i];

        switch(estado){

            case 0:

                if(isalpha(c)){
                    estado = 1;
                    auxlex[jnx] = c;
                    jnx++;
                    break;
                }else{
                    if(c == '#'){
                        printf("Analisis realizado satisfactoriamente!\n");

                        printf("********************************************************************\n");
                        printf("Informacion recopilada:\n");
                        printf("%s %s %s", "Id: ", id, "\n");
                        printf("%s %s %s", "Type: ", type, "\n");
                        printf("********************************************************************\n");

                        jnx = 0;

                        /*Si no existe algun error*/
                        if(_banderaError == 0){
                            /*Si el type viene vacio significa que será tomado como full*/
                            if(type[0] == '\0'){
                                strcpy(type, "full");

                                /*Verifico si la particion se encuentra montada*/
                                xnode **z = NULL;

                                /*Busco en la lista si ya existe alguna particion montada con ese nombre*/
                                z = xx_list_search(&m, id);

                                if(z == NULL){
                                    /*Significa que la particion no existe*/
                                    printf("No se puede formatear la particion. Esta no se encuentra montada!\n");
                                    printf("***********************************************************************\n");
                                }else{
                                    formatearParticion(id, type);
                                }

                            }else{
                                /*Verifico si la particion se encuentra montada*/
                                xnode **z = NULL;

                                /*Busco en la lista si ya existe alguna particion montada con ese nombre*/
                                z = xx_list_search(&m, id);

                                if(z == NULL){
                                    /*Significa que la particion no existe*/
                                    printf("No se puede formatear la particion. Esta no se encuentra montada!\n");
                                    printf("***********************************************************************\n");
                                }else{
                                    formatearParticion(id, type);
                                }
                            }
                        }else{
                            printf("Existen errores en la sentencia, no se ejecuto codigo.\n");
                            printf("********************************************************************\n");
                        }


                        limpiar(id, 10);
                        limpiar(type, 5);

                        break;
                    }
                }

            case 1:

                if(isalpha(c)){

                    estado = 1;
                    auxlex[jnx] = c;
                    jnx++;
                    break;

                }else if(c == '-'){

                    int j = 0;
                    for(j = 0; auxlex[j]; j++){
                      auxlex[j] = tolower(auxlex[j]);
                    }

                    if(strcmp(auxlex, "mkfs") == 0){
                        /*Esto signfica que lo recien leido es valido, por lo que procedemos con el analisis*/
                        estado = 0;
                        vaciarArreglo(auxlex);
						jnx = 0;
                        printf("encontro el mkfs\n");
                        break;
                    }else{
                        printf("Error sintactico con: %s\n", auxlex);
                        _banderaError = 1;
                    }

                }else if(c == ':'){

                    int j = 0;
                    for(j = 0; auxlex[j]; j++){
                      auxlex[j] = tolower(auxlex[j]);
                    }

                    if(strcmp(auxlex, "id") == 0){
                        /*Esto signfica que lo recien leido es valido, por lo que procedemos con el analisis*/
                        estado = 2;
                        vaciarArreglo(auxlex);
                        jnx = 0;
                        printf("encontro el id\n");
                        break;
                    }else if(strcmp(auxlex, "type") == 0){
                        /*Esto signfica que lo recien leido es valido, por lo que procedemos con el analisis*/
                        estado = 3;
                        vaciarArreglo(auxlex);
						jnx = 0;
                        printf("encontro el type\n");
                        break;
                    }else{
                        printf("Error sintactico con: %s\n", auxlex);
                        _banderaError = 1;
                    }

                }else{
                    printf("Error lexico con: %c\n", c);
                    _banderaError = 1;
                }


             case 2:

                if(isalpha(c)){
                    estado = 2;
                    auxlex[jnx] = c;
                    jnx++;
                    break;
                }else if(isdigit(c)){
                    estado = 2;
                    auxlex[jnx] = c;
                    jnx++;
                    break;
                }else if(c == '-'){
                    strcpy(id, auxlex);
                    vaciarArreglo(auxlex);
					jnx = 0;
                    estado = 0;
                    break;
                }else if(c == '#'){
                    limpiar(id, 10);
                    strcpy(id, auxlex);
                    vaciarArreglo(auxlex);
					jnx = 0;
                    estado = 0;
                    i--;
                    break;
                }else{
                    printf("Error lexico con: %c\n", c);
                    _banderaError = 1;
                }


            case 3:

                if(isalpha(c)){
                    estado = 3;
                    auxlex[jnx] = c;
                    jnx++;
                }else if(c == '#'){
                    strcpy(type, auxlex);
                    vaciarArreglo(auxlex);
					jnx = 0;
                    estado = 0;
                    i--;
                    break;
                }else{
                    printf("Error lexico con: %c\n", c);
                    _banderaError = 1;
                }

        }

    }

}
