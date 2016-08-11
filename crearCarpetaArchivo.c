#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <time.h>
#include "crearCarpetaArchivo.h"
#include "estructuras.h"
#include "montarParticion.h"
#include "limpiar.h"
#include "busquedaCarpeta.h"
#include "crearArchivo.h"

/*Ruta del disco en donde se encuentra la particion*/
char rutaDisco[100];
/*Ruta del archivo que tiene el contenido para escribir en el archivo (si viene)*/
char rutaContenido[100];
/*Id de la particion que esta montada*/
char identificador[10];
/*Ruta del archivo (nuevo) que se va a escribir*/
char rutaArchivo[100];
/*Nombre de la particion para luego buscar su ubicacion en el MBR*/
char nameParticion[16];


void crearCarpetaArchivo(char *id, char *path, char comando, int tamano, char *pathContenido){

    /*Limpio las variables anteriormente creadas*/
    limpiar(rutaDisco, 100);
    limpiar(rutaContenido, 100);
    limpiar(identificador, 10);
    limpiar(rutaArchivo, 100);
    limpiar(nameParticion, 16);

    /*Copio los valores del metodo en los nuevos arreglos*/
    strcpy(identificador, id);
    strcpy(rutaArchivo, path);
    strcpy(rutaContenido, pathContenido);

    /*Por medio del ID busco el path del disco entre las particiones montadas*/
    xnode **w = NULL;

    w = xx_list_search(&m, identificador);

    if(w != NULL){
        strcpy(rutaDisco, (*w)->path);
        strcpy(nameParticion, (*w)->nombreParticion);
    }

    /*Leo del archivo el MBR para identificar en que byte empieza la particion correspondiente al ID*/
    MBR test;

    FILE * prueba = fopen(rutaDisco, "r+b");
    fseek(prueba, 0, SEEK_SET);
    fread(&test, sizeof(MBR), 1, prueba);

    if(prueba != NULL){

        /**************************************************************************************************************************************************************************************************************************/
        if(strcmp(test.mbr_partition_1.part_name, nameParticion) == 0){

            int respuesta = busquedaCarpeta(1, path, rutaDisco);

            /*Si la respuesta es igual a 0, significa que la ruta ingresada no existe, por lo que si viene el comando -p se procede a crear la ruta indicada, pero si no, se muestra error*/
            if(respuesta == 0){
                if(comando == 'p'){
                    busqueda_creacion(1, rutaArchivo, rutaDisco);
                    crearArchivo(1, rutaDisco, rutaArchivo, tamano, pathContenido);
                }else{
                    printf("No se puede realizar lo solicitado porque la ruta ingresada no existe!\n");
                    printf("***********************************************************************\n");
                }
            /*Si la ruta ingresada si existe, se procede a crear el archivo :)*/
            }else{
                printf("La ruta de archivo si existe, se procederá a crear el archivo!\n");
                crearArchivo(1, rutaDisco, rutaArchivo, tamano, pathContenido);
            }

        /**************************************************************************************************************************************************************************************************************************/
        }else if(strcmp(test.mbr_partition_2.part_name, nameParticion) == 0){

             int respuesta = busquedaCarpeta(2, path, rutaDisco);

            /*Si la respuesta es igual a 0, significa que la ruta ingresada no existe, por lo que si viene el comando -p se procede a crear la ruta indicada, pero si no, se muestra error*/
            if(respuesta == 0){
                if(comando == 'p'){
                    busqueda_creacion(2, rutaArchivo, rutaDisco);
                    crearArchivo(2, rutaDisco, rutaArchivo, tamano, pathContenido);
                }else{
                    printf("No se puede realizar lo solicitado porque la ruta ingresada no existe!\n");
                    printf("***********************************************************************\n");
                }
            /*Si la ruta ingresada si existe, se procede a crear el archivo :)*/
            }else{
                printf("La ruta de archivo si existe, se procederá a crear el archivo!\n");
                crearArchivo(2, rutaDisco, rutaArchivo, tamano, pathContenido);
            }

        /**************************************************************************************************************************************************************************************************************************/
        }else if(strcmp(test.mbr_partition_3.part_name, nameParticion) == 0){

            int respuesta = busquedaCarpeta(3, path, rutaDisco);

            /*Si la respuesta es igual a 0, significa que la ruta ingresada no existe, por lo que si viene el comando -p se procede a crear la ruta indicada, pero si no, se muestra error*/
            if(respuesta == 0){
                if(comando == 'p'){
                    busqueda_creacion(3, rutaArchivo, rutaDisco);
                    crearArchivo(3, rutaDisco, rutaArchivo, tamano, pathContenido);
                }else{
                    printf("No se puede realizar lo solicitado porque la ruta ingresada no existe!\n");
                    printf("***********************************************************************\n");
                }
            /*Si la ruta ingresada si existe, se procede a crear el archivo :)*/
            }else{
                printf("La ruta de archivo si existe, se procederá a crear el archivo!\n");
                crearArchivo(3, rutaDisco, rutaArchivo, tamano, pathContenido);
            }

        /**************************************************************************************************************************************************************************************************************************/
        }else if(strcmp(test.mbr_partition_4.part_name, nameParticion) == 0){

            int respuesta = busquedaCarpeta(4, path, rutaDisco);

            /*Si la respuesta es igual a 0, significa que la ruta ingresada no existe, por lo que si viene el comando -p se procede a crear la ruta indicada, pero si no, se muestra error*/
            if(respuesta == 0){
                if(comando == 'p'){
                    busqueda_creacion(4, rutaArchivo, rutaDisco);
                    crearArchivo(4, rutaDisco, rutaArchivo, tamano, pathContenido);
                }else{
                    printf("No se puede realizar lo solicitado porque la ruta ingresada no existe!\n");
                    printf("***********************************************************************\n");
                }
            /*Si la ruta ingresada si existe, se procede a crear el archivo :)*/
            }else{
                printf("La ruta de archivo si existe, se procederá a crear el archivo!\n");
                crearArchivo(4, rutaDisco, rutaArchivo, tamano, pathContenido);
            }

        }
        /**************************************************************************************************************************************************************************************************************************/

    }

}



























