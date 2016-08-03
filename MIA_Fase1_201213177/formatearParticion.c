#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <time.h>
#include "formatearParticion.h"
#include "montarParticion.h"
#include "estructuras.h"
#include "limpiar.h"

char rutaDisco[100];
char identificador[10];
char tipoFormateo[5];
char nameParticion[16];
time_t hora_de_montaje;

void formatearParticion(char *id, char *type){

    /*Limpio las variables*/
    limpiar(rutaDisco, 100);
    limpiar(identificador, 10);
    limpiar(tipoFormateo, 5);
    limpiar(nameParticion, 16);

    /*Copio los valores del metodo a nuevos arreglos y declaro la variable tiempo para el superbloque*/
    strcpy(identificador, id);
    strcpy(tipoFormateo, type);

    /*Por medio del ID busco el path del disco entre las particiones montadas*/
    xnode **w = NULL;

    w = xx_list_search(&m, identificador);

    if(w != NULL){
        strcpy(rutaDisco, (*w)->path);
        hora_de_montaje = (*w)->hora_de_montado;
        strcpy(nameParticion, (*w)->nombreParticion);
    }

    /*Si el tipo de formateo es full*/
    if(strcmp(tipoFormateo, "full") == 0){

        /*Escribo el SUPERBLOQUE*/
        SUPERBLOQUE sp = {

            1, /*Coloco uno porque luego tengo que crear avd con el root (/)*/
            0,
            0,
            0,
            14,
            15,
            15,
            15,
            hora_de_montaje,
            hora_de_montaje, /*Arreglar este porque no es correcto*/
            1,
            201213177,
            sizeof(AVD),
            sizeof(DETALLE_DIRECTORIO),
            sizeof(INODO),
            sizeof(BLOQUE_DATOS),
            -1, /*Este valor y el siguiente los igualo a -1 aunque despues, al saber que particion es y donde ira el superbloque, lo actualizo.*/
            -1,
            -1, /*Este valor y el siguiente son los apuntadores a los detalles de directorio, son -1 porque al inicio no existe ninguno.*/
            -1,
            -1, /*Este valor y el siguiente son los apuntadores a los inodos, son -1 porque al inicio no existe ninguno.*/
            -1,
            -1, /*Este valor y el siguiente son los apuntadores a los bloques de datos, son -1 porque al inicio no existe ninguno.*/
            -1,
            0, /*Apuntador de la bitacora*/
            0, /*Apuntador de la copia del superbloque*/
            1, /*Los siguientes cuatro numeros son los apuntadores a el primer bitmap disponible, solo el primero es uno porque la primera posicion [0] ya esta ocupada por el (/)  NOTA: estos no son -1 porque apuntan a una posicion en el array de char[]*/
            0,
            0,
            0

        };

        /*Escribo el bitmap de AVD*/
        BITMAP_AVD ba = {
            {'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0'}
        };

        BITMAP_DD bit_dd = {
            {'0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0'}
        };

        BITMAP_INODO bit_inodo = {
            {'0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0'}
        };

        BITMAP_BD bit_bd = {
            {'0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0'}
        };

        /*Escribo el AVD del root (/)*/
        time_t now = time(0);

        AVD avd = {

            now,
            "/",
            {-1, -1, -1, -1, -1, -1},
            -1,
            -1

        };

        /*Ahora procedo a escribirlo todo en la particion del disco*/
        MBR test;

        FILE * prueba = fopen(rutaDisco, "r+b");
        fseek(prueba, 0, SEEK_SET);
        fread(&test, sizeof(MBR), 1, prueba);

        if(prueba != NULL){

            if(strcmp(test.mbr_partition_1.part_name, nameParticion) == 0){

                /*Lleno de espacios vacios toda la parte de la particion*/
                int inicioParticion = test.mbr_partition_1.part_start;
                int finParticion = test.mbr_partition_1.part_start + test.mbr_partition_1.part_size;
                int i = 0;
                char vacio = '\0';

                for(i = inicioParticion; i < finParticion; i++){
                    fseek(prueba, i, SEEK_SET);
                    fwrite(&vacio, 1, sizeof(vacio), prueba);
                }

                int inicioBitmapAVD = test.mbr_partition_1.part_start + sizeof(SUPERBLOQUE);
                int inicioAVD = inicioBitmapAVD + sizeof(BITMAP_AVD);
                int inicioBitmapDD = inicioAVD + (25*sizeof(AVD));
                int inicioDD = inicioBitmapDD + sizeof(BITMAP_DD);
                int inicioBitmapInodo = inicioDD + (25*sizeof(DETALLE_DIRECTORIO));
                int inicioInodos = inicioBitmapInodo + sizeof(BITMAP_INODO);
                int inicioBitmapBD = inicioInodos + (25*sizeof(INODO));
                int inicioBD = inicioBitmapBD + sizeof(BITMAP_BD);

                /*Actualizo los apuntadores del superbloque correspondientes al bitmap de avd y avd*/
                sp.sb_ap_bitmap_avd = inicioBitmapAVD;
                sp.sb_ap_avd = inicioAVD;

                /*Actualizo los apuntadores del superbloque correspondientes al bitmap de detalle de directorio y este mismo*/
                sp.sb_ap_bitmap_detalle_directorio = inicioBitmapDD;
                sp.sb_ap_detalle_directorio = inicioDD;

                /*Actualizo los apuntadores del superbloque correspondientes al bitmap de inodos y este mismo*/
                sp.sb_ap_bitmap_tabla_inodo = inicioBitmapInodo;
                sp.sb_ap_tabla_inodo = inicioInodos;

                /*Actualizo los apuntadores del superbloque correspondientes al bitmap de bloque de datos y este mismo*/
                sp.sb_ap_bitmap_bloque = inicioBitmapBD;
                sp.sb_ap_bloque = inicioBD;

                /*Escribo todos los bitmap y estructuras correspondientes al formateo*/
                fseek(prueba, test.mbr_partition_1.part_start, SEEK_SET);
                fwrite(&sp, sizeof(SUPERBLOQUE), 1, prueba);

                fseek(prueba, inicioBitmapAVD, SEEK_SET);
                fwrite(&ba, sizeof(BITMAP_AVD), 1, prueba);

                fseek(prueba, inicioAVD, SEEK_SET);
                fwrite(&avd, sizeof(AVD), 1, prueba);

                fseek(prueba, inicioBitmapDD, SEEK_SET);
                fwrite(&bit_dd, sizeof(BITMAP_DD), 1, prueba);

                fseek(prueba, inicioBitmapInodo, SEEK_SET);
                fwrite(&bit_inodo, sizeof(BITMAP_INODO), 1, prueba);

                fseek(prueba, inicioBitmapBD, SEEK_SET);
                fwrite(&bit_bd, sizeof(BITMAP_BD), 1, prueba);

                fflush(prueba);
                fclose(prueba);

                printf("Formateo realizado correctamente!\n");
                printf("***********************************************************************\n");

            }else if(strcmp(test.mbr_partition_2.part_name, nameParticion) == 0){

                /*Lleno de espacios vacios toda la parte de la particion*/
                int inicioParticion = test.mbr_partition_2.part_start;
                int finParticion = test.mbr_partition_2.part_start + test.mbr_partition_2.part_size;
                int i = 0;
                char vacio = '\0';

                for(i = inicioParticion; i < finParticion; i++){
                    fseek(prueba, i, SEEK_SET);
                    fwrite(&vacio, 1, sizeof(vacio), prueba);
                }

                int inicioBitmapAVD = test.mbr_partition_2.part_start + sizeof(SUPERBLOQUE);
                int inicioAVD = inicioBitmapAVD + sizeof(BITMAP_AVD);
                int inicioBitmapDD = inicioAVD + (25*sizeof(AVD));
                int inicioDD = inicioBitmapDD + sizeof(BITMAP_DD);
                int inicioBitmapInodo = inicioDD + (25*sizeof(DETALLE_DIRECTORIO));
                int inicioInodos = inicioBitmapInodo + sizeof(BITMAP_INODO);
                int inicioBitmapBD = inicioInodos + (25*sizeof(INODO));
                int inicioBD = inicioBitmapBD + sizeof(BITMAP_BD);

                /*Actualizo los apuntadores del superbloque correspondientes al bitmap de avd y avd*/
                sp.sb_ap_bitmap_avd = inicioBitmapAVD;
                sp.sb_ap_avd = inicioAVD;

                /*Actualizo los apuntadores del superbloque correspondientes al bitmap de detalle de directorio y este mismo*/
                sp.sb_ap_bitmap_detalle_directorio = inicioBitmapDD;
                sp.sb_ap_detalle_directorio = inicioDD;

                /*Actualizo los apuntadores del superbloque correspondientes al bitmap de inodos y este mismo*/
                sp.sb_ap_bitmap_tabla_inodo = inicioBitmapInodo;
                sp.sb_ap_tabla_inodo = inicioInodos;

                /*Actualizo los apuntadores del superbloque correspondientes al bitmap de bloque de datos y este mismo*/
                sp.sb_ap_bitmap_bloque = inicioBitmapBD;
                sp.sb_ap_bloque = inicioBD;

                /*Escribo todos los bitmap y estructuras correspondientes al formateo*/
                fseek(prueba, test.mbr_partition_2.part_start, SEEK_SET);
                fwrite(&sp, sizeof(SUPERBLOQUE), 1, prueba);

                fseek(prueba, inicioBitmapAVD, SEEK_SET);
                fwrite(&ba, sizeof(BITMAP_AVD), 1, prueba);

                fseek(prueba, inicioAVD, SEEK_SET);
                fwrite(&avd, sizeof(AVD), 1, prueba);

                fseek(prueba, inicioBitmapDD, SEEK_SET);
                fwrite(&bit_dd, sizeof(BITMAP_DD), 1, prueba);

                fseek(prueba, inicioBitmapInodo, SEEK_SET);
                fwrite(&bit_inodo, sizeof(BITMAP_INODO), 1, prueba);

                fseek(prueba, inicioBitmapBD, SEEK_SET);
                fwrite(&bit_bd, sizeof(BITMAP_BD), 1, prueba);

                fflush(prueba);
                fclose(prueba);

                printf("Formateo realizado correctamente!\n");
                printf("***********************************************************************\n");

            }else if(strcmp(test.mbr_partition_3.part_name, nameParticion) == 0){

                /*Lleno de espacios vacios toda la parte de la particion*/
                int inicioParticion = test.mbr_partition_3.part_start;
                int finParticion = test.mbr_partition_3.part_start + test.mbr_partition_3.part_size;
                int i = 0;
                char vacio = '\0';

                for(i = inicioParticion; i < finParticion; i++){
                    fseek(prueba, i, SEEK_SET);
                    fwrite(&vacio, 1, sizeof(vacio), prueba);
                }

                int inicioBitmapAVD = test.mbr_partition_3.part_start + sizeof(SUPERBLOQUE);
                int inicioAVD = inicioBitmapAVD + sizeof(BITMAP_AVD);
                int inicioBitmapDD = inicioAVD + (25*sizeof(AVD));
                int inicioDD = inicioBitmapDD + sizeof(BITMAP_DD);
                int inicioBitmapInodo = inicioDD + (25*sizeof(DETALLE_DIRECTORIO));
                int inicioInodos = inicioBitmapInodo + sizeof(BITMAP_INODO);
                int inicioBitmapBD = inicioInodos + (25*sizeof(INODO));
                int inicioBD = inicioBitmapBD + sizeof(BITMAP_BD);

                /*Actualizo los apuntadores del superbloque correspondientes al bitmap de avd y avd*/
                sp.sb_ap_bitmap_avd = inicioBitmapAVD;
                sp.sb_ap_avd = inicioAVD;

                /*Actualizo los apuntadores del superbloque correspondientes al bitmap de detalle de directorio y este mismo*/
                sp.sb_ap_bitmap_detalle_directorio = inicioBitmapDD;
                sp.sb_ap_detalle_directorio = inicioDD;

                /*Actualizo los apuntadores del superbloque correspondientes al bitmap de inodos y este mismo*/
                sp.sb_ap_bitmap_tabla_inodo = inicioBitmapInodo;
                sp.sb_ap_tabla_inodo = inicioInodos;

                /*Actualizo los apuntadores del superbloque correspondientes al bitmap de bloque de datos y este mismo*/
                sp.sb_ap_bitmap_bloque = inicioBitmapBD;
                sp.sb_ap_bloque = inicioBD;

                /*Escribo todos los bitmap y estructuras correspondientes al formateo*/
                fseek(prueba, test.mbr_partition_3.part_start, SEEK_SET);
                fwrite(&sp, sizeof(SUPERBLOQUE), 1, prueba);

                fseek(prueba, inicioBitmapAVD, SEEK_SET);
                fwrite(&ba, sizeof(BITMAP_AVD), 1, prueba);

                fseek(prueba, inicioAVD, SEEK_SET);
                fwrite(&avd, sizeof(AVD), 1, prueba);

                fseek(prueba, inicioBitmapDD, SEEK_SET);
                fwrite(&bit_dd, sizeof(BITMAP_DD), 1, prueba);

                fseek(prueba, inicioBitmapInodo, SEEK_SET);
                fwrite(&bit_inodo, sizeof(BITMAP_INODO), 1, prueba);

                fseek(prueba, inicioBitmapBD, SEEK_SET);
                fwrite(&bit_bd, sizeof(BITMAP_BD), 1, prueba);

                fflush(prueba);
                fclose(prueba);

                printf("Formateo realizado correctamente!\n");
                printf("***********************************************************************\n");

            }else if(strcmp(test.mbr_partition_4.part_name, nameParticion) == 0){

                /*Lleno de espacios vacios toda la parte de la particion*/
                int inicioParticion = test.mbr_partition_4.part_start;
                int finParticion = test.mbr_partition_4.part_start + test.mbr_partition_4.part_size;
                int i = 0;
                char vacio = '\0';

                for(i = inicioParticion; i < finParticion; i++){
                    fseek(prueba, i, SEEK_SET);
                    fwrite(&vacio, 1, sizeof(vacio), prueba);
                }

                int inicioBitmapAVD = test.mbr_partition_4.part_start + sizeof(SUPERBLOQUE);
                int inicioAVD = inicioBitmapAVD + sizeof(BITMAP_AVD);
                int inicioBitmapDD = inicioAVD + (25*sizeof(AVD));
                int inicioDD = inicioBitmapDD + sizeof(BITMAP_DD);
                int inicioBitmapInodo = inicioDD + (25*sizeof(DETALLE_DIRECTORIO));
                int inicioInodos = inicioBitmapInodo + sizeof(BITMAP_INODO);
                int inicioBitmapBD = inicioInodos + (25*sizeof(INODO));
                int inicioBD = inicioBitmapBD + sizeof(BITMAP_BD);

                /*Actualizo los apuntadores del superbloque correspondientes al bitmap de avd y avd*/
                sp.sb_ap_bitmap_avd = inicioBitmapAVD;
                sp.sb_ap_avd = inicioAVD;

                /*Actualizo los apuntadores del superbloque correspondientes al bitmap de detalle de directorio y este mismo*/
                sp.sb_ap_bitmap_detalle_directorio = inicioBitmapDD;
                sp.sb_ap_detalle_directorio = inicioDD;

                /*Actualizo los apuntadores del superbloque correspondientes al bitmap de inodos y este mismo*/
                sp.sb_ap_bitmap_tabla_inodo = inicioBitmapInodo;
                sp.sb_ap_tabla_inodo = inicioInodos;

                /*Actualizo los apuntadores del superbloque correspondientes al bitmap de bloque de datos y este mismo*/
                sp.sb_ap_bitmap_bloque = inicioBitmapBD;
                sp.sb_ap_bloque = inicioBD;

                /*Escribo todos los bitmap y estructuras correspondientes al formateo*/
                fseek(prueba, test.mbr_partition_4.part_start, SEEK_SET);
                fwrite(&sp, sizeof(SUPERBLOQUE), 1, prueba);

                fseek(prueba, inicioBitmapAVD, SEEK_SET);
                fwrite(&ba, sizeof(BITMAP_AVD), 1, prueba);

                fseek(prueba, inicioAVD, SEEK_SET);
                fwrite(&avd, sizeof(AVD), 1, prueba);

                fseek(prueba, inicioBitmapDD, SEEK_SET);
                fwrite(&bit_dd, sizeof(BITMAP_DD), 1, prueba);

                fseek(prueba, inicioBitmapInodo, SEEK_SET);
                fwrite(&bit_inodo, sizeof(BITMAP_INODO), 1, prueba);

                fseek(prueba, inicioBitmapBD, SEEK_SET);
                fwrite(&bit_bd, sizeof(BITMAP_BD), 1, prueba);

                fflush(prueba);
                fclose(prueba);

                printf("Formateo tipo 'full' realizado correctamente!\n");
                printf("***********************************************************************\n");

            }

        }

    /*De lo contrario, si el tipo de formateo es fast*/
    }else if(strcmp(tipoFormateo, "fast") == 0){

        MBR test;

        BITMAP_AVD ba;
        BITMAP_DD bdd;
        BITMAP_INODO bin;
        BITMAP_BD bbd;

        SUPERBLOQUE sb = {

            1, /*Coloco uno porque luego tengo que crear avd con el root (/)*/
            0,
            0,
            0,
            14,
            15,
            15,
            15,
            hora_de_montaje,
            hora_de_montaje, /*Arreglar este porque no es correcto*/
            1,
            201213177,
            sizeof(AVD),
            sizeof(DETALLE_DIRECTORIO),
            sizeof(INODO),
            sizeof(BLOQUE_DATOS),
            -1, /*Este valor y el siguiente los igualo a -1 aunque despues, al saber que particion es y donde ira el superbloque, lo actualizo.*/
            -1,
            -1, /*Este valor y el siguiente son los apuntadores a los detalles de directorio, son -1 porque al inicio no existe ninguno.*/
            -1,
            -1, /*Este valor y el siguiente son los apuntadores a los inodos, son -1 porque al inicio no existe ninguno.*/
            -1,
            -1, /*Este valor y el siguiente son los apuntadores a los bloques de datos, son -1 porque al inicio no existe ninguno.*/
            -1,
            0, /*Apuntador de la bitacora*/
            0, /*Apuntador de la copia del superbloque*/
            1, /*Los siguientes cuatro numeros son los apuntadores a el primer bitmap disponible, solo el primero es uno porque la primera posicion [0] ya esta ocupada por el (/)  NOTA: estos no son -1 porque apuntan a una posicion en el array de char[]*/
            0,
            0,
            0

        };


        FILE * prueba = fopen(rutaDisco, "r+b");
        fseek(prueba, 0, SEEK_SET);
        fread(&test, sizeof(MBR), 1, prueba);

        if(prueba != NULL){

            if(strcmp(test.mbr_partition_1.part_name, nameParticion) == 0){

                int inicioBitmapAVD = test.mbr_partition_1.part_start + sizeof(SUPERBLOQUE);
                int inicioAVD = inicioBitmapAVD + sizeof(BITMAP_AVD);
                int inicioBitmapDD = inicioAVD + (25*sizeof(AVD));
                int inicioDD = inicioBitmapDD + sizeof(BITMAP_DD);
                int inicioBitmapInodo = inicioDD + (25*sizeof(DETALLE_DIRECTORIO));
                int inicioInodos = inicioBitmapInodo + sizeof(BITMAP_INODO);
                int inicioBitmapBD = inicioInodos + (25*sizeof(INODO));

                /*Escribo de nuevo el superbloque vacio o inicial*/
                fseek(prueba, test.mbr_partition_1.part_start, SEEK_SET);
                fwrite(&sb, sizeof(SUPERBLOQUE), 1, prueba);

                /*AVD*/
                /*En esta parte, leo el bitmap de AVD's y lo vacio*/
                fseek(prueba, inicioBitmapAVD, SEEK_SET);
                fread(&ba, sizeof(BITMAP_AVD), 1, prueba);
                int i = 0;

                for(i = 0; i < 25; i++){
                    if(i == 0){
                        ba.bitmap[i] = '1';
                    }else{
                        ba.bitmap[i] = '0';
                    }
                }

                fseek(prueba, inicioBitmapAVD, SEEK_SET);
                fwrite(&ba, sizeof(BITMAP_AVD), 1, prueba);


                /*DETALLE DE DIRECTORIO*/
                /*En esta parte, leo el bitmap de detalle de directorio y lo vacio tanto la estructura como el espacio que ocupan los 15 DD's que puedo escribir*/
                fseek(prueba, inicioBitmapDD, SEEK_SET);
                fread(&bdd, sizeof(BITMAP_DD), 1, prueba);
                int k = 0;

                for(k = 0; k < 25; k++){
                    bdd.bitmap[k] = '0';
                }

                fseek(prueba, inicioBitmapDD, SEEK_SET);
                fwrite(&bdd, sizeof(BITMAP_DD), 1, prueba);


                /*TABLA DE INODOS*/
                /*En esta parte, leo el bitmap de detalle de directorio y lo vacio tanto la estructura como el espacio que ocupan los 15 INODOS's que puedo escribir*/
                fseek(prueba, inicioBitmapInodo, SEEK_SET);
                fread(&bin, sizeof(BITMAP_INODO), 1, prueba);
                int n = 0;

                for(n = 0; n < 25; n++){
                    bin.bitmap[n] = '0';
                }

                fseek(prueba, inicioBitmapInodo, SEEK_SET);
                fwrite(&bin, sizeof(BITMAP_INODO), 1, prueba);


                /*BLOQUE DE DATOS*/
                /*En esta parte, leo el bitmap de detalle de directorio y lo vacio tanto la estructura como el espacio que ocupan los 15 BLOQUES_DE_DATOS's que puedo escribir*/
                fseek(prueba, inicioBitmapBD, SEEK_SET);
                fread(&bbd, sizeof(BITMAP_BD), 1, prueba);
                int p = 0;

                for(p = 0; p < 25; p++){
                    bbd.bitmap[p] = '0';
                }

                fseek(prueba, inicioBitmapBD, SEEK_SET);
                fwrite(&bbd, sizeof(BITMAP_BD), 1, prueba);

                fclose(prueba);

                printf("Formateo tipo 'fast' realizado correctamente!\n");
                printf("***********************************************************************\n");


            }else if(strcmp(test.mbr_partition_2.part_name, nameParticion) == 0){

                int inicioBitmapAVD = test.mbr_partition_2.part_start + sizeof(SUPERBLOQUE);
                int inicioAVD = inicioBitmapAVD + sizeof(BITMAP_AVD);
                int inicioBitmapDD = inicioAVD + (25*sizeof(AVD));
                int inicioDD = inicioBitmapDD + sizeof(BITMAP_DD);
                int inicioBitmapInodo = inicioDD + (25*sizeof(DETALLE_DIRECTORIO));
                int inicioInodos = inicioBitmapInodo + sizeof(BITMAP_INODO);
                int inicioBitmapBD = inicioInodos + (25*sizeof(INODO));

                /*Escribo de nuevo el superbloque vacio o inicial*/
                fseek(prueba, test.mbr_partition_2.part_start, SEEK_SET);
                fwrite(&sb, sizeof(SUPERBLOQUE), 1, prueba);

                /*AVD*/
                /*En esta parte, leo el bitmap de AVD's y lo vacio*/
                fseek(prueba, inicioBitmapAVD, SEEK_SET);
                fread(&ba, sizeof(BITMAP_AVD), 1, prueba);
                int i = 0;

                for(i = 0; i < 25; i++){
                    if(i == 0){
                        ba.bitmap[i] = '1';
                    }else{
                        ba.bitmap[i] = '0';
                    }
                }

                fseek(prueba, inicioBitmapAVD, SEEK_SET);
                fwrite(&ba, sizeof(BITMAP_AVD), 1, prueba);


                /*DETALLE DE DIRECTORIO*/
                /*En esta parte, leo el bitmap de detalle de directorio y lo vacio tanto la estructura como el espacio que ocupan los 15 DD's que puedo escribir*/
                fseek(prueba, inicioBitmapDD, SEEK_SET);
                fread(&bdd, sizeof(BITMAP_DD), 1, prueba);
                int k = 0;

                for(k = 0; k < 25; k++){
                    bdd.bitmap[k] = '0';
                }

                fseek(prueba, inicioBitmapDD, SEEK_SET);
                fwrite(&bdd, sizeof(BITMAP_DD), 1, prueba);


                /*TABLA DE INODOS*/
                /*En esta parte, leo el bitmap de detalle de directorio y lo vacio tanto la estructura como el espacio que ocupan los 15 INODOS's que puedo escribir*/
                fseek(prueba, inicioBitmapInodo, SEEK_SET);
                fread(&bin, sizeof(BITMAP_INODO), 1, prueba);
                int n = 0;

                for(n = 0; n < 25; n++){
                    bin.bitmap[n] = '0';
                }

                fseek(prueba, inicioBitmapInodo, SEEK_SET);
                fwrite(&bin, sizeof(BITMAP_INODO), 1, prueba);


                /*BLOQUE DE DATOS*/
                /*En esta parte, leo el bitmap de detalle de directorio y lo vacio tanto la estructura como el espacio que ocupan los 15 BLOQUES_DE_DATOS's que puedo escribir*/
                fseek(prueba, inicioBitmapBD, SEEK_SET);
                fread(&bbd, sizeof(BITMAP_BD), 1, prueba);
                int p = 0;

                for(p = 0; p < 25; p++){
                    bbd.bitmap[p] = '0';
                }

                fseek(prueba, inicioBitmapBD, SEEK_SET);
                fwrite(&bbd, sizeof(BITMAP_BD), 1, prueba);

                fclose(prueba);

                printf("Formateo tipo 'fast' realizado correctamente!\n");
                printf("***********************************************************************\n");

            }else if(strcmp(test.mbr_partition_3.part_name, nameParticion) == 0){

                int inicioBitmapAVD = test.mbr_partition_3.part_start + sizeof(SUPERBLOQUE);
                int inicioAVD = inicioBitmapAVD + sizeof(BITMAP_AVD);
                int inicioBitmapDD = inicioAVD + (25*sizeof(AVD));
                int inicioDD = inicioBitmapDD + sizeof(BITMAP_DD);
                int inicioBitmapInodo = inicioDD + (25*sizeof(DETALLE_DIRECTORIO));
                int inicioInodos = inicioBitmapInodo + sizeof(BITMAP_INODO);
                int inicioBitmapBD = inicioInodos + (25*sizeof(INODO));

                /*Escribo de nuevo el superbloque vacio o inicial*/
                fseek(prueba, test.mbr_partition_3.part_start, SEEK_SET);
                fwrite(&sb, sizeof(SUPERBLOQUE), 1, prueba);

                /*AVD*/
                /*En esta parte, leo el bitmap de AVD's y lo vacio*/
                fseek(prueba, inicioBitmapAVD, SEEK_SET);
                fread(&ba, sizeof(BITMAP_AVD), 1, prueba);
                int i = 0;

                for(i = 0; i < 25; i++){
                    if(i == 0){
                        ba.bitmap[i] = '1';
                    }else{
                        ba.bitmap[i] = '0';
                    }
                }

                fseek(prueba, inicioBitmapAVD, SEEK_SET);
                fwrite(&ba, sizeof(BITMAP_AVD), 1, prueba);


                /*DETALLE DE DIRECTORIO*/
                /*En esta parte, leo el bitmap de detalle de directorio y lo vacio tanto la estructura como el espacio que ocupan los 15 DD's que puedo escribir*/
                fseek(prueba, inicioBitmapDD, SEEK_SET);
                fread(&bdd, sizeof(BITMAP_DD), 1, prueba);
                int k = 0;

                for(k = 0; k < 25; k++){
                    bdd.bitmap[k] = '0';
                }

                fseek(prueba, inicioBitmapDD, SEEK_SET);
                fwrite(&bdd, sizeof(BITMAP_DD), 1, prueba);


                /*TABLA DE INODOS*/
                /*En esta parte, leo el bitmap de detalle de directorio y lo vacio tanto la estructura como el espacio que ocupan los 15 INODOS's que puedo escribir*/
                fseek(prueba, inicioBitmapInodo, SEEK_SET);
                fread(&bin, sizeof(BITMAP_INODO), 1, prueba);
                int n = 0;

                for(n = 0; n < 25; n++){
                    bin.bitmap[n] = '0';
                }

                fseek(prueba, inicioBitmapInodo, SEEK_SET);
                fwrite(&bin, sizeof(BITMAP_INODO), 1, prueba);


                /*BLOQUE DE DATOS*/
                /*En esta parte, leo el bitmap de detalle de directorio y lo vacio tanto la estructura como el espacio que ocupan los 15 BLOQUES_DE_DATOS's que puedo escribir*/
                fseek(prueba, inicioBitmapBD, SEEK_SET);
                fread(&bbd, sizeof(BITMAP_BD), 1, prueba);
                int p = 0;

                for(p = 0; p < 25; p++){
                    bbd.bitmap[p] = '0';
                }

                fseek(prueba, inicioBitmapBD, SEEK_SET);
                fwrite(&bbd, sizeof(BITMAP_BD), 1, prueba);

                fclose(prueba);

                printf("Formateo tipo 'fast' realizado correctamente!\n");
                printf("***********************************************************************\n");

            }else if(strcmp(test.mbr_partition_4.part_name, nameParticion) == 0){

                int inicioBitmapAVD = test.mbr_partition_4.part_start + sizeof(SUPERBLOQUE);
                int inicioAVD = inicioBitmapAVD + sizeof(BITMAP_AVD);
                int inicioBitmapDD = inicioAVD + (25*sizeof(AVD));
                int inicioDD = inicioBitmapDD + sizeof(BITMAP_DD);
                int inicioBitmapInodo = inicioDD + (25*sizeof(DETALLE_DIRECTORIO));
                int inicioInodos = inicioBitmapInodo + sizeof(BITMAP_INODO);
                int inicioBitmapBD = inicioInodos + (25*sizeof(INODO));

                /*Escribo de nuevo el superbloque vacio o inicial*/
                fseek(prueba, test.mbr_partition_4.part_start, SEEK_SET);
                fwrite(&sb, sizeof(SUPERBLOQUE), 1, prueba);

                /*AVD*/
                /*En esta parte, leo el bitmap de AVD's y lo vacio*/
                fseek(prueba, inicioBitmapAVD, SEEK_SET);
                fread(&ba, sizeof(BITMAP_AVD), 1, prueba);
                int i = 0;

                for(i = 0; i < 25; i++){
                    if(i == 0){
                        ba.bitmap[i] = '1';
                    }else{
                        ba.bitmap[i] = '0';
                    }
                }

                fseek(prueba, inicioBitmapAVD, SEEK_SET);
                fwrite(&ba, sizeof(BITMAP_AVD), 1, prueba);


                /*DETALLE DE DIRECTORIO*/
                /*En esta parte, leo el bitmap de detalle de directorio y lo vacio tanto la estructura como el espacio que ocupan los 15 DD's que puedo escribir*/
                fseek(prueba, inicioBitmapDD, SEEK_SET);
                fread(&bdd, sizeof(BITMAP_DD), 1, prueba);
                int k = 0;

                for(k = 0; k < 25; k++){
                    bdd.bitmap[k] = '0';
                }

                fseek(prueba, inicioBitmapDD, SEEK_SET);
                fwrite(&bdd, sizeof(BITMAP_DD), 1, prueba);


                /*TABLA DE INODOS*/
                /*En esta parte, leo el bitmap de detalle de directorio y lo vacio tanto la estructura como el espacio que ocupan los 15 INODOS's que puedo escribir*/
                fseek(prueba, inicioBitmapInodo, SEEK_SET);
                fread(&bin, sizeof(BITMAP_INODO), 1, prueba);
                int n = 0;

                for(n = 0; n < 25; n++){
                    bin.bitmap[n] = '0';
                }

                fseek(prueba, inicioBitmapInodo, SEEK_SET);
                fwrite(&bin, sizeof(BITMAP_INODO), 1, prueba);


                /*BLOQUE DE DATOS*/
                /*En esta parte, leo el bitmap de detalle de directorio y lo vacio tanto la estructura como el espacio que ocupan los 15 BLOQUES_DE_DATOS's que puedo escribir*/
                fseek(prueba, inicioBitmapBD, SEEK_SET);
                fread(&bbd, sizeof(BITMAP_BD), 1, prueba);
                int p = 0;

                for(p = 0; p < 25; p++){
                    bbd.bitmap[p] = '0';
                }

                fseek(prueba, inicioBitmapBD, SEEK_SET);
                fwrite(&bbd, sizeof(BITMAP_BD), 1, prueba);

                fclose(prueba);

                printf("Formateo tipo 'fast' realizado correctamente!\n");
                printf("***********************************************************************\n");

            }

        }

    }

}




































