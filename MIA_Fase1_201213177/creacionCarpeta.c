#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <time.h>
#include "estructuras.h"
#include "creacionCarpeta.h"
#include "limpiar.h"
#include "busquedaCarpeta.h"

char filePath[100];
char filePath_extra[100];
char diskPath[100];
char diskPath_extra[100];

void creacionCarpeta(int numero_de_particion, char *pathArchivo, char *pathDisco){

    limpiar(filePath, 100);
    limpiar(diskPath, 100);
    limpiar(filePath_extra, 100);
    limpiar(diskPath_extra, 100);
    strcpy(filePath, pathArchivo);
    strcpy(filePath_extra, pathArchivo);
    strcpy(diskPath, pathDisco);
    strcpy(diskPath_extra, pathDisco);

    MBR test;

    FILE * prueba = fopen(diskPath, "r+b");
    fseek(prueba, 0, SEEK_SET);
    fread(&test, sizeof(MBR), 1, prueba);

    /*Entero que me indica la posicion en donde comienzan los AVD's*/
    int inicioAVDs = 0;
    /*Entero que me indica la posicion en donde comienza el bitmap de los AVD's*/
    int inicioBitmapAVD = 0;

    /*Dependiendo del numero de pariticion del disco, así establezco los valores anteriores*/
    if(numero_de_particion == 1){
        inicioAVDs = test.mbr_partition_1.part_start + sizeof(SUPERBLOQUE) + sizeof(BITMAP_AVD);
        inicioBitmapAVD = test.mbr_partition_1.part_start + sizeof(SUPERBLOQUE);
    }else if(numero_de_particion == 2){
        inicioAVDs = test.mbr_partition_2.part_start + sizeof(SUPERBLOQUE) + sizeof(BITMAP_AVD);
        inicioBitmapAVD = test.mbr_partition_2.part_start + sizeof(SUPERBLOQUE);
    }else if(numero_de_particion == 3){
        inicioAVDs = test.mbr_partition_3.part_start + sizeof(SUPERBLOQUE) + sizeof(BITMAP_AVD);
        inicioBitmapAVD = test.mbr_partition_3.part_start + sizeof(SUPERBLOQUE);
    }else if(numero_de_particion == 4){
        inicioAVDs = test.mbr_partition_4.part_start + sizeof(SUPERBLOQUE) + sizeof(BITMAP_AVD);
        inicioBitmapAVD = test.mbr_partition_4.part_start + sizeof(SUPERBLOQUE);
    }


    BITMAP_AVD ba;
    BITMAP_AVD ba2;
    AVD avd_test;

    /*Variables que me van a servir para guardar la informacion*/
    int banderaExiste = 0;
    int posicionArchivo = 0;

    /*Ahora hago un split de (/) para contar cuantas carpetas vienen y lo guardo en la variable contadorEspacios*/
    const char s[2] = "/";
    char *token;
    token = strtok(filePath, s);

    /*Hago un ciclo en donde obtengo cuantas carpetas (incluyendo el nombre del archivo)*/
    int contadorEspacios = 0;
    while(token != NULL){
        contadorEspacios++;
        token = strtok(NULL, s);
    }

    contadorEspacios = contadorEspacios - 1;
    char *tokens_array[contadorEspacios];

    char *tok;
    tok = strtok(filePath_extra, s);
    int counter = 0;

    while(tok != NULL){
        if(counter < contadorEspacios){
            tokens_array[counter] = tok;
            counter++;
        }
        tok = strtok(NULL, s);
    }

    int f = 0;

    for(f = 0; f < (contadorEspacios); f++){
        printf("Creacion --- Valor de %d: %s\n", f, tokens_array[f]);
    }

    /*Esta sentencia me devuelve dos arrays para identificar que carpetas estan creadas y cuales no*/
    RESPUESTA resp = busquedaSimple(numero_de_particion, filePath_extra, diskPath_extra);



}

