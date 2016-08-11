#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "crearParticionExtendida.h"

struct ebr {
    char part_status;
    char part_fit;
    int part_start;
    int part_size;
    int part_next;
    char part_name[16];
};

struct partition {
    char part_status;
    char part_type;
    char part_fit;
    int part_start;
    int part_size;
    char part_name[16];
};

struct mbr {
    int mbr_tamano;
    time_t mbr_fecha_creacion;
    int mbr_disk_signature;
    struct partition mbr_partition_1;
    struct partition mbr_partition_2;
    struct partition mbr_partition_3;
    struct partition mbr_partition_4;
};

void crearParticionExtendida(int size, char unit, char * path, char type, char fit, int num_add, char * name, char * borrar){

    /*Primero valido en el MBR que el disco no contenga una particion extendida ya que solo pueden contar con una*/
    struct mbr test;

    FILE * prueba = fopen(path, "r+b");
    fseek(prueba, 0, SEEK_SET);
    fread(&test, sizeof(test), 1, prueba);

    if(test.mbr_partition_1.part_status != 'A'){

        printf("///////////////////////////////////////////////////////////////\n");
        printf("Antes de la actualizacion:\n");
        printf("Status: %c\n", test.mbr_partition_1.part_status);
        printf("Type: %c\n", test.mbr_partition_1.part_type);
        printf("Fit: %c\n", test.mbr_partition_1.part_fit);
        printf("Start: %d\n", test.mbr_partition_1.part_start);
        printf("Size: %d\n", test.mbr_partition_1.part_size);
        printf("Name: %s\n", test.mbr_partition_1.part_name);
        printf("///////////////////////////////////////////////////////////////\n");

        /*STATUS*/
        test.mbr_partition_1.part_status = 'A';

        /*TYPE*/
        test.mbr_partition_1.part_type = 'E';

        /*FIT*/
        test.mbr_partition_1.part_fit = fit;

        /*START*/
        test.mbr_partition_1.part_start = sizeof(test);

        /*SIZE*/
        if(unit == 'B'){
            test.mbr_partition_1.part_size = size;
        }else if(unit == 'K'){
            test.mbr_partition_1.part_size = size*1024;
        }else if(unit == 'M'){
            test.mbr_partition_1.part_size = size*1048576;
        }

        /*NAME*/
        strncpy(test.mbr_partition_1.part_name, name, 16);

        printf("///////////////////////////////////////////////////////////////\n");
        printf("Despues de la actualizacion:\n");
        printf("Status: %c\n", test.mbr_partition_1.part_status);
        printf("Type: %c\n", test.mbr_partition_1.part_type);
        printf("Fit: %c\n", test.mbr_partition_1.part_fit);
        printf("Start: %d\n", test.mbr_partition_1.part_start);
        printf("Size: %d\n", test.mbr_partition_1.part_size);
        printf("Name: %s\n", test.mbr_partition_1.part_name);
        printf("///////////////////////////////////////////////////////////////\n");


        /*Creo el EBR que se crea junto con la partición*/
        struct ebr particion_ebr = {
            'D',
            'X',
            0,
            0,
            -1,
            "NONE"
        };

        /*Escribo el EBR*/
        fseek(prueba, sizeof(test), SEEK_SET);
        fwrite(&particion_ebr, sizeof(particion_ebr), 1, prueba);

        /*Agrego los cambios al MBR*/
        fseek(prueba, 0, SEEK_SET);
        fwrite(&test, sizeof(test), 1, prueba);

        /*Cierro los archivos*/
        fflush(prueba);
        fclose(prueba);

        printf("********************************************************************\n");
        printf("Particion creada exitosamente!\n");
        printf("********************************************************************\n");


    }else if(test.mbr_partition_2.part_status != 'A'){

        printf("///////////////////////////////////////////////////////////////\n");
        printf("Antes de la actualizacion:\n");
        printf("Status: %c\n", test.mbr_partition_2.part_status);
        printf("Type: %c\n", test.mbr_partition_2.part_type);
        printf("Fit: %c\n", test.mbr_partition_2.part_fit);
        printf("Start: %d\n", test.mbr_partition_2.part_start);
        printf("Size: %d\n", test.mbr_partition_2.part_size);
        printf("Name: %s\n", test.mbr_partition_2.part_name);
        printf("///////////////////////////////////////////////////////////////\n");

        /*STATUS*/
        test.mbr_partition_2.part_status = 'A';

        /*TYPE*/
        test.mbr_partition_2.part_type = 'E';

        /*FIT*/
        test.mbr_partition_2.part_fit = fit;

        /*START*/
        test.mbr_partition_2.part_start = test.mbr_partition_1.part_start + test.mbr_partition_1.part_size;

        /*SIZE*/
        if(unit == 'B'){
            test.mbr_partition_2.part_size = size;
        }else if(unit == 'K'){
            test.mbr_partition_2.part_size = size*1024;
        }else if(unit == 'M'){
            test.mbr_partition_2.part_size = size*1048576;
        }

        /*NAME*/
        strncpy(test.mbr_partition_2.part_name, name, 16);

        printf("///////////////////////////////////////////////////////////////\n");
        printf("Despues de la actualizacion:\n");
        printf("Status: %c\n", test.mbr_partition_2.part_status);
        printf("Type: %c\n", test.mbr_partition_2.part_type);
        printf("Fit: %c\n", test.mbr_partition_2.part_fit);
        printf("Start: %d\n", test.mbr_partition_2.part_start);
        printf("Size: %d\n", test.mbr_partition_2.part_size);
        printf("Name: %s\n", test.mbr_partition_2.part_name);
        printf("///////////////////////////////////////////////////////////////\n");

        /*Creo el EBR que se crea junto con la partición*/
        struct ebr particion_ebr = {
            'D',
            'X',
            0,
            0,
            -1,
            "NONE"
        };

        /*Escribo el EBR*/
        fseek(prueba, test.mbr_partition_1.part_start + test.mbr_partition_1.part_size, SEEK_SET);
        fwrite(&particion_ebr, sizeof(particion_ebr), 1, prueba);

        /*Agrego los cambios al MBR*/
        fseek(prueba, 0, SEEK_SET);
        fwrite(&test, sizeof(test), 1, prueba);

        /*Cierro los archivos*/
        fflush(prueba);
        fclose(prueba);

        printf("********************************************************************\n");
        printf("Particion creada exitosamente!\n");
        printf("********************************************************************\n");

    }else if(test.mbr_partition_3.part_status != 'A'){

        printf("///////////////////////////////////////////////////////////////\n");
        printf("Antes de la actualizacion:\n");
        printf("Status: %c\n", test.mbr_partition_3.part_status);
        printf("Type: %c\n", test.mbr_partition_3.part_type);
        printf("Fit: %c\n", test.mbr_partition_3.part_fit);
        printf("Start: %d\n", test.mbr_partition_3.part_start);
        printf("Size: %d\n", test.mbr_partition_3.part_size);
        printf("Name: %s\n", test.mbr_partition_3.part_name);
        printf("///////////////////////////////////////////////////////////////\n");

        /*STATUS*/
        test.mbr_partition_3.part_status = 'A';

        /*TYPE*/
        test.mbr_partition_3.part_type = 'E';

        /*FIT*/
        test.mbr_partition_3.part_fit = fit;

        /*START*/
        test.mbr_partition_3.part_start = test.mbr_partition_2.part_start + test.mbr_partition_2.part_size;

        /*SIZE*/
        if(unit == 'B'){
            test.mbr_partition_3.part_size = size;
        }else if(unit == 'K'){
            test.mbr_partition_3.part_size = size*1024;
        }else if(unit == 'M'){
            test.mbr_partition_3.part_size = size*1048576;
        }

        /*NAME*/
        strncpy(test.mbr_partition_3.part_name, name, 16);

        printf("///////////////////////////////////////////////////////////////\n");
        printf("Despues de la actualizacion:\n");
        printf("Status: %c\n", test.mbr_partition_3.part_status);
        printf("Type: %c\n", test.mbr_partition_3.part_type);
        printf("Fit: %c\n", test.mbr_partition_3.part_fit);
        printf("Start: %d\n", test.mbr_partition_3.part_start);
        printf("Size: %d\n", test.mbr_partition_3.part_size);
        printf("Name: %s\n", test.mbr_partition_3.part_name);
        printf("///////////////////////////////////////////////////////////////\n");

        /*Creo el EBR que se crea junto con la partición*/
        struct ebr particion_ebr = {
            'D',
            'X',
            0,
            0,
            -1,
            "NONE"
        };

        /*Escribo el EBR*/
        fseek(prueba, test.mbr_partition_2.part_start + test.mbr_partition_2.part_size, SEEK_SET);
        fwrite(&particion_ebr, sizeof(particion_ebr), 1, prueba);

        /*Agrego los cambios al MBR*/
        fseek(prueba, 0, SEEK_SET);
        fwrite(&test, sizeof(test), 1, prueba);

        /*Cierro los archivos*/
        fflush(prueba);
        fclose(prueba);

        printf("********************************************************************\n");
        printf("Particion creada exitosamente!\n");
        printf("********************************************************************\n");

    }else if(test.mbr_partition_4.part_status != 'A'){

        printf("///////////////////////////////////////////////////////////////\n");
        printf("Antes de la actualizacion:\n");
        printf("Status: %c\n", test.mbr_partition_4.part_status);
        printf("Type: %c\n", test.mbr_partition_4.part_type);
        printf("Fit: %c\n", test.mbr_partition_4.part_fit);
        printf("Start: %d\n", test.mbr_partition_4.part_start);
        printf("Size: %d\n", test.mbr_partition_4.part_size);
        printf("Name: %s\n", test.mbr_partition_4.part_name);
        printf("///////////////////////////////////////////////////////////////\n");

        /*STATUS*/
        test.mbr_partition_4.part_status = 'A';

        /*TYPE*/
        test.mbr_partition_4.part_type = 'E';

        /*FIT*/
        test.mbr_partition_4.part_fit = fit;

        /*START*/
        test.mbr_partition_4.part_start = test.mbr_partition_3.part_start + test.mbr_partition_3.part_size;

        /*SIZE*/
        if(unit == 'B'){
            test.mbr_partition_4.part_size = size;
        }else if(unit == 'K'){
            test.mbr_partition_4.part_size = size*1024;
        }else if(unit == 'M'){
            test.mbr_partition_4.part_size = size*1048576;
        }

        /*NAME*/
        strncpy(test.mbr_partition_4.part_name, name, 16);

        printf("///////////////////////////////////////////////////////////////\n");
        printf("Despues de la actualizacion:\n");
        printf("Status: %c\n", test.mbr_partition_4.part_status);
        printf("Type: %c\n", test.mbr_partition_4.part_type);
        printf("Fit: %c\n", test.mbr_partition_4.part_fit);
        printf("Start: %d\n", test.mbr_partition_4.part_start);
        printf("Size: %d\n", test.mbr_partition_4.part_size);
        printf("Name: %s\n", test.mbr_partition_4.part_name);
        printf("///////////////////////////////////////////////////////////////\n");

        /*Creo el EBR que se crea junto con la partición*/
        struct ebr particion_ebr = {
            'D',
            'X',
            0,
            0,
            -1,
            "NONE"
        };

        /*Escribo el EBR*/
        fseek(prueba, test.mbr_partition_3.part_start + test.mbr_partition_3.part_size, SEEK_SET);
        fwrite(&particion_ebr, sizeof(particion_ebr), 1, prueba);

        /*Agrego los cambios al MBR*/
        fseek(prueba, 0, SEEK_SET);
        fwrite(&test, sizeof(test), 1, prueba);

        /*Cierro los archivos*/
        fflush(prueba);
        fclose(prueba);

        printf("********************************************************************\n");
        printf("Particion creada exitosamente!\n");
        printf("********************************************************************\n");

    }

}
