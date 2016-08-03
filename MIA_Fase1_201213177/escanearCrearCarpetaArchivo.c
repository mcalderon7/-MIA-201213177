#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "removeSpaces.h"
#include "limpiar.h"
#include "vaciarArreglo.h"
#include "escanearCrearCarpetaArchivo.h"
#include "montarParticion.h"
#include "crearCarpetaArchivo.h"

int ynx = 0;
int bandera_error = 0;
int banderaNumeroNegativo = 0;

void escanearCrearCarpetaArchivo(char *ingreso){

    /*Remuevo los espacios en blanco de la sentencia*/
    RemoveSpaces(ingreso);

    int x = strlen(ingreso);
    int i;
    int estado = 0;
    char c;

    char p;
    int size = 0;
    char id[10];
    char path[200];
    char pathCont[200];
    limpiar(id, 10);
    limpiar(path, 200);
    limpiar(pathCont, 200);

    char auxlex[200];
    limpiar(auxlex, 200);

    for(i = 0; i < x; i++)
    {
        c = ingreso[i];

        switch(estado){

            case 0:

                if(isalpha(c)){
                    estado = 1;
                    auxlex[ynx] = c;
                    ynx++;
                    break;
                }else if(c == '-'){

                    /*Si esto se cumple significa que viene el comando -p*/
                    if(ingreso[i+1] == 's'){
                        estado = 0;
                        break;
                    }else{
                        estado = 4;
                        break;
                    }

                }else{

                    if(c == '#'){

                        printf("Analisis realizado satisfactoriamente!\n");

                        printf("********************************************************************\n");
                        printf("Informacion recopilada:\n");
                        printf("%s %s %s", "Id: ", id, "\n");
                        printf("%s %s %s", "Path: ", path, "\n");
                        printf("%s %c %s", "Comando: ", p, "\n");
                        printf("%s %d %s", "Size: ", size, "\n");
                        printf("%s %s %s", "Path Copia: ", pathCont, "\n");
                        printf("********************************************************************\n");

                        ynx = 0;

                        /*Si no existe algun error*/
                        if(bandera_error == 0){

                            /*Verifico si la particion se encuentra montada*/
                            xnode **z = NULL;

                            /*Busco en la lista si ya existe alguna particion montada con ese nombre*/
                            z = xx_list_search(&m, id);

                            if(z == NULL){
                                /*Significa que la particion no existe*/
                                printf("No se puede crear el archivo/carpeta. Particion no se encuentra montada!\n");
                                printf("************************************************************************\n");
                            }else{
                                crearCarpetaArchivo(id, path, p, size, pathCont);
                            }

                        }else{
                            printf("Existen errores en la sentencia, no se ejecuto codigo.\n");
                            printf("************************************************************************\n");
                        }


                        limpiar(id, 10);
                        limpiar(path, 200);
                        limpiar(pathCont, 200);
                        p = '\0';
                        size = 0;
                        bandera_error = 0;

                        break;
                    }
                }



            case 1:

                if(isalpha(c)){

                    estado = 1;
                    auxlex[ynx] = c;
                    ynx++;
                    break;

                }else if(c == '-'){

                    if(strcmp(auxlex, "mkfile") == 0){
                        /*Esto signfica que lo recien leido es valido, por lo que procedemos con el analisis*/
                        estado = 0;
                        vaciarArreglo(auxlex);
						ynx = 0;
                        printf("encontro el mkfile\n");
                        break;
                    }else{
                        printf("Error sintactico con: %s\n", auxlex);
                        bandera_error = 1;
                    }

                }else if(c == ':'){

                    if(strcmp(auxlex, "id") == 0){
                        /*Esto signfica que lo recien leido es valido, por lo que procedemos con el analisis*/
                        estado = 2;
                        vaciarArreglo(auxlex);
                        ynx = 0;
                        printf("encontro el id\n");
                        break;
                    }else if(strcmp(auxlex, "path") == 0){
                        /*Esto signfica que lo recien leido es valido, por lo que procedemos con el analisis*/
                        estado = 3;
                        vaciarArreglo(auxlex);
						ynx = 0;
                        printf("encontro el path\n");
                        break;
                    }else if(strcmp(auxlex, "size") == 0){
                        /*Esto signfica que lo recien leido es valido, por lo que procedemos con el analisis*/
                        estado = 5;
                        vaciarArreglo(auxlex);
						ynx = 0;
                        printf("encontro el size\n");
                        break;
                    }else if(strcmp(auxlex, "cont") == 0){
                        /*Esto signfica que lo recien leido es valido, por lo que procedemos con el analisis*/
                        estado = 6;
                        vaciarArreglo(auxlex);
						ynx = 0;
                        printf("encontro el cont\n");
                        break;
                    }else{
                        printf("Error sintactico con: %s\n", auxlex);
                        bandera_error = 1;
                    }

                }else{
                    printf("Error lexico con: %c\n", c);
                    bandera_error = 1;
                }


             case 2:

                if(isalpha(c)){
                    estado = 2;
                    auxlex[ynx] = c;
                    ynx++;
                    break;
                }else if(isdigit(c)){
                    estado = 2;
                    auxlex[ynx] = c;
                    ynx++;
                    break;
                }else if(c == '-'){
                    strcpy(id, auxlex);
                    vaciarArreglo(auxlex);
					ynx = 0;
                    estado = 0;
                    break;
                }else{
                    printf("Error lexico con: %c\n", c);
                    bandera_error = 1;
                }


            case 3:

                if(isalpha(c)){
                    estado = 3;
                    auxlex[ynx] = c;
                    ynx++;
                    break;
                }else if(c == '/'){
                    estado = 3;
                    auxlex[ynx] = c;
                    ynx++;
                    break;
                }else if(isdigit(c)){
                    estado = 3;
                    auxlex[ynx] = c;
                    ynx++;
                    break;
                }else if(c == '.'){
                    estado = 3;
                    auxlex[ynx] = c;
                    ynx++;
                    break;
                }else if(c == '-'){
                    strcpy(path, auxlex);
                    vaciarArreglo(auxlex);
					ynx = 0;
                    estado = 0;
                    i--;
                    break;
                }else if(c == '#'){
                    strcpy(path, auxlex);
                    vaciarArreglo(auxlex);
					ynx = 0;
                    estado = 0;
                    i--;
                    break;
                }else{
                    printf("Error lexico con: %c\n", c);
                    bandera_error = 1;
                }


            case 4:

                if(isalpha(c) && c == 'p'){
                    p = c;
                    estado = 0;
                    vaciarArreglo(auxlex);
                    i++;
                    break;
                }else{
                    printf("Error lexico con: %c\n", c);
                    bandera_error = 1;
                }


            case 5:

                if(isdigit(c)){
                    estado = 5;
                    auxlex[ynx] = c;
                    ynx++;
                    banderaNumeroNegativo = 1;
                    break;
                }else if(c == '-'){
                    if(banderaNumeroNegativo == 0){
                        printf("Error lexico con: %c\n", c);
                        bandera_error = 1;
                    }else{
                        size = atoi(auxlex);
                        estado = 0;
                        vaciarArreglo(auxlex);
						ynx = 0;
						break;
                    }
                }else if(c == '#'){
                    if(banderaNumeroNegativo == 0){
                        printf("Error lexico con: %c\n", c);
                        bandera_error = 1;
                    }else{
                        size = atoi(auxlex);
                        estado = 0;
                        vaciarArreglo(auxlex);
						ynx = 0;
						i--;
						break;
                    }
                }


            case 6:

                if(isalpha(c)){
                    estado = 6;
                    auxlex[ynx] = c;
                    ynx++;
                    break;
                }else if(c == '/'){
                    estado = 6;
                    auxlex[ynx] = c;
                    ynx++;
                    break;
                }else if(isdigit(c)){
                    estado = 6;
                    auxlex[ynx] = c;
                    ynx++;
                    break;
                }else if(c == '.'){
                    estado = 6;
                    auxlex[ynx] = c;
                    ynx++;
                    break;
                }else if(c == '#'){
                    strcpy(pathCont, auxlex);
                    vaciarArreglo(auxlex);
					ynx = 0;
                    estado = 0;
                    i--;
                    break;
                }else{
                    printf("Error lexico con: %c\n", c);
                    bandera_error = 1;
                }

        }

    }

}
