#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "escanearCrearParticion.h"
#include "removeSpaces.h"
#include "limpiar.h"
#include "vaciarArreglo.h"
#include "crearParticion.h"

int px = 0;
int py = 0;

void escanearCrearParticion(char *ingreso){
	/*Remuevo los espacios en blanco de la sentencia*/
    RemoveSpaces(ingreso);

    int x = strlen(ingreso);
    int i;
    int estado = 0;
    char c;

    /*Variables en las que almaceno la información*/
    int size = 0;
    int num_add = 0;
    char unit = '\0';
    char type = '\0';
    char fit = '\0';
    char borrar[5];
    limpiar(borrar, 5);
    char name[100];
    limpiar(name, 100);
    char path[200];

    /*Variables utilizadas para el analisis*/
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
                    auxlex[px] = c;
                    px++;
                    break;
                }else if(isdigit(c)){
                    estado = 2;
                    numlex[py] = c;
                    py++;
                    break;
                }else if(c == '-'){
                    estado = 0;
                    break;
                }else if(c == '/'){
                    auxlex[px] = c;
                    px++;
                    estado = 0;
                    break;
                }else{
                    if(c == '#'){

                        printf("Analisis realizado satisfactoriamente!\n");

                        /*Si unit viene vacio, significa que el usuario no agrego la unidad si en dado caso la llegara a crear, por lo que se colocará K*/
                        if(unit == '\0'){
                            unit = 'K';
                        /*Si unit es distinto de vacio se verificará que sea una de las letras que corresponde*/
                        }else{
                            if((unit == 'B')||(unit == 'M')||(unit == 'K')){

                            }else{
                                printf("++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
                                printf("Unidad no valida.\n");
                                printf("++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
                            }
                        }


                        /*Si type viene vacio, significa que el usuario no agrego el tipo de particion si en dado caso la llegara a crear, por lo que se colocará P*/
                        if(type == '\0'){
                            type = 'P';
                        /*Si unit es distinto de vacio se verificará que sea una de las letras que corresponde*/
                        }else{
                            if(type == 'P' || type == 'E' || type == 'L'){

                            }else{
                                printf("++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
                                printf("Tipo de particion no valida.\n");
                                printf("++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
                            }
                        }


                        /*Si fit viene vacio, significa que el usuario no indico el ajuste para colocar la particion, por lo que se colocará W*/
                        if(fit == '\0'){
                            fit = 'W';
                        /*Si unit es distinto de vacio se verificará que sea una de las letras que corresponde*/
                        }else{
                            if(fit == 'B' || fit == 'F' || fit == 'W'){

                            }else{
                                printf("++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
                                printf("Tipo de ajuste no valido.\n");
                                printf("++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
                            }
                        }

                        printf("********************************************************************\n");
                        printf("Informacion recopilada:\n");
                        /*Ahora mando a crear el archivo con sus parametros especificos*/
                        printf("%s %d %s", "Size: ", size, "\n");
                        printf("%s %c %s", "Unit: ", unit, "\n");
                        printf("%s %s %s", "Path: ", path, "\n");
                        printf("%s %c %s", "Type: ", type, "\n");
                        printf("%s %c %s", "Fit: ", fit, "\n");
                        printf("%s %d %s", "Add: ", num_add, "\n");
                        printf("%s %s %s", "Name: ", name, "\n");
                        printf("%s %s %s", "Delete: ", borrar, "\n");
                        px = 0;
                        py = 0;
                        printf("********************************************************************\n");

                        /*Mando los parametros para crear/agregar/eliminar particiones*/
                        crearParticion(size, unit, path, type, fit, num_add, name, borrar);

                        break;
                    }
                }

            case 1:

                if(isalpha(c)){
                    estado = 1;

                    if(strcmp(auxlex, "unit") == 0){
                        /*En esta parte de aqui, guardo la letra de unit que desee para el disco*/
                        unit = c;
                        vaciarArreglo(auxlex);
                        px = 0;
                        estado = 0;
                        break;
                    }else if(strcmp(auxlex, "type") == 0){
                        type = c;
                        vaciarArreglo(auxlex);
                        px = 0;
                        estado = 0;
                        break;
                    }else{
                        auxlex[px] = c;
                        px++;
                        break;
                    }

                }else if(c == '-'){
                    if(strcmp(auxlex, "fdisk") == 0){
                        /*Esto signfica que lo recien leido es valido, por lo que procedemos con el analisis*/
                        estado = 0;
                        vaciarArreglo(auxlex);
                        px = 0;
                        printf("encontro el fdisk\n");
                        break;
                    }else{
                        printf("Sentencia desconocida\n");
                        break;
                    }
                }else if(c == ':'){

                    if(strcmp(auxlex, "size") == 0){
                        /*Esto signfica que lo recien leido es valido, por lo que procedemos con el analisis*/
                        estado = 2;
                        vaciarArreglo(auxlex);
                        px = 0;
                        printf("encontro el size\n");
                        break;
                    }else if(strcmp(auxlex, "unit") == 0){
                        /*Esto signfica que lo recien leido es valido, por lo que procedemos con el analisis*/
                        estado = 1;
                        printf("encontro el unit\n");
                        break;
                    }else if(strcmp(auxlex, "path") == 0){
                        /*Esto signfica que lo recien leido es valido, por lo que procedemos con el analisis*/
                        estado = 7;
                        vaciarArreglo(auxlex);
                        px = 0;
                        printf("encontro el path\n");
                        break;
                    }else if(strcmp(auxlex, "type") == 0){
                        /*Esto signfica que lo recien leido es valido, por lo que procedemos con el analisis*/
                        estado = 1;
                        printf("encontro el type\n");
                        break;
                    }else if(strcmp(auxlex, "fit") == 0){
                        /*Esto signfica que lo recien leido es valido, por lo que procedemos con el analisis*/
                        estado = 3;
                        vaciarArreglo(auxlex);
                        px = 0;
                        printf("encontro el fit\n");
                        break;
                    }else if(strcmp(auxlex, "delete") == 0){
                        /*Esto signfica que lo recien leido es valido, por lo que procedemos con el analisis*/
                        estado = 4;
                        vaciarArreglo(auxlex);
                        px = 0;
                        printf("encontro el delete\n");
                        break;
                    }else if(strcmp(auxlex, "name") == 0){
                        /*Esto signfica que lo recien leido es valido, por lo que procedemos con el analisis*/
                        estado = 5;
                        vaciarArreglo(auxlex);
                        px = 0;
                        printf("encontro el name\n");
                        break;
                    }else if(strcmp(auxlex, "add") == 0){
                        /*Esto signfica que lo recien leido es valido, por lo que procedemos con el analisis*/
                        estado = 6;
                        vaciarArreglo(auxlex);
                        px = 0;
                        printf("encontro el add\n");
                        break;
                    }

                }

             case 2:

                if(isdigit(c)){
                    estado = 2;
                    auxlex[px] = c;
                    px++;
                    break;
                }else if(c == '-'){
                    size = atoi(auxlex);
                    estado = 0;
                    vaciarArreglo(auxlex);
                    px = 0;
                    break;
                }else if(c == '#'){
                    size = atoi(auxlex);
                    estado = 0;
                    vaciarArreglo(auxlex);
                    px = 0;
                    i--;
                    break;
                }

             case 3:

                if(isalpha(c)){
                    estado = 3;
                    fit = c;
                    break;
                }else if(c == '-'){
                    vaciarArreglo(auxlex);
                    px = 0;
                    estado = 0;
                    break;
                }else if(c == '#'){
                    vaciarArreglo(auxlex);
                    px = 0;
                    estado = 0;
                    i--;
                    break;
                }

             case 4:

                if(isalpha(c)){
                    estado = 4;
                    auxlex[px] = c;
                    px++;
                    break;
                }else if(c == '-'){
                    strcpy(borrar, auxlex);
                    vaciarArreglo(auxlex);
                    px = 0;
                    estado = 0;
                    break;
                }else if(c == '#'){
                    strcpy(borrar, auxlex);
                    vaciarArreglo(auxlex);
                    px = 0;
                    estado = 0;
                    i--;
                    break;
                }

             case 5:

                if(c == '"'){
                    estado = 5;
                    auxlex[px] = c;
                    px++;
                    break;
                }else if(isalpha(c)){
                    estado = 5;
                    auxlex[px] = c;
                    px++;
                    break;
                }else if(c == '_'){
                    estado = 5;
                    auxlex[px] = c;
                    px++;
                    break;
                }else if(isdigit(c)){
                    estado = 5;
                    auxlex[px] = c;
                    px++;
                    break;
                }else if(c == '-'){
                    strcpy(name, auxlex);
                    vaciarArreglo(auxlex);
                    px = 0;
                    estado = 0;
                    break;
                }else if(c == '#'){
                    strcpy(name, auxlex);
                    vaciarArreglo(auxlex);
                    px = 0;
                    estado = 0;
                    i--;
                    break;
                }

              case 6:

                if(c == '-'){
                    if(isdigit(ingreso[i+1])){
                        estado = 6;
                        auxlex[px] = c;
                        px++;
                        break;
                    }else if(isalpha(ingreso[i+1])){
                        num_add = atoi(auxlex);
                        estado = 0;
                        vaciarArreglo(auxlex);
                        px = 0;
                        break;
                    }
                }else if(isdigit(c)){
                    estado = 6;
                    auxlex[px] = c;
                    px++;
                    break;
                }else if(c == '#'){
                    num_add = atoi(auxlex);
                    estado = 0;
                    vaciarArreglo(auxlex);
                    px = 0;
                    i--;
                    break;
                }


              case 7:

                if(isalpha(c)){
                    estado = 7;
                    auxlex[px] = c;
                    px++;
                    break;
                }else if(isdigit(c)){
                    estado = 7;
                    auxlex[px] = c;
                    px++;
                    break;
                }else if(c == '/'){
                    estado = 7;
                    auxlex[px] = c;
                    px++;
                    break;
                }else if(c == '_'){
                    estado = 7;
                    auxlex[px] = c;
                    px++;
                    break;
                }else if(c == '.'){
                    estado = 7;
                    auxlex[px] = c;
                    px++;
                    break;
                }else if(c == '-'){
                    strcpy(path, auxlex);
                    vaciarArreglo(auxlex);
                    px = 0;
                    estado = 0;
                    break;
                }else if(c == '#'){
                    strcpy(path, auxlex);
                    vaciarArreglo(auxlex);
                    estado = 0;
                    i--;
                    break;
                }

        }

    }
}
