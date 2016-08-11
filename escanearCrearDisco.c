#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "escanearCrearDisco.h"
#include "limpiar.h"
#include "removeSpaces.h"
#include "vaciarArreglo.h"
#include "creacionDiscos.h"
#include "vaciarNumeros.h"

int cntx = 0;
int cnty = 0;
int banderaErrores = 0;

void escanearCrearDisco(char *ingreso){

	/*Remuevo los espacios en blanco de la sentencia*/
    RemoveSpaces(ingreso);

    int x = strlen(ingreso);
    int i;
    int estado = 0;
    char c;

    int size;
    char unit;
    char path[200];

    char auxlex[200];
    limpiar(auxlex, 200);
    char numlex[200];
    limpiar(numlex, 200);

    for(i = 0; i < x; i++)
    {
        c = ingreso[i];

        switch(estado){

            case 0:

                if(isalpha(c)){
                    estado = 1;
                    auxlex[cntx] = c;
                    cntx++;
                    break;
                }else if(isdigit(c)){
                    estado = 2;
                    numlex[cnty] = c;
                    cnty++;
                    break;
                }else if(c == '-'){
                    estado = 0;
                    break;
                }else if(c == '/'){
                    auxlex[cntx] = c;
                    cntx++;
                    estado = 0;
                    break;
                }else{
                    if(c == '#'){
                        printf("Analisis realizado satisfactoriamente!\n");

                        printf("********************************************************************\n");
                        printf("Informacion recopilada:\n");
                        printf("%s %d %s", "Size: ", size, "\n");
                        printf("%s %c %s", "Unidad: ", unit, "\n");
                        printf("%s %s %s", "Path: ", path, "\n");
                        /*Ahora mando a crear el archivo con sus parametros especificos*/
                        cntx = 0;
                        cnty = 0;

                        /*Si unit viene vacio, significa que el usuario no agrego la unidad si en dado caso la llegara a crear, por lo que se colocará K*/
                        if(unit == '\0'){
                            unit = 'K';
                        /*Si unit es distinto de vacio se verificará que sea una de las letras que corresponde*/
                        }

                        if(banderaErrores == 1){
                            printf("********************************************************************\n");
                            printf("Existen errores, revise su sentencia!\n");
                            printf("********************************************************************\n");
                            banderaErrores = 0;
                        }else{
                            printf("********************************************************************\n");
                            crearDisco(size, unit, path);
                            printf("********************************************************************\n");
                        }

                        break;
                    }
                }

            case 1:

                if(isalpha(c)){
                    //estado = 1;

                    if(strcmp(auxlex, "unit") == 0){
                        /*En esta parte de aqui, guardo la letra de unit que desee para el disco*/
                        unit = c;
                        vaciarArreglo(auxlex);
						cntx = 0;
                        estado = 0;
                        break;
                    }else{
                        auxlex[cntx] = c;
                        cntx++;
                        break;
                    }

                }else if(c == '-'){

                    int j = 0;
                    for(j = 0; auxlex[j]; j++){
                      auxlex[j] = tolower(auxlex[j]);
                    }

                    if(strcmp(auxlex, "mkdisk") == 0){
                        /*Esto signfica que lo recien leido es valido, por lo que procedemos con el analisis*/
                        estado = 0;
                        vaciarArreglo(auxlex);
                        cntx = 0;
                        printf("encontro el mkdisk\n");
                        break;
                    }

                }else if(c == ':'){

                    int j = 0;
                    for(j = 0; auxlex[j]; j++){
                      auxlex[j] = tolower(auxlex[j]);
                    }

                    if(strcmp(auxlex, "size") == 0){
                        /*Esto signfica que lo recien leido es valido, por lo que procedemos con el analisis*/

                        if(ingreso[i+1] == ':'){
                            estado = 1;
                            break;
                        }else{
                            estado = 3;
                            printf("encontro el size\n");
                            break;
                        }

                    }else if(strcmp(auxlex, "unit") == 0){
                        /*Esto signfica que lo recien leido es valido, por lo que procedemos con el analisis*/

                        if(ingreso[i+1] == ':'){
                            estado = 1;
                            break;
                        }else{
                            estado = 1;
                            printf("encontro el unit\n");
                            break;
                        }

                    }else if(strcmp(auxlex, "path") == 0){
                        /*Esto signfica que lo recien leido es valido, por lo que procedemos con el analisis*/

                        if(ingreso[i+1] == ':'){
                            estado = 1;
                            break;
                        }else{
                            estado = 0;
                            vaciarArreglo(auxlex);
                            cntx = 0;
                            printf("encontro el path\n");
                            break;
                        }

                    }
                }else if(c == '/'){
                    estado = 0;
                    auxlex[cntx] = c;
                    cntx++;
                    break;
                }else if(isdigit(c)){
                    estado = 1;
                    auxlex[cntx] = c;
                    cntx++;
                    break;
                }else if(c == '.'){
                    estado = 1;
                    auxlex[cntx] = c;
                    cntx++;
                    break;
                }else if(c == '#'){
                    strcpy(path, auxlex);
                    vaciarArreglo(auxlex);
					cntx = 0;
                    estado = 0;
                    i--;
                    break;
                }

             case 2:

                if(isdigit(c)){
                    estado = 2;
                    numlex[cnty] = c;
                    cnty++;
                    break;
                }else if(c == '-'){

                    int j = 0;
                    for(j = 0; auxlex[j]; j++){
                      auxlex[j] = tolower(auxlex[j]);
                    }

                    if(strcmp(auxlex, "size") == 0){
                        /*Aqui ya tengo registrado el tamaño del que va a querer el disco*/
                        size = atoi(numlex);
                        estado = 0;
                        vaciarArreglo(auxlex);
						cntx = 0;
                        vaciarNumeros(numlex);
						cnty = 0;
                        break;
                    }
                }


            case 3:

                if(isdigit(c)){
                    estado = 3;
                    numlex[cnty] = c;
                    cnty++;
                    break;
                }else if(c == '-'){

                    int j = 0;
                    for(j = 0; auxlex[j]; j++){
                      auxlex[j] = tolower(auxlex[j]);
                    }

                    if((strcmp(auxlex, "size") == 0) && isdigit(numlex[0])){
                        /*Aqui ya tengo registrado el tamaño del que va a querer el disco*/
                        size = atoi(numlex);
                        estado = 0;
                        vaciarArreglo(auxlex);
						cntx = 0;
                        vaciarNumeros(numlex);
						cnty = 0;
                        break;
                    }else{
                        printf("********************************************************************\n");
                        printf("Error lexico con: %c\n", c);
                        printf("No se puede crear un tamaño con numeros negativos!\n");
                        printf("********************************************************************\n");
                        estado = 0;
                        banderaErrores = 1;
                    }
                }else if(c == '+'){
                    /*Aqui ya tengo registrado el tamaño del que va a querer el disco*/
                    size = atoi(numlex);
                    estado = 0;
                    vaciarArreglo(auxlex);
                    cntx = 0;
                    vaciarNumeros(numlex);
                    cnty = 0;
                }

        }

    }

}
