#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "escanearGraficarMBR.h"
#include "removeSpaces.h"
#include "limpiar.h"
#include "graficarMBR.h"
#include "vaciarArreglo.h"

int cnx = 0;

void escanearGraficarMBR(char * ingreso){

    /*Remuevo los espacios en blanco de la sentencia*/
    RemoveSpaces(ingreso);

    int x = strlen(ingreso);
    int i;
    int estado = 0;
    char c;

    char path[200];
    char name[10];

    char auxlex[200];
    limpiar(auxlex, 200);

    for(i = 0; i < x; i++)
    {
        c = ingreso[i];

        switch(estado){

            case 0:

                if(isalpha(c)){
                    estado = 1;
                    auxlex[cnx] = c;
                    cnx++;
                    break;
                }else if(isdigit(c)){
                    estado = 2;
                    auxlex[cnx] = c;
                    cnx++;
                    break;
                }else if(c == '-'){
                    estado = 0;
                    break;
                }else if(c == '/'){
                    auxlex[cnx] = c;
                    cnx++;
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
                        cnx = 0;

                        if((strcmp(name, "mbr") == 0) || (strcmp(name, "disk") == 0)){
                            graficarMBR(path);
                        }else{
                            printf("********************************************************************\n");
                            printf("No se puede realizar el reporte indicado.\n");
                            printf("********************************************************************\n");
                        }

                        break;
                    }
                }

            case 1:

                if(isalpha(c)){

                    estado = 1;
                    auxlex[cnx] = c;
                    cnx++;
                    break;

                }else if(c == '-'){

                    if(strcmp(auxlex, "rep") == 0){
                        /*Esto signfica que lo recien leido es valido, por lo que procedemos con el analisis*/
                        estado = 0;
                        vaciarArreglo(auxlex);
						cnx = 0;
                        printf("encontro el rep\n");
                        break;
                    }

                }else if(c == ':'){

                    if(strcmp(auxlex, "name") == 0){
                        /*Esto signfica que lo recien leido es valido, por lo que procedemos con el analisis*/
                        estado = 2;
                        vaciarArreglo(auxlex);
                        cnx = 0;
                        printf("encontro el name\n");
                        break;
                    }else if(strcmp(auxlex, "path") == 0){
                        /*Esto signfica que lo recien leido es valido, por lo que procedemos con el analisis*/
                        estado = 0;
                        vaciarArreglo(auxlex);
						cnx = 0;
                        printf("encontro el path\n");
                        break;
                    }

                }else if(c == '/'){
                    estado = 0;
                    auxlex[cnx] = c;
                    cnx++;
                    break;
                }else if(isdigit(c)){
                    estado = 1;
                    auxlex[cnx] = c;
                    cnx++;
                    break;
                }else if(c == '.'){
                    estado = 1;
                    auxlex[cnx] = c;
                    cnx++;
                    break;
                }else if(c == '#'){
                    strcpy(path, auxlex);
                    vaciarArreglo(auxlex);
					cnx = 0;
                    estado = 0;
                    i--;
                    break;
                }

             case 2:

                if(isalpha(c)){
                    estado = 2;
                    auxlex[cnx] = c;
                    cnx++;
                    break;
                }else if(c == '-'){
                    strcpy(name, auxlex);
                    vaciarArreglo(auxlex);
					cnx = 0;
                    estado = 0;
                }

        }

    }

}
