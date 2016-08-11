#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "escanearMontarParticion.h"
#include "removeSpaces.h"
#include "limpiar.h"
#include "vaciarArreglo.h"
#include "montarParticion.h"
#include "verificarExistenciaParticion.h"

int tnx = 0;

int existe(const char* ruta) {

    FILE *archivo = fopen(ruta, "r");

    if (archivo) {
        fclose(archivo);
        return 1; //TRUE
    } else {
        return 0; //FALSE
    }

}

void escanearMontarParticion(char *ingreso){

    /*Remuevo los espacios en blanco de la sentencia*/
    RemoveSpaces(ingreso);

    int x = strlen(ingreso);
    int i;
    int estado = 0;
    char c;

    char path[200];
    char name[20];
    char id[5];
    limpiar(id, 5);

    char auxlex[200];
    limpiar(auxlex, 200);

    for(i = 0; i < x; i++)
    {
        c = ingreso[i];

        switch(estado){

            case 0:

                if(isalpha(c)){
                    estado = 1;
                    auxlex[tnx] = c;
                    tnx++;
                    break;
                }else if(isdigit(c)){
                    estado = 2;
                    auxlex[tnx] = c;
                    tnx++;
                    break;
                }else if(c == '-'){
                    estado = 0;
                    break;
                }else if(c == '/'){
                    auxlex[tnx] = c;
                    tnx++;
                    estado = 0;
                    break;
                }else{
                    if(c == '#'){
                        printf("Analisis realizado satisfactoriamente!\n");

                        printf("********************************************************************\n");
                        printf("Informacion recopilada:\n");
                        printf("%s %s %s", "Path: ", path, "\n");
                        printf("%s %s %s", "Name: ", name, "\n");
                        printf("%s %s %s", "Id: ", id, "\n");
                        printf("********************************************************************\n");

                        tnx = 0;


                        /*Significa que viene un unmount*/
                        if(id[0] != '\0'){
                            montarParticion(path, name, id);
                        /*Significa que viene un mount*/
                        }else{
                            /*Mando a verificar si existe el disco antes de y luego verifico si existe la particion*/
                            if(existe(path)){

                                /*Verifico si existe la particion en el disco*/
                                int valido = verificarExistenciaParticion(path, name);

                                if(valido == 1){
                                    montarParticion(path, name, id);
                                }else if(valido == 2){
                                    printf("No se puede montar la particion extendida!\n");
                                    printf("********************************************************************\n");
                                }else{
                                    printf("No se puede montar la particion porque no existe tal en el disco!\n");
                                    printf("********************************************************************\n");
                                }

                            }else{
                                printf("No se puede montar la particion porque la ruta de disco no existe!\n");
                                printf("********************************************************************\n");
                            }
                        }

                        limpiar(path, 200);
                        limpiar(name, 20);
                        limpiar(id, 5);

                        break;
                    }
                }

            case 1:

                if(isalpha(c)){

                    estado = 1;
                    auxlex[tnx] = c;
                    tnx++;
                    break;

                }else if(c == '-'){

                    int j = 0;
                    for(j = 0; auxlex[j]; j++){
                      auxlex[j] = tolower(auxlex[j]);
                    }

                    if(strcmp(auxlex, "mount") == 0){
                        /*Esto signfica que lo recien leido es valido, por lo que procedemos con el analisis*/
                        estado = 0;
                        vaciarArreglo(auxlex);
						tnx = 0;
                        printf("encontro el mount\n");
                        break;
                    }else if(strcmp(auxlex, "unmount") == 0){
                        /*Esto signfica que lo recien leido es valido, por lo que procedemos con el analisis*/
                        estado = 0;
                        vaciarArreglo(auxlex);
						tnx = 0;
                        printf("encontro el unmount\n");
                        break;
                    }else{
                        strcpy(path, auxlex);
                        vaciarArreglo(auxlex);
                        tnx = 0;
                        estado = 0;
                        break;
                    }

                }else if(c == ':'){

                    int j = 0;
                    for(j = 0; auxlex[j]; j++){
                      auxlex[j] = tolower(auxlex[j]);
                    }

                    if(strcmp(auxlex, "name") == 0){

                        /*Esto signfica que lo recien leido es valido, por lo que procedemos con el analisis*/
                        if(ingreso[i+1] == ':'){
                            estado = 1;
                            break;
                        }else{
                            estado = 2;
                            vaciarArreglo(auxlex);
                            tnx = 0;
                            printf("encontro el name\n");
                            break;
                        }

                    }else if(strcmp(auxlex, "path") == 0){

                        /*Esto signfica que lo recien leido es valido, por lo que procedemos con el analisis*/
                        if(ingreso[i+1] == ':'){
                            estado = 1;
                            break;
                        }else{
                            estado = 1;
                            vaciarArreglo(auxlex);
                            tnx = 0;
                            printf("encontro el path\n");
                            break;
                        }

                    }else if(strcmp(auxlex, "id") == 0){

                        /*Esto signfica que lo recien leido es valido, por lo que procedemos con el analisis*/
                        if(ingreso[i+1] == ':'){
                            estado = 1;
                            break;
                        }else{
                            estado = 3;
                            vaciarArreglo(auxlex);
                            tnx = 0;
                            printf("encontro el id\n");
                            break;
                        }

                    }

                }else if(c == '/'){
                    estado = 1;
                    auxlex[tnx] = c;
                    tnx++;
                    break;
                }else if(isdigit(c)){
                    estado = 1;
                    auxlex[tnx] = c;
                    tnx++;
                    break;
                }else if(c == '.'){
                    estado = 1;
                    auxlex[tnx] = c;
                    tnx++;
                    break;
                }else if(c == '#'){
                    strcpy(path, auxlex);
                    vaciarArreglo(auxlex);
					tnx = 0;
                    estado = 0;
                    i--;
                    break;
                }

             case 2:

                if(isalpha(c)){
                    estado = 2;
                    auxlex[tnx] = c;
                    tnx++;
                    break;
                }else if(isdigit(c)){
                    estado = 2;
                    auxlex[tnx] = c;
                    tnx++;
                    break;
                }else if(c == '#'){
                    strcpy(name, auxlex);
                    vaciarArreglo(auxlex);
					tnx = 0;
                    estado = 0;
                    i--;
                    break;
                }


            case 3:

                if(isalpha(c)){
                    estado = 3;
                    auxlex[tnx] = c;
                    tnx++;
                }else if(isdigit(c)){
                    estado = 3;
                    auxlex[tnx] = c;
                    tnx++;
                    break;
                }else if(c == '#'){
                    strcpy(id, auxlex);
                    vaciarArreglo(auxlex);
					tnx = 0;
                    estado = 0;
                    i--;
                    break;
                }

        }

    }

}
