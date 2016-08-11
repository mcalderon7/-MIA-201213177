#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <time.h>
#include "estructuras.h"
#include "busquedaCarpeta.h"
#include "limpiar.h"

char filePath[100];
char filePath2[100];
char diskPath[100];

int existencia(FILE *prueba, int inicioAVD, char *token){

    AVD avd_test;

    int respuesta = 0;

    fseek(prueba, inicioAVD, SEEK_SET);
    fread(&avd_test, sizeof(AVD), 1, prueba);

    if(strcmp(avd_test.avd_name_directorio, token) == 0){
        respuesta = 1;
    }else{
        respuesta = 0;
    }

    return respuesta;

}

void busqueda_creacion(int numero_de_particion, char *pathArchivo, char *pathDisco){

    limpiar(filePath, 100);
    limpiar(filePath2, 100);
    limpiar(diskPath, 100);
    strcpy(filePath, pathArchivo);
    strcpy(filePath2, pathArchivo);
    strcpy(diskPath, pathDisco);

    MBR test;
    AVD avd_test;
    //AVD avd_test_2;
    BITMAP_AVD ba;
    BITMAP_AVD ba2;

    FILE * prueba = fopen(pathDisco, "r+b");
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

    /*Ahora hago un split de (/) para verificar si ya existen esas carpetas en el AVD*/
    const char s[2] = "/";
    char *token;
    token = strtok(filePath, s);

    /*Hago un ciclo en donde obtengo cuantas carpetas (incluyendo el nombre del archivo)*/
    int contadorEspacios = 0;
    while(token != NULL){
        contadorEspacios++;
        token = strtok(NULL, s);
    }

    /*Ya que conte cuantos elementos son, creo un array para guardarlos y asi no desperdicio espacio de memoria*/
    contadorEspacios = contadorEspacios + 1;
    char *tokens_array[contadorEspacios];
    tokens_array[0] = "/";

    char *tok;
    tok = strtok(filePath2, s);
    int counter = 1;

    while(tok != NULL){
        if(counter < contadorEspacios){
            tokens_array[counter] = tok;
            counter++;
        }
        tok = strtok(NULL, s);
    }

    int f = 0;

    printf("Valores del tokens_array:\n");
    for(f = 0; f < (contadorEspacios - 1); f++){
        printf("Valor de %d: %s\n", f, tokens_array[f]);
    }

    /*Ahora en este ciclo, mando a verificar si existe ese nombre de carpeta, excepto el ultimo que es el nombre del archivo*/
    int w = 0;

    printf("----------------------------------------------------------------------------\n");

    for(w = 0; w < (contadorEspacios - 1); w++){

        int ex = existencia(prueba, inicioAVDs, tokens_array[w]);

        if(ex == 1){

            fseek(prueba, inicioAVDs, SEEK_SET);
            fread(&avd_test, sizeof(AVD), 1, prueba);

            int j = 0;

            for(j = 0; j < 6; j++){

                if(avd_test.avd_ap_array_subdirectorios[j] != -1){

                    int resp = existencia(prueba, avd_test.avd_ap_array_subdirectorios[j], tokens_array[w+1]);

                    if(resp == 1){
                        printf("Encontro la carpeta: %s\n", tokens_array[w+1]);
                        inicioAVDs = avd_test.avd_ap_array_subdirectorios[j];
                        break;
                    }
                }
            }

        }else{

            printf("----------------------------------------------------------------------------\n");
            printf("No encontro la carpeta: %s\n", tokens_array[w]);

            /*Como no encontro la carpeta, procedo a crearla*/
            /*Me posiciono en el puntero para leer el bitmap de avd para escribir*/
            fseek(prueba, inicioBitmapAVD, SEEK_SET);
            fread(&ba, sizeof(BITMAP_AVD), 1, prueba);
            int i = 0;
            int pos_bit_vacio = 0;

            /*Con el bitmap obtengo la posicion libre donde puedo escribir*/
            for(i=0; i<sizeof(BITMAP_AVD); i++){
                if(ba.bitmap[i] == '0'){
                    pos_bit_vacio = i;
                    break;
                }
            }

            /*Me posiciono en el puntero para escribir el avd que indica*/
            int nuevaPos = inicioBitmapAVD + sizeof(BITMAP_AVD) + ((pos_bit_vacio + 1)*sizeof(AVD)) - sizeof(AVD);
            fseek(prueba, nuevaPos, SEEK_SET);

            time_t now = time(0);
            char nuevo_nombre[16];
            limpiar(nuevo_nombre, 16);
            printf("Token array en la posicion %d: %s\n", i, tokens_array[w]);
            strcpy(nuevo_nombre, tokens_array[w]);

            AVD x_avd = {

                now,
                {nuevo_nombre[0], nuevo_nombre[1], nuevo_nombre[2], nuevo_nombre[3], nuevo_nombre[4], nuevo_nombre[5], nuevo_nombre[6], nuevo_nombre[7], nuevo_nombre[8], nuevo_nombre[9], nuevo_nombre[10], nuevo_nombre[11], nuevo_nombre[12], nuevo_nombre[13], nuevo_nombre[14], nuevo_nombre[15]},
                {-1, -1, -1, -1, -1, -1},
                -1,
                -1

            };

            /*Escribo en el archivo*/
            fwrite(&x_avd, sizeof(AVD), 1, prueba);

            /*Luego de escribirlo actualizo el bitmap*/
            fseek(prueba, inicioBitmapAVD, SEEK_SET);
            fread(&ba2, sizeof(BITMAP_AVD), 1, prueba);
            ba2.bitmap[pos_bit_vacio] = '1';
            fseek(prueba, inicioBitmapAVD, SEEK_SET);
            fwrite(&ba2, sizeof(BITMAP_AVD), 1, prueba);

            /*Luego de actualizar el bitmap, procedo a actualizar el primer puntero vacio del AVD con respecto a la estructura que estoy leyendo*/
            fseek(prueba, inicioAVDs, SEEK_SET);
            fread(&avd_test, sizeof(AVD), 1, prueba);
            int t = 0;

            for(t = 0; t < sizeof(avd_test.avd_ap_array_subdirectorios); t++){
                if(avd_test.avd_ap_array_subdirectorios[t] == -1){
                    avd_test.avd_ap_array_subdirectorios[t] = nuevaPos;
                    break;
                }
            }

            /*Luego de que ya cambie el valor de la posicion, lo escribo en el archivo*/
            fseek(prueba, inicioAVDs, SEEK_SET);
            fwrite(&avd_test, sizeof(AVD), 1, prueba);

            fseek(prueba, inicioAVDs, SEEK_SET);
            fread(&avd_test, sizeof(AVD), 1, prueba);

            printf("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
            printf("Valores del array de apuntadores de %s\n:", tokens_array[w-1]);
            int g = 0;
            for(g = 0; g < 6; g++){
                printf("Valores de la posicion %d: %d\n", w, avd_test.avd_ap_array_subdirectorios[g]);
            }
            printf("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");

            printf("Inicio AVDs: %d\n", inicioAVDs);
            inicioAVDs = nuevaPos;
            printf("Posicion del bit vacio en el bitmap: %d\n", pos_bit_vacio);
            printf("Posicion donde se escribio: %d\n", nuevaPos);
            printf("Ya se escribio :)\n");
            printf("----------------------------------------------------------------------------\n");

        }

    }

    /*int hehe = test.mbr_partition_1.part_start + sizeof(SUPERBLOQUE) + sizeof(BITMAP_AVD);
    printf("*-*-*-*-*-*-*-*-*-*Impresion de todos al final*-*-*-*-*-*-*-*-*-*\n");

    for(i = 0; i < (contadorEspacios - 1); i++){

        fseek(prueba, hehe, SEEK_SET);
        fread(&avd_test_2, sizeof(AVD), 1, prueba);

        int hoho = 0;
        printf("----------------------------------------------------------------------------\n");

        printf("Fecha creacion: %s\n", ctime(&avd_test_2.avd_fecha_creacion));
        printf("Nombre del directorio: %s\n", avd_test_2.avd_name_directorio);

        for(hoho = 0; hoho < 6; hoho++){
            printf("Apuntador en la posicion %d: %d\n", hoho, avd_test_2.avd_ap_array_subdirectorios[hoho]);
        }

        printf("----------------------------------------------------------------------------\n");

        hehe = hehe + sizeof(AVD);

    }*/

    limpiar(filePath, 100);
    limpiar(filePath2, 100);
    limpiar(diskPath, 100);
    fflush(prueba);
    fclose(prueba);
    printf("----------------------------------------------------------------------------\n");

}

int busquedaCarpeta(int numero_de_particion, char* pathArchivo, char* pathDisco){

    limpiar(filePath, 100);
    limpiar(filePath2, 100);
    limpiar(diskPath, 100);
    strcpy(filePath, pathArchivo);
    strcpy(filePath2, pathArchivo);
    strcpy(diskPath, pathDisco);

    int banderaRetornoDeMetodo = 0;

    MBR test;
    AVD avd_test;

    FILE * prueba = fopen(pathDisco, "r+b");
    fseek(prueba, 0, SEEK_SET);
    fread(&test, sizeof(MBR), 1, prueba);

    /*Entero que me indica la posicion en donde comienzan los AVD's*/
    int inicioAVDs = 0;

    /*Dependiendo del numero de pariticion del disco, así establezco los valores anteriores*/
    if(numero_de_particion == 1){
        inicioAVDs = test.mbr_partition_1.part_start + sizeof(SUPERBLOQUE) + sizeof(BITMAP_AVD);
    }else if(numero_de_particion == 2){
        inicioAVDs = test.mbr_partition_2.part_start + sizeof(SUPERBLOQUE) + sizeof(BITMAP_AVD);
    }else if(numero_de_particion == 3){
        inicioAVDs = test.mbr_partition_3.part_start + sizeof(SUPERBLOQUE) + sizeof(BITMAP_AVD);
    }else if(numero_de_particion == 4){
        inicioAVDs = test.mbr_partition_4.part_start + sizeof(SUPERBLOQUE) + sizeof(BITMAP_AVD);
    }

    /*Variables que me van a servir para guardar la informacion*/
    int banderaExiste = 0;

    /*Ahora hago un split de (/) para verificar si ya existen esas carpetas en el AVD*/
    const char s[2] = "/";
    char *token;
    token = strtok(filePath, s);

    /*Hago un ciclo en donde obtengo cuantas carpetas (incluyendo el nombre del archivo)*/
    int contadorEspacios = 0;
    while(token != NULL){
        contadorEspacios++;
        token = strtok(NULL, s);
    }

    /*Ya que conte cuantos elementos son, creo un array para guardarlos y asi no desperdicio espacio de memoria*/
    contadorEspacios = contadorEspacios + 1;
    char *tokens_array[contadorEspacios];
    tokens_array[0] = "/";

    char *tok;
    tok = strtok(filePath2, s);
    int counter = 1;

    while(tok != NULL){
        if(counter < contadorEspacios){
            tokens_array[counter] = tok;
            counter++;
        }
        tok = strtok(NULL, s);
    }

    /*int f = 0;

    for(f = 0; f < (contadorEspacios - 1); f++){
        printf("Valor de %d: %s\n", f, tokens_array[f]);
    }*/

    /*Array de enteros que me servira para identificar si existe o no cada carpeta de la ruta*/
    int array_carpetas[contadorEspacios];

    /*Lleno de 0's el archivo para representar que no existe tal carpeta*/
    int x = 0;
    for(x = 0; x < contadorEspacios; x++){
        array_carpetas[x] = 0;
    }

    /*Escribo el primer 1 en el array de carpetas porque la raiz ya existe siempre en el sistema de archivos*/
    array_carpetas[0] = 1;

    /*Ahora en este ciclo, mando a verificar si existe ese nombre de carpeta, excepto el ultimo que es el nombre del archivo*/
    int i = 0;
    int j = 0;

    printf("----------------------------------------------------------------------------\n");

    for(i = 0; i < (contadorEspacios - 2); i++){

        int ex = existencia(prueba, inicioAVDs, tokens_array[i]);

        if(ex == 1){

            fseek(prueba, inicioAVDs, SEEK_SET);
            fread(&avd_test, sizeof(AVD), 1, prueba);

            for(j = 0; j < 6; j++){

                if(avd_test.avd_ap_array_subdirectorios[j] != -1){

                    int resp = existencia(prueba, avd_test.avd_ap_array_subdirectorios[j], tokens_array[i+1]);

                    if(resp == 1){
                        printf("Encontro la carpeta: %s\n", tokens_array[i+1]);
                        array_carpetas[i] = 1;
                        inicioAVDs = avd_test.avd_ap_array_subdirectorios[j];
                        break;
                    }
                }
            }

        }else{
            printf("No encontro la carpeta: %s\n", tokens_array[i]);
            break;
        }

    }

    printf("----------------------------------------------------------------------------\n");

    /*Ahora recorro el array de carpetas para verificar que todos sean 1 excepto el ultimo valor del array por cuestiones del nombre del archivo*/
    int y = 0;
    for(y = 0; y < (contadorEspacios - 2); y++){

        //printf("Valor %d del array de carpetas: %d\n", y, array_carpetas[y]);

        if(array_carpetas[y] == 0){
            banderaExiste = 1;
            break;
        }
    }

    /*Si banderaExiste es igual a 1 significa que alguna de las carpetas no se encuentra creada, por lo que el valor que se retorna es 0*/
    if(banderaExiste == 1){
        banderaRetornoDeMetodo = 0;
        banderaExiste = 0;
        fclose(prueba);
    /*De lo contrario, si todas las carpetas existen, se puede proceder con la creacion del archivo*/
    }else{
        banderaRetornoDeMetodo = 1;
        banderaExiste = 0;
        fclose(prueba);
    }


    return banderaRetornoDeMetodo;

}

int obtenerApuntadorUltimaCarpeta(int numero_de_particion, char *pathArchivo, char *pathDisco){

    limpiar(filePath, 100);
    limpiar(filePath2, 100);
    limpiar(diskPath, 100);
    strcpy(filePath, pathArchivo);
    strcpy(filePath2, pathArchivo);
    strcpy(diskPath, pathDisco);

    int banderaRetornoDeMetodo = 0;

    MBR test;
    AVD avd_test;

    FILE * prueba = fopen(pathDisco, "r+b");
    fseek(prueba, 0, SEEK_SET);
    fread(&test, sizeof(MBR), 1, prueba);

    /*Entero que me indica la posicion en donde comienzan los AVD's*/
    int inicioAVDs = 0;

    /*Dependiendo del numero de pariticion del disco, así establezco los valores anteriores*/
    if(numero_de_particion == 1){
        inicioAVDs = test.mbr_partition_1.part_start + sizeof(SUPERBLOQUE) + sizeof(BITMAP_AVD);
    }else if(numero_de_particion == 2){
        inicioAVDs = test.mbr_partition_2.part_start + sizeof(SUPERBLOQUE) + sizeof(BITMAP_AVD);
    }else if(numero_de_particion == 3){
        inicioAVDs = test.mbr_partition_3.part_start + sizeof(SUPERBLOQUE) + sizeof(BITMAP_AVD);
    }else if(numero_de_particion == 4){
        inicioAVDs = test.mbr_partition_4.part_start + sizeof(SUPERBLOQUE) + sizeof(BITMAP_AVD);
    }

    /*Ahora hago un split de (/) para verificar si ya existen esas carpetas en el AVD*/
    const char s[2] = "/";
    char *token;
    token = strtok(filePath, s);

    /*Hago un ciclo en donde obtengo cuantas carpetas (incluyendo el nombre del archivo)*/
    int contadorEspacios = 0;
    while(token != NULL){
        contadorEspacios++;
        token = strtok(NULL, s);
    }

    /*Ya que conte cuantos elementos son, creo un array para guardarlos y asi no desperdicio espacio de memoria*/
    contadorEspacios = contadorEspacios + 1;
    char *tokens_array[contadorEspacios];
    tokens_array[0] = "/";

    char *tok;
    tok = strtok(filePath2, s);
    int counter = 1;

    while(tok != NULL){
        if(counter < contadorEspacios){
            tokens_array[counter] = tok;
            counter++;
        }
        tok = strtok(NULL, s);
    }

    /*int f = 0;

    for(f = 0; f < (contadorEspacios - 1); f++){
        printf("Valor de %d: %s\n", f, tokens_array[f]);
    }*/

    /*Ahora en este ciclo, mando a verificar si existe ese nombre de carpeta, excepto el ultimo que es el nombre del archivo*/
    int i = 0;
    int j = 0;

    printf("----------------------------------------------------------------------------\n");

    for(i = 0; i < (contadorEspacios - 2); i++){

        int ex = existencia(prueba, inicioAVDs, tokens_array[i]);

        if(ex == 1){

            fseek(prueba, inicioAVDs, SEEK_SET);
            fread(&avd_test, sizeof(AVD), 1, prueba);

            for(j = 0; j < 6; j++){

                if(avd_test.avd_ap_array_subdirectorios[j] != -1){

                    int resp = existencia(prueba, avd_test.avd_ap_array_subdirectorios[j], tokens_array[i+1]);

                    if(resp == 1){
                        printf("Encontro la carpeta: %s\n", tokens_array[i+1]);
                        banderaRetornoDeMetodo = avd_test.avd_ap_array_subdirectorios[j];
                        inicioAVDs = avd_test.avd_ap_array_subdirectorios[j];
                        break;
                    }
                }
            }

        }else{
            printf("No encontro la carpeta: %s\n", tokens_array[i]);
            break;
        }

    }

    //printf("-------------------------------------%d---------------------------------------\n", banderaRetornoDeMetodo);

    fflush(prueba);
    fclose(prueba);

    return banderaRetornoDeMetodo;

}
