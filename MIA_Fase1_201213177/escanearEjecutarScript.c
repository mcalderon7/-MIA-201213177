#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "removeSpaces.h"
#include "limpiar.h"
#include "vaciarArreglo.h"
#include "escanearEjecutarScript.h"
#include "ejecutarScript.h"

int fnx = 0;
int banderaError = 0;

void escanearEjecutarScript(char *ingreso){

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
                    auxlex[fnx] = c;
                    fnx++;
                    break;
                }else if(isdigit(c)){
                    estado = 2;
                    auxlex[fnx] = c;
                    fnx++;
                    break;
                }else if(c == '-'){
                    estado = 0;
                    break;
                }else if(c == '/'){
                    auxlex[fnx] = c;
                    fnx++;
                    estado = 0;
                    break;
                }else if(c == '#'){

                    if(banderaError == 0){

                        printf("Analisis realizado satisfactoriamente!\n");
                        printf("********************************************************************\n");
                        printf("Informacion recopilada:\n");
                        printf("%s %s %s", "Path: ", path, "\n");
                        printf("********************************************************************\n");

                        ejecutarScript(path);

                        fnx = 0;
                        limpiar(path, 200);

                        break;

                    }else{
                        printf("********************************************************************\n");
                        printf("No se procedio a realizar ninguna operacion!\n");
                        printf("********************************************************************\n");
                        break;
                    }


                }else{
                    printf("Error lexico con: %c\n", c);
                    estado = 0;
                    banderaError = 1;
                }


            case 1:

                if(isalpha(c)){
                    estado = 1;
                    auxlex[fnx] = c;
                    fnx++;
                    break;
                }else if(c == '/'){

                    if(strcmp(auxlex, "exec") == 0){
                        /*Esto signfica que lo recien leido es valido, por lo que procedemos con el analisis*/
                        estado = 2;
                        vaciarArreglo(auxlex);
						fnx = 0;
                        printf("encontro el exec\n");

                        /*Guardo de una vez la diagonal del path*/
                        auxlex[fnx] = c;
                        fnx++;

                        break;
                    }

                }else{
                    printf("Error lexico con: %c\n", c);
                    estado = 0;
                    banderaError = 1;
                }


            case 2:

                if(isalpha(c)){
                    estado = 2;
                    auxlex[fnx] = c;
                    fnx++;
                    break;
                }else if(c == '/'){
                    estado = 2;
                    auxlex[fnx] = c;
                    fnx++;
                    break;
                }else if(isdigit(c)){
                    estado = 2;
                    auxlex[fnx] = c;
                    fnx++;
                    break;
                }else if(c == '.'){
                    estado = 2;
                    auxlex[fnx] = c;
                    fnx++;
                    break;
                }else if(c == '#'){
                    strcpy(path, auxlex);
                    vaciarArreglo(auxlex);
					fnx = 0;
                    estado = 0;
                    i--;
                    break;
                }else{
                    printf("Error lexico con: %c\n", c);
                    estado = 0;
                    banderaError = 1;
                }


        }

    }

}
