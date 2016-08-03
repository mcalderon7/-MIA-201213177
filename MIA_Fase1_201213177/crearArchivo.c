#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <math.h>
#include "crearArchivo.h"
#include "estructuras.h"
#include "busquedaCarpeta.h"
#include "limpiar.h"

void crearArchivo(int numero_de_particion, char *pathDisco, char *pathArchivo, int tamano, char *pathContenido){

    /*Creo y limpio mis variables para copiar lo que venga el metodo*/
    char file_path[100];
    char file_path_2[100];
    char nombre_archivo[16];
    char content_path[100];
    char disk_path[100];
    limpiar(file_path, 100);
    limpiar(file_path_2, 100);
    limpiar(nombre_archivo, 16);
    limpiar(content_path, 100);
    limpiar(disk_path, 100);
    strcpy(file_path, pathArchivo);
    strcpy(file_path_2, pathArchivo);
    strcpy(content_path, pathContenido);
    strcpy(disk_path, pathDisco);

    MBR test_mbr;
    AVD test_avd;
    BITMAP_DD test_bit_dd;
    BITMAP_BD test_bit_bd;
    BITMAP_INODO test_bit_inodo;

    /*Detalle de directorio*/
    int inicioBitmapDD = 0;
    int inicioDetalleDirectorio = 0;

    /*Inodo*/
    int inicioBitmapInodos = 0;
    int inicioInodos = 0;

    /*Bloque de datos*/
    int inicioBitmapBD = 0;

    /*Cantidad de bloques*/
    int cantidadBloques = 0;

    /*Leo el MBR del archivo para posicionarme segun sea el numero de la particion*/
    FILE * prueba = fopen(pathDisco, "r+b");
    fseek(prueba, 0, SEEK_SET);
    fread(&test_mbr, sizeof(MBR), 1, prueba);

    /*Obtengo los valores con respecto a la particion*/
    if(numero_de_particion == 1){
        inicioBitmapDD = test_mbr.mbr_partition_1.part_start + sizeof(SUPERBLOQUE) + sizeof(BITMAP_AVD) + (25*sizeof(AVD));
    }else if(numero_de_particion == 2){
        inicioBitmapDD = test_mbr.mbr_partition_2.part_start + sizeof(SUPERBLOQUE) + sizeof(BITMAP_AVD) + (25*sizeof(AVD));
    }else if(numero_de_particion == 3){
        inicioBitmapDD = test_mbr.mbr_partition_3.part_start + sizeof(SUPERBLOQUE) + sizeof(BITMAP_AVD) + (25*sizeof(AVD));
    }else if(numero_de_particion == 4){
        inicioBitmapDD = test_mbr.mbr_partition_4.part_start + sizeof(SUPERBLOQUE) + sizeof(BITMAP_AVD) + (25*sizeof(AVD));
    }

    /*Guardo los apuntadores de cada bloque de estructuras de la particion*/
    inicioDetalleDirectorio = inicioBitmapDD + sizeof(BITMAP_DD);
    inicioBitmapInodos = inicioDetalleDirectorio + (25*sizeof(DETALLE_DIRECTORIO));
    inicioInodos = inicioBitmapInodos + sizeof(BITMAP_INODO);
    inicioBitmapBD = inicioInodos + (25*sizeof(INODO));

    /*Obtengo el entero que me indica el byte en el que se encuentra escrita la ultima carpeta de la ruta*/
    int apuntadorUltimaCarpeta = obtenerApuntadorUltimaCarpeta(numero_de_particion, file_path, disk_path);

    /*Abro el archivo y leo el AVD de la ultima carpeta para acceder a su apuntador de detalle de directorio*/
    fseek(prueba, apuntadorUltimaCarpeta, SEEK_SET);
    fread(&test_avd, sizeof(AVD), 1, prueba);

    /*Si el apuntador es igual a -1 significa que no existe ningun detalle de directorio por lo que procedo a crear uno, si no, me posiciono en ese entero para leer el detalle de directorio y agregar el archivo*/
    if(test_avd.avd_ap_detalle_directorio == -1){

        /*Ahora hago un split de (/) para obtener el ultimo valor del split para guardar el valor del nombre del archivo*/
        const char s[2] = "/";
        char *token;
        token = strtok(file_path, s);

        /*Hago un ciclo en donde obtengo cuantas carpetas (incluyendo el nombre del archivo)*/
        int contadorEspacios = 0;
        while(token != NULL){
            contadorEspacios++;
            token = strtok(NULL, s);
        }

        /*Ya que conte cuantos elementos son, creo un array para guardarlos y asi no desperdicio espacio de memoria*/
        char *tokens_array[contadorEspacios];

        char *tok;
        tok = strtok(file_path_2, s);
        int counter = 0;

        while(tok != NULL){
            if(counter < contadorEspacios){
                tokens_array[counter] = tok;
                counter++;
            }
            tok = strtok(NULL, s);
        }

        /*Ya que llene el tokens_array obtengo el ultimo valor del array que es el nombre del archivo*/
        strcpy(nombre_archivo, tokens_array[contadorEspacios]);

        /*Primero, antes de escribir todas las estructuras (Detalle de directorio, Inodo y Bloque de datos) procedo a estimar los bloques de datos dependiendo del texto ya sea con size o que tenga el contenido de otro archivo*/
        /*En este arreglo guardo los apuntadores donde se va a escribir los bloques de datos para luego escribirlo en el inodo*/
        int apuntadores[4] = {-1, -1, -1, -1};

        /*Bandera que me indica si venia contenido o no para poder obtener el size que se va a escribir en el inodo y otro entero para guardar la cantidad de bytes (tamaño) para cuando viene un contenido*/
        int flagContenido = 0;
        int bytesContenido = 0;

        /*Significa que no viene una ruta de la cual copiar contenido*/
        if ((pathContenido != NULL) && (pathContenido[0] == '\0')) {

            /*Actualizo mi bandera*/
            flagContenido = 0;

            /*Ahora verifico si viene el parametro size para escribir los numeros del 0-9 o vacio*/
            if(tamano == 0){

                fseek(prueba, inicioBitmapBD, SEEK_SET);
                fread(&test_bit_bd, sizeof(BITMAP_BD), 1, prueba);
                int y = 0;
                int pos_bit_vacio = 0;

                /*Con el bitmap obtengo la posicion libre donde puedo escribir*/
                for(y=0; y<25; y++){
                    if(test_bit_bd.bitmap[y] == '0'){
                        pos_bit_vacio = y;
                        break;
                    }
                }

                /*Me posiciono en el puntero para escribir el bloque de datos que indica*/
                int nuevaPos = inicioBitmapBD + sizeof(BITMAP_BD) + ((pos_bit_vacio + 1)*sizeof(BLOQUE_DATOS)) - sizeof(BLOQUE_DATOS);

                /*Ahora procedo a escribir la estructura de bloque de datos*/
                BLOQUE_DATOS test_bd = {
                    {'\0'}
                };

                /*Me posiciono en el puntero para escribir el bloque de datos*/
                fseek(prueba, nuevaPos, SEEK_SET);
                fwrite(&test_bd, sizeof(BLOQUE_DATOS), 1, prueba);

                /*Luego de escribirlo actualizo el bitmap*/
                fseek(prueba, inicioBitmapBD, SEEK_SET);
                fread(&test_bit_bd, sizeof(BITMAP_BD), 1, prueba);

                test_bit_bd.bitmap[pos_bit_vacio] = '1';

                fseek(prueba, inicioBitmapBD, SEEK_SET);
                fwrite(&test_bit_bd, sizeof(BITMAP_BD), 1, prueba);

                /*Luego procedo a almacenar el apuntador en el arreglo que se creo con anterioridad*/
                int u = 0;
                for(u = 0; u < sizeof(apuntadores); u++){
                    if(apuntadores[u] == -1){
                        apuntadores[u] = nuevaPos;
                        break;
                    }
                }

            }else{

                int numero = 0;
                int contador = 0;
                char texto[25];
                char c;
                limpiar(texto, 25);

                /*Valor que me indica cuantos bloques voy a utilizar*/
                int _cantidadBloques = 0;
                cantidadBloques = (int) ceil(tamano/25);

                do{

                    if(contador < 25){

                        if(numero == 9){
                            c = numero + '0';
                            texto[contador] = c;
                            numero = 0;
                            contador++;
                        }else{
                            c = numero + '0';
                            texto[contador] = c;
                            numero++;
                            contador++;
                        }

                    }else{

                        /*Significa que ya lleno el primer array por lo que procedo a escribirlo y guardar su apuntador*/
                        fseek(prueba, inicioBitmapBD, SEEK_SET);
                        fread(&test_bit_bd, sizeof(BITMAP_BD), 1, prueba);
                        int y = 0;
                        int pos_bit_vacio = 0;

                        /*Con el bitmap obtengo la posicion libre donde puedo escribir*/
                        for(y=0; y<25; y++){
                            if(test_bit_bd.bitmap[y] == '0'){
                                pos_bit_vacio = y;
                                break;
                            }
                        }

                        /*Me posiciono en el puntero para escribir el bloque de datos que indica*/
                        int nuevaPos = inicioBitmapBD + sizeof(BITMAP_BD) + ((pos_bit_vacio + 1)*sizeof(BLOQUE_DATOS)) - sizeof(BLOQUE_DATOS);

                        /*Ahora procedo a escribir la estructura de bloque de datos*/
                        BLOQUE_DATOS test_bd = {
                            {texto[0],	texto[1],	texto[2],	texto[3],	texto[4],	texto[5],	texto[6],	texto[7],	texto[8],	texto[9],	texto[10],	texto[11],	texto[12],	texto[13],	texto[14],	texto[15],	texto[16],	texto[17],	texto[18],	texto[19],	texto[20],	texto[21],	texto[22], texto[23], texto[24]}
                        };

                        /*Me posiciono en el puntero para escribir el bloque de datos*/
                        fseek(prueba, nuevaPos, SEEK_SET);
                        fwrite(&test_bd, sizeof(BLOQUE_DATOS), 1, prueba);

                        /*Luego de escribirlo actualizo el bitmap*/
                        fseek(prueba, inicioBitmapBD, SEEK_SET);
                        fread(&test_bit_bd, sizeof(BITMAP_BD), 1, prueba);

                        test_bit_bd.bitmap[pos_bit_vacio] = '1';

                        fseek(prueba, inicioBitmapBD, SEEK_SET);
                        fwrite(&test_bit_bd, sizeof(BITMAP_BD), 1, prueba);

                        /*Luego procedo a almacenar el apuntador en el arreglo que se creo con anterioridad*/
                        int u = 0;
                        for(u = 0; u < sizeof(apuntadores); u++){
                            if(apuntadores[u] == -1){
                                apuntadores[u] = nuevaPos;
                                break;
                            }
                        }

                        /*Limpio mis variables nuevamente*/
                        limpiar(texto, 25);
                        contador = 0;
                        numero = 0;
                        _cantidadBloques++;

                    }

                }while(_cantidadBloques < cantidadBloques);

            }

        /*De lo contrario, si viene para copiar la informacion de un archivo existente*/
        }else{

            /*Actualizo mi bandera*/
            flagContenido = 1;

            char c;
            char texto[25];
            int contador = 0;
            int cantidadBytes = 0;
            limpiar(texto, 25);

            /*Procedo a abrir el archivo en modo de lectura para leer su contenido*/
            FILE *fp = fopen(content_path ,"r");

            /*Primero obtengo del ciclo la cantidad de caracteres que contiene el archivo para calcular cuantos bloque de datos necesitare*/
            if(fp == NULL){
                perror("Error al abrir el archivo.");
            }else{
                do{
                    c = fgetc(fp);

                    if(feof(fp)){
                        break;
                    }else{
                        cantidadBytes++;
                    }

                }while(1);

            }


            /*Valor que me indica cuantos bloques voy a utilizar*/
//            int _cantidadBloques = 0;
            cantidadBloques = (int) ceil(cantidadBytes/25);
            bytesContenido = cantidadBytes;


            /*De nuevo vuelvo a hacer el ciclo para leer el archivo y guardar la informacion*/
            if(fp == NULL){
                perror("Error al abrir el archivo.");
            }else{
                do{
                    c = fgetc(fp);

                    if(feof(fp)){
                        break;
                    }else{

                        if(contador < 25){
                            texto[contador] = c;
                            contador++;
                        }else{

                            /*Significa que ya lleno el primer array por lo que procedo a escribirlo y guardar su apuntador*/
                            fseek(prueba, inicioBitmapBD, SEEK_SET);
                            fread(&test_bit_bd, sizeof(BITMAP_BD), 1, prueba);
                            int y = 0;
                            int pos_bit_vacio = 0;

                            /*Con el bitmap obtengo la posicion libre donde puedo escribir*/
                            for(y=0; y<25; y++){
                                if(test_bit_bd.bitmap[y] == '0'){
                                    pos_bit_vacio = y;
                                    break;
                                }
                            }

                            /*Me posiciono en el puntero para escribir el bloque de datos que indica*/
                            int nuevaPos = inicioBitmapBD + sizeof(BITMAP_BD) + ((pos_bit_vacio + 1)*sizeof(BLOQUE_DATOS)) - sizeof(BLOQUE_DATOS);

                            /*Ahora procedo a escribir la estructura de bloque de datos*/
                            BLOQUE_DATOS test_bd = {
                                {texto[0],	texto[1],	texto[2],	texto[3],	texto[4],	texto[5],	texto[6],	texto[7],	texto[8],	texto[9],	texto[10],	texto[11],	texto[12],	texto[13],	texto[14],	texto[15],	texto[16],	texto[17],	texto[18],	texto[19],	texto[20],	texto[21],	texto[22], texto[23], texto[24]}
                            };

                            /*Me posiciono en el puntero para escribir el bloque de datos*/
                            fseek(prueba, nuevaPos, SEEK_SET);
                            fwrite(&test_bd, sizeof(BLOQUE_DATOS), 1, prueba);

                            /*Luego de escribirlo actualizo el bitmap*/
                            fseek(prueba, inicioBitmapBD, SEEK_SET);
                            fread(&test_bit_bd, sizeof(BITMAP_BD), 1, prueba);

                            test_bit_bd.bitmap[pos_bit_vacio] = '1';

                            fseek(prueba, inicioBitmapBD, SEEK_SET);
                            fwrite(&test_bit_bd, sizeof(BITMAP_BD), 1, prueba);

                            /*Luego procedo a almacenar el apuntador en el arreglo que se creo con anterioridad*/
                            int u = 0;
                            for(u = 0; u < sizeof(apuntadores); u++){
                                if(apuntadores[u] == -1){
                                    apuntadores[u] = nuevaPos;
                                    break;
                                }
                            }

                            /*Limpio mis variables nuevamente*/
                            limpiar(texto, 25);
                            contador = 0;
                            //cantidadBloques++;

                            /*Para no perder el caracter que esta en lectura, de una vez lo agrego*/
                            texto[contador] = c;

                        }


                    }

                }while(1);

                /*Verifico que no se hayan quedado caracteres en el arreglo de texto*/
                if(texto[0] != '\0'){

                    /*Significa que ya lleno el primer array por lo que procedo a escribirlo y guardar su apuntador*/
                    fseek(prueba, inicioBitmapBD, SEEK_SET);
                    fread(&test_bit_bd, sizeof(BITMAP_BD), 1, prueba);
                    int y = 0;
                    int pos_bit_vacio = 0;

                    /*Con el bitmap obtengo la posicion libre donde puedo escribir*/
                    for(y=0; y<25; y++){
                        if(test_bit_bd.bitmap[y] == '0'){
                            pos_bit_vacio = y;
                            break;
                        }
                    }

                    /*Me posiciono en el puntero para escribir el bloque de datos que indica*/
                    int nuevaPos = inicioBitmapBD + sizeof(BITMAP_BD) + ((pos_bit_vacio + 1)*sizeof(BLOQUE_DATOS)) - sizeof(BLOQUE_DATOS);

                    /*Ahora procedo a escribir la estructura de bloque de datos*/
                    BLOQUE_DATOS test_bd = {
                        {texto[0],	texto[1],	texto[2],	texto[3],	texto[4],	texto[5],	texto[6],	texto[7],	texto[8],	texto[9],	texto[10],	texto[11],	texto[12],	texto[13],	texto[14],	texto[15],	texto[16],	texto[17],	texto[18],	texto[19],	texto[20],	texto[21],	texto[22], texto[23], texto[24]}
                    };

                    /*Me posiciono en el puntero para escribir el bloque de datos*/
                    fseek(prueba, nuevaPos, SEEK_SET);
                    fwrite(&test_bd, sizeof(BLOQUE_DATOS), 1, prueba);

                    /*Luego de escribirlo actualizo el bitmap*/
                    fseek(prueba, inicioBitmapBD, SEEK_SET);
                    fread(&test_bit_bd, sizeof(BITMAP_BD), 1, prueba);

                    test_bit_bd.bitmap[pos_bit_vacio] = '1';

                    fseek(prueba, inicioBitmapBD, SEEK_SET);
                    fwrite(&test_bit_bd, sizeof(BITMAP_BD), 1, prueba);

                    /*Luego procedo a almacenar el apuntador en el arreglo que se creo con anterioridad*/
                    int u = 0;
                    for(u = 0; u < sizeof(apuntadores); u++){
                        if(apuntadores[u] == -1){
                            apuntadores[u] = nuevaPos;
                            break;
                        }
                    }

                }

            }

        }


        /*Ya que tengo escrito el texto en sus respectivos bloques de datos.. Procedo a crear los inodos donde iran esos bloques de datos*/
        fseek(prueba, inicioBitmapInodos, SEEK_SET);
        fread(&test_bit_inodo, sizeof(BITMAP_INODO), 1, prueba);
        int i = 0;
        int pos_bit_vacio = 0;

        /*Con el bitmap obtengo la posicion libre donde puedo escribir*/
        for(i=0; i<25; i++){
            if(test_bit_inodo.bitmap[i] == '0'){
                pos_bit_vacio = i;
                break;
            }
        }

        /*Me posiciono en el puntero para escribir el inodo que indica*/
        int nuevaPos = inicioBitmapInodos + sizeof(BITMAP_INODO) + ((pos_bit_vacio + 1)*sizeof(INODO)) - sizeof(INODO);

        /*Obtengo el tamaño del archivo*/
        int tamano_archivo = 0;

        /*Si la bandera de contenido indica que no venia ruta de contenido para archivo*/
        if(flagContenido == 0){
            tamano_archivo = tamano;
        }else{
            tamano_archivo = bytesContenido;
        }


        /*Escribo la estructura del inodo*/
        INODO test_inodo = {
            pos_bit_vacio,
            tamano_archivo,
            cantidadBloques,
            {apuntadores[0], apuntadores[1], apuntadores[2], apuntadores[3]},
            -1
        };

        /*Escribo en el archivo la estructura del inodo*/
        fseek(prueba, nuevaPos, SEEK_SET);
        fwrite(&test_inodo, sizeof(INODO), 1, prueba);

        /*Guardo el apuntador en donde se escribio el inodo para ponerselo al detalle de directorio*/
        int apuntadorInodo = nuevaPos;

        /*Procedo a leer en donde voy a escribir mi detalle de directorio*/
        fseek(prueba, inicioBitmapDD, SEEK_SET);
        fread(&test_bit_dd, sizeof(BITMAP_DD), 1, prueba);
        int t = 0;
        int pos_bit_vacio_DD = 0;

        /*Con el bitmap obtengo la posicion libre donde puedo escribir*/
        for(t=0; t<25; t++){
            if(test_bit_dd.bitmap[t] == '0'){
                pos_bit_vacio_DD = t;
                break;
            }
        }

        /*Me posiciono en el puntero para escribir el detalle de directorio que indica*/
        int nuevaPosDD = inicioBitmapDD + sizeof(BITMAP_DD) + ((pos_bit_vacio_DD + 1)*sizeof(DETALLE_DIRECTORIO)) - sizeof(DETALLE_DIRECTORIO);

        /*Ahora procedo a escribir la estructura de archivo (que es necesaria para el detalle de directorio) y el detalle de directorio por aparte*/
        time_t now = time(0);

        ARCHIVO test_archivo = {
            {nombre_archivo[0], nombre_archivo[1], nombre_archivo[2], nombre_archivo[3], nombre_archivo[4], nombre_archivo[5], nombre_archivo[6], nombre_archivo[7], nombre_archivo[8], nombre_archivo[9], nombre_archivo[10], nombre_archivo[11], nombre_archivo[12], nombre_archivo[13], nombre_archivo[14], nombre_archivo[15]},
            apuntadorInodo,
            now,
            now
        };

        /*Ahora procedio a escribir la estructura de detalle de directorio*/

        DETALLE_DIRECTORIO test_dd = {
            test_archivo,
            {{'\0', '\0', '\0', '\0', '\0', '\0', '\0',	'\0', '\0', '\0', '\0',	'\0', '\0', '\0', '\0'}, -1, now, now},
            {{'\0', '\0', '\0', '\0', '\0', '\0', '\0',	'\0', '\0', '\0', '\0',	'\0', '\0', '\0', '\0'}, -1, now, now},
            {{'\0', '\0', '\0', '\0', '\0', '\0', '\0',	'\0', '\0', '\0', '\0',	'\0', '\0', '\0', '\0'}, -1, now, now},
            {{'\0', '\0', '\0', '\0', '\0', '\0', '\0',	'\0', '\0', '\0', '\0',	'\0', '\0', '\0', '\0'}, -1, now, now},
            -1
        };


        /*Escribo en el archivo la estructura de DD*/
        fseek(prueba, nuevaPosDD, SEEK_SET);
        fwrite(&test_dd, sizeof(DETALLE_DIRECTORIO), 1, prueba);

        /*Luego de escribirlo actualizo el bitmap*/
        fseek(prueba, inicioBitmapDD, SEEK_SET);
        fread(&test_bit_dd, sizeof(BITMAP_DD), 1, prueba);
        test_bit_dd.bitmap[pos_bit_vacio_DD] = '1';
        fseek(prueba, inicioBitmapDD, SEEK_SET);
        fwrite(&test_bit_dd, sizeof(BITMAP_DD), 1, prueba);

        /*Luego de actualizar el bitmap, procedo a actualizar el puntero de detalle de directorio del AVD*/
        fseek(prueba, apuntadorUltimaCarpeta, SEEK_SET);
        fread(&test_avd, sizeof(AVD), 1, prueba);

        /*Le actualizo el apuntador al AVD y le coloco el de detalle de directorio que se escribio*/
        test_avd.avd_ap_detalle_directorio = nuevaPosDD;

        /*Luego de que ya cambie el valor de la posicion, lo escribo en el archivo*/
        fseek(prueba, apuntadorUltimaCarpeta, SEEK_SET);
        fwrite(&test_avd, sizeof(AVD), 1, prueba);

        /*Cierro el archivo*/
        fclose(prueba);


    }else{

        /*Si la carpeta indicada ya cuenta con un detalle de directorio*/

    }

}
