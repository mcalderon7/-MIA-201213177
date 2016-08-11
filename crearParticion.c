#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "crearParticion.h"
#include "crearParticionPrimaria.h"
#include "crearParticionLogica.h"
#include "crearParticionExtendida.h"
#include "verificarParticiones.h"
#include "verificarPartExt.h"
#include "verificarPartLog.h"
#include "agregarParticion.h"
#include "borrarParticion.h"

void crearParticion(int size, char unit, char * path, char type, char fit, int num_add, char * name, char * borrar){


    /*Primero verifico si no es un add o un delete*/
    if(num_add != 0 || borrar[0] != '\0'){

        if(num_add != 0 && borrar[0] != '\0'){

            printf("***********************************************************************\n");
            printf("No se pueden ejecutar los comandos add y delete a la misma vez!\n");
            printf("***********************************************************************\n");

        }else{

            if(num_add != 0){
                agregarParticion(size, unit, path, num_add, name);
            }else if(borrar[0] != '\0'){
                borrarParticion(path, name, borrar);
            }

        }

    }else{

        /*Como no es un add o un delete, entonces el usuario va a crear una particion, por lo que verifico primero es que tipo de particion desea crear*/

        /*Si desea crear una particion primaria:*/
        if(type == 'P'){

            /*Primero valido si hay particiones disponibles para trabajar en ellas*/
            int valido = verificarParticiones(path);

            if(valido == 1){
                crearParticionPrimaria(size, unit, path, type, fit, num_add, name, borrar);
            }else{
                printf("***********************************************************************\n");
                printf("Ya no se pueden crear particiones en este disco, todas estan activadas!\n");
                printf("***********************************************************************\n");
            }

        /*Si desea crear una particion extendida:*/
        }else if(type == 'E'){

            int valido = verificarPartExt(path);

            if(valido == 1){
                crearParticionExtendida(size, unit, path, type, fit, num_add, name, borrar);
            }else if(valido == 2){
                printf("***********************************************************************\n");
                printf("Ya no se pueden crear particiones en este disco, todas estan activadas!\n");
                printf("***********************************************************************\n");
            }else{
                printf("***********************************************************************\n");
                printf("Este disco ya cuenta con una particion de tipo extendida en su sistema!\n");
                printf("***********************************************************************\n");
            }

        /*Si desea crear una particion lógica*/
        }else{

            int valido = verificarPartLog(path);

            if(valido == 1){
                crearParticionLogica(size, unit, path, type, fit, num_add, name, borrar);
            }else{
                printf("***********************************************************************\n");
                printf("No es posible crear particion logica.\n");
                printf("Este disco no cuenta con una particion de tipo extendida en su sistema!\n");
                printf("***********************************************************************\n");
            }

        }

    }

}
