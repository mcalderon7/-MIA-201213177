#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "crearParticionLogica.h"

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

void crearParticionLogica(int size, char unit, char * path, char type, char fit, int num_add, char * name, char * borrar){

    struct mbr test;
    struct ebr test_ebr;

    FILE * prueba = fopen(path, "r+b");
    fseek(prueba, 0, SEEK_SET);
    fread(&test, sizeof(test), 1, prueba);

    if(test.mbr_partition_1.part_type == 'E'){

        /*Busco al inicio de la particion el ebr del principio*/
        fseek(prueba, test.mbr_partition_1.part_start, SEEK_SET);
        fread(&test_ebr, sizeof(test_ebr), 1, prueba);

        /*Verifico si el EBR que estoy leyendo tiene un siguiente*/
        if(test_ebr.part_next == -1){

            printf("///////////////////////////////////////////////////////////////\n");
            printf("Antes de la actualizacion:\n");
            printf("Status: %c\n", test_ebr.part_status);
            printf("Fit: %c\n", test_ebr.part_fit);
            printf("Start: %d\n", test_ebr.part_start);
            printf("Size: %d\n", test_ebr.part_size);
            printf("Next: %d\n", test_ebr.part_next);
            printf("Name: %s\n", test_ebr.part_name);
            printf("///////////////////////////////////////////////////////////////\n");

            /*STATUS*/
            test_ebr.part_status = 'A';

            /*FIT*/
            test_ebr.part_fit = fit;

            /*START*/
            test_ebr.part_start = sizeof(test_ebr);

            /*SIZE*/
            if(unit == 'B'){
                test_ebr.part_size = size;
            }else if(unit == 'K'){
                test_ebr.part_size = size*1024;
            }else if(unit == 'M'){
                test_ebr.part_size = size*1048576;
            }

            /*NEXT*/
            test_ebr.part_next = sizeof(test_ebr) + test_ebr.part_size;

            /*NAME*/
            strncpy(test_ebr.part_name, name, 16);

            printf("///////////////////////////////////////////////////////////////\n");
            printf("Despues de la actualizacion:\n");
            printf("Status: %c\n", test_ebr.part_status);
            printf("Fit: %c\n", test_ebr.part_fit);
            printf("Start: %d\n", test_ebr.part_start);
            printf("Size: %d\n", test_ebr.part_size);
            printf("Next: %d\n", test_ebr.part_next);
            printf("Name: %s\n", test_ebr.part_name);
            printf("///////////////////////////////////////////////////////////////\n");

            struct ebr particion_ebr = {
                'D',
                'X',
                0,
                0,
                -1,
                "NONE"
            };

            /*Actualizo el EBR existente*/
            fseek(prueba, test.mbr_partition_1.part_start, SEEK_SET);
            fwrite(&test_ebr, sizeof(test_ebr), 1, prueba);

            /*Escribo el nuevo EBR*/
            fseek(prueba, test_ebr.part_next, SEEK_SET);
            fwrite(&particion_ebr, sizeof(particion_ebr), 1, prueba);

            /*Cierro los archivos*/
            fflush(prueba);
            fclose(prueba);

            printf("********************************************************************\n");
            printf("Particion creada exitosamente!\n");
            printf("********************************************************************\n");

        }else{

            int next = test_ebr.part_next;

            do{
                fseek(prueba, next, SEEK_SET);
                fread(&test_ebr, sizeof(test_ebr), 1, prueba);

                if(test_ebr.part_next != -1){

                    next = test_ebr.part_next;

                }else{

                    printf("///////////////////////////////////////////////////////////////\n");
                    printf("Antes de la actualizacion:\n");
                    printf("Status: %c\n", test_ebr.part_status);
                    printf("Fit: %c\n", test_ebr.part_fit);
                    printf("Start: %d\n", test_ebr.part_start);
                    printf("Size: %d\n", test_ebr.part_size);
                    printf("Next: %d\n", test_ebr.part_next);
                    printf("Name: %s\n", test_ebr.part_name);
                    printf("///////////////////////////////////////////////////////////////\n");

                    /*STATUS*/
                    test_ebr.part_status = 'A';

                    /*FIT*/
                    test_ebr.part_fit = fit;

                    /*START*/
                    test_ebr.part_start = next + sizeof(test_ebr);

                    /*SIZE*/
                    if(unit == 'B'){
                        test_ebr.part_size = size;
                    }else if(unit == 'K'){
                        test_ebr.part_size = size*1024;
                    }else if(unit == 'M'){
                        test_ebr.part_size = size*1048576;
                    }

                    /*NEXT*/
                    test_ebr.part_next = next + sizeof(test_ebr) + test_ebr.part_size;

                    /*NAME*/
                    strncpy(test_ebr.part_name, name, 16);

                    printf("///////////////////////////////////////////////////////////////\n");
                    printf("Despues de la actualizacion:\n");
                    printf("Status: %c\n", test_ebr.part_status);
                    printf("Fit: %c\n", test_ebr.part_fit);
                    printf("Start: %d\n", test_ebr.part_start);
                    printf("Size: %d\n", test_ebr.part_size);
                    printf("Next: %d\n", test_ebr.part_next);
                    printf("Name: %s\n", test_ebr.part_name);
                    printf("///////////////////////////////////////////////////////////////\n");

                    struct ebr particion_ebr = {
                        'D',
                        'X',
                        0,
                        0,
                        -1,
                        "NONE"
                    };

                    /*Actualizo el EBR existente*/
                    fseek(prueba, next, SEEK_SET);
                    fwrite(&test_ebr, sizeof(test_ebr), 1, prueba);

                    /*Escribo el nuevo EBR*/
                    fseek(prueba, test_ebr.part_next, SEEK_SET);
                    fwrite(&particion_ebr, sizeof(particion_ebr), 1, prueba);

                    /*Cierro los archivos*/
                    fflush(prueba);
                    fclose(prueba);

                    printf("********************************************************************\n");
                    printf("Particion creada exitosamente!\n");
                    printf("********************************************************************\n");
                    break;

                }

            }while(next != -1);

    }



    }else if(test.mbr_partition_2.part_type == 'E'){

        /*Busco al inicio de la particion el ebr del principio*/
        fseek(prueba, test.mbr_partition_2.part_start, SEEK_SET);
        fread(&test_ebr, sizeof(test_ebr), 1, prueba);

        /*Verifico si el EBR que estoy leyendo tiene un siguiente*/
        if(test_ebr.part_next == -1){

            printf("///////////////////////////////////////////////////////////////\n");
            printf("Antes de la actualizacion:\n");
            printf("Status: %c\n", test_ebr.part_status);
            printf("Fit: %c\n", test_ebr.part_fit);
            printf("Start: %d\n", test_ebr.part_start);
            printf("Size: %d\n", test_ebr.part_size);
            printf("Next: %d\n", test_ebr.part_next);
            printf("Name: %s\n", test_ebr.part_name);
            printf("///////////////////////////////////////////////////////////////\n");

            /*STATUS*/
            test_ebr.part_status = 'A';

            /*FIT*/
            test_ebr.part_fit = fit;

            /*START*/
            test_ebr.part_start = sizeof(test_ebr);

            /*SIZE*/
            if(unit == 'B'){
                test_ebr.part_size = size;
            }else if(unit == 'K'){
                test_ebr.part_size = size*1024;
            }else if(unit == 'M'){
                test_ebr.part_size = size*1048576;
            }

            /*NEXT*/
            test_ebr.part_next = sizeof(test_ebr) + test_ebr.part_size;

            /*NAME*/
            strncpy(test_ebr.part_name, name, 16);

            printf("///////////////////////////////////////////////////////////////\n");
            printf("Despues de la actualizacion:\n");
            printf("Status: %c\n", test_ebr.part_status);
            printf("Fit: %c\n", test_ebr.part_fit);
            printf("Start: %d\n", test_ebr.part_start);
            printf("Size: %d\n", test_ebr.part_size);
            printf("Next: %d\n", test_ebr.part_next);
            printf("Name: %s\n", test_ebr.part_name);
            printf("///////////////////////////////////////////////////////////////\n");

            struct ebr particion_ebr = {
                'D',
                'X',
                0,
                0,
                -1,
                "NONE"
            };

            /*Actualizo el EBR existente*/
            fseek(prueba, test.mbr_partition_2.part_start, SEEK_SET);
            fwrite(&test_ebr, sizeof(test_ebr), 1, prueba);

            /*Escribo el nuevo EBR*/
            fseek(prueba, test_ebr.part_next, SEEK_SET);
            fwrite(&particion_ebr, sizeof(particion_ebr), 1, prueba);

            /*Cierro los archivos*/
            fflush(prueba);
            fclose(prueba);

            printf("********************************************************************\n");
            printf("Particion creada exitosamente!\n");
            printf("********************************************************************\n");

        }else{

            int next = test_ebr.part_next;

            do{
                fseek(prueba, next, SEEK_SET);
                fread(&test_ebr, sizeof(test_ebr), 1, prueba);

                if(test_ebr.part_next != -1){

                    next = test_ebr.part_next;

                }else{

                    printf("///////////////////////////////////////////////////////////////\n");
                    printf("Antes de la actualizacion:\n");
                    printf("Status: %c\n", test_ebr.part_status);
                    printf("Fit: %c\n", test_ebr.part_fit);
                    printf("Start: %d\n", test_ebr.part_start);
                    printf("Size: %d\n", test_ebr.part_size);
                    printf("Next: %d\n", test_ebr.part_next);
                    printf("Name: %s\n", test_ebr.part_name);
                    printf("///////////////////////////////////////////////////////////////\n");

                    /*STATUS*/
                    test_ebr.part_status = 'A';

                    /*FIT*/
                    test_ebr.part_fit = fit;

                    /*START*/
                    test_ebr.part_start = next + sizeof(test_ebr);

                    /*SIZE*/
                    if(unit == 'B'){
                        test_ebr.part_size = size;
                    }else if(unit == 'K'){
                        test_ebr.part_size = size*1024;
                    }else if(unit == 'M'){
                        test_ebr.part_size = size*1048576;
                    }

                    /*NEXT*/
                    test_ebr.part_next = next + sizeof(test_ebr) + test_ebr.part_size;

                    /*NAME*/
                    strncpy(test_ebr.part_name, name, 16);

                    printf("///////////////////////////////////////////////////////////////\n");
                    printf("Despues de la actualizacion:\n");
                    printf("Status: %c\n", test_ebr.part_status);
                    printf("Fit: %c\n", test_ebr.part_fit);
                    printf("Start: %d\n", test_ebr.part_start);
                    printf("Size: %d\n", test_ebr.part_size);
                    printf("Next: %d\n", test_ebr.part_next);
                    printf("Name: %s\n", test_ebr.part_name);
                    printf("///////////////////////////////////////////////////////////////\n");

                    struct ebr particion_ebr = {
                        'D',
                        'X',
                        0,
                        0,
                        -1,
                        "NONE"
                    };

                    /*Actualizo el EBR existente*/
                    fseek(prueba, next, SEEK_SET);
                    fwrite(&test_ebr, sizeof(test_ebr), 1, prueba);

                    /*Escribo el nuevo EBR*/
                    fseek(prueba, test_ebr.part_next, SEEK_SET);
                    fwrite(&particion_ebr, sizeof(particion_ebr), 1, prueba);

                    /*Cierro los archivos*/
                    fflush(prueba);
                    fclose(prueba);

                    printf("********************************************************************\n");
                    printf("Particion creada exitosamente!\n");
                    printf("********************************************************************\n");
                    break;

                }

            }while(next != -1);

        }

    }else if(test.mbr_partition_3.part_type == 'E'){

        /*Busco al inicio de la particion el ebr del principio*/
        fseek(prueba, test.mbr_partition_3.part_start, SEEK_SET);
        fread(&test_ebr, sizeof(test_ebr), 1, prueba);

        /*Verifico si el EBR que estoy leyendo tiene un siguiente*/
        if(test_ebr.part_next == -1){

            printf("///////////////////////////////////////////////////////////////\n");
            printf("Antes de la actualizacion:\n");
            printf("Status: %c\n", test_ebr.part_status);
            printf("Fit: %c\n", test_ebr.part_fit);
            printf("Start: %d\n", test_ebr.part_start);
            printf("Size: %d\n", test_ebr.part_size);
            printf("Next: %d\n", test_ebr.part_next);
            printf("Name: %s\n", test_ebr.part_name);
            printf("///////////////////////////////////////////////////////////////\n");

            /*STATUS*/
            test_ebr.part_status = 'A';

            /*FIT*/
            test_ebr.part_fit = fit;

            /*START*/
            test_ebr.part_start = sizeof(test_ebr);

            /*SIZE*/
            if(unit == 'B'){
                test_ebr.part_size = size;
            }else if(unit == 'K'){
                test_ebr.part_size = size*1024;
            }else if(unit == 'M'){
                test_ebr.part_size = size*1048576;
            }

            /*NEXT*/
            test_ebr.part_next = sizeof(test_ebr) + test_ebr.part_size;

            /*NAME*/
            strncpy(test_ebr.part_name, name, 16);

            printf("///////////////////////////////////////////////////////////////\n");
            printf("Despues de la actualizacion:\n");
            printf("Status: %c\n", test_ebr.part_status);
            printf("Fit: %c\n", test_ebr.part_fit);
            printf("Start: %d\n", test_ebr.part_start);
            printf("Size: %d\n", test_ebr.part_size);
            printf("Next: %d\n", test_ebr.part_next);
            printf("Name: %s\n", test_ebr.part_name);
            printf("///////////////////////////////////////////////////////////////\n");

            struct ebr particion_ebr = {
                'D',
                'X',
                0,
                0,
                -1,
                "NONE"
            };

            /*Actualizo el EBR existente*/
            fseek(prueba, test.mbr_partition_3.part_start, SEEK_SET);
            fwrite(&test_ebr, sizeof(test_ebr), 1, prueba);

            /*Escribo el nuevo EBR*/
            fseek(prueba, test_ebr.part_next, SEEK_SET);
            fwrite(&particion_ebr, sizeof(particion_ebr), 1, prueba);

            /*Cierro los archivos*/
            fflush(prueba);
            fclose(prueba);

            printf("********************************************************************\n");
            printf("Particion creada exitosamente!\n");
            printf("********************************************************************\n");

        }else{

            int next = test_ebr.part_next;

            do{
                fseek(prueba, next, SEEK_SET);
                fread(&test_ebr, sizeof(test_ebr), 1, prueba);

                if(test_ebr.part_next != -1){

                    next = test_ebr.part_next;

                }else{

                    printf("///////////////////////////////////////////////////////////////\n");
                    printf("Antes de la actualizacion:\n");
                    printf("Status: %c\n", test_ebr.part_status);
                    printf("Fit: %c\n", test_ebr.part_fit);
                    printf("Start: %d\n", test_ebr.part_start);
                    printf("Size: %d\n", test_ebr.part_size);
                    printf("Next: %d\n", test_ebr.part_next);
                    printf("Name: %s\n", test_ebr.part_name);
                    printf("///////////////////////////////////////////////////////////////\n");

                    /*STATUS*/
                    test_ebr.part_status = 'A';

                    /*FIT*/
                    test_ebr.part_fit = fit;

                    /*START*/
                    test_ebr.part_start = next + sizeof(test_ebr);

                    /*SIZE*/
                    if(unit == 'B'){
                        test_ebr.part_size = size;
                    }else if(unit == 'K'){
                        test_ebr.part_size = size*1024;
                    }else if(unit == 'M'){
                        test_ebr.part_size = size*1048576;
                    }

                    /*NEXT*/
                    test_ebr.part_next = next + sizeof(test_ebr) + test_ebr.part_size;

                    /*NAME*/
                    strncpy(test_ebr.part_name, name, 16);

                    printf("///////////////////////////////////////////////////////////////\n");
                    printf("Despues de la actualizacion:\n");
                    printf("Status: %c\n", test_ebr.part_status);
                    printf("Fit: %c\n", test_ebr.part_fit);
                    printf("Start: %d\n", test_ebr.part_start);
                    printf("Size: %d\n", test_ebr.part_size);
                    printf("Next: %d\n", test_ebr.part_next);
                    printf("Name: %s\n", test_ebr.part_name);
                    printf("///////////////////////////////////////////////////////////////\n");

                    struct ebr particion_ebr = {
                        'D',
                        'X',
                        0,
                        0,
                        -1,
                        "NONE"
                    };

                    /*Actualizo el EBR existente*/
                    fseek(prueba, next, SEEK_SET);
                    fwrite(&test_ebr, sizeof(test_ebr), 1, prueba);

                    /*Escribo el nuevo EBR*/
                    fseek(prueba, test_ebr.part_next, SEEK_SET);
                    fwrite(&particion_ebr, sizeof(particion_ebr), 1, prueba);

                    /*Cierro los archivos*/
                    fflush(prueba);
                    fclose(prueba);

                    printf("********************************************************************\n");
                    printf("Particion creada exitosamente!\n");
                    printf("********************************************************************\n");
                    break;

                }

            }while(next != -1);

        }

    }else if(test.mbr_partition_4.part_type == 'E'){

        /*Busco al inicio de la particion el ebr del principio*/
        fseek(prueba, test.mbr_partition_4.part_start, SEEK_SET);
        fread(&test_ebr, sizeof(test_ebr), 1, prueba);

        /*Verifico si el EBR que estoy leyendo tiene un siguiente*/
        if(test_ebr.part_next == -1){

            printf("///////////////////////////////////////////////////////////////\n");
            printf("Antes de la actualizacion:\n");
            printf("Status: %c\n", test_ebr.part_status);
            printf("Fit: %c\n", test_ebr.part_fit);
            printf("Start: %d\n", test_ebr.part_start);
            printf("Size: %d\n", test_ebr.part_size);
            printf("Next: %d\n", test_ebr.part_next);
            printf("Name: %s\n", test_ebr.part_name);
            printf("///////////////////////////////////////////////////////////////\n");

            /*STATUS*/
            test_ebr.part_status = 'A';

            /*FIT*/
            test_ebr.part_fit = fit;

            /*START*/
            test_ebr.part_start = sizeof(test_ebr);

            /*SIZE*/
            if(unit == 'B'){
                test_ebr.part_size = size;
            }else if(unit == 'K'){
                test_ebr.part_size = size*1024;
            }else if(unit == 'M'){
                test_ebr.part_size = size*1048576;
            }

            /*NEXT*/
            test_ebr.part_next = sizeof(test_ebr) + test_ebr.part_size;

            /*NAME*/
            strncpy(test_ebr.part_name, name, 16);

            printf("///////////////////////////////////////////////////////////////\n");
            printf("Despues de la actualizacion:\n");
            printf("Status: %c\n", test_ebr.part_status);
            printf("Fit: %c\n", test_ebr.part_fit);
            printf("Start: %d\n", test_ebr.part_start);
            printf("Size: %d\n", test_ebr.part_size);
            printf("Next: %d\n", test_ebr.part_next);
            printf("Name: %s\n", test_ebr.part_name);
            printf("///////////////////////////////////////////////////////////////\n");

            struct ebr particion_ebr = {
                'D',
                'X',
                0,
                0,
                -1,
                "NONE"
            };

            /*Actualizo el EBR existente*/
            fseek(prueba, test.mbr_partition_4.part_start, SEEK_SET);
            fwrite(&test_ebr, sizeof(test_ebr), 1, prueba);

            /*Escribo el nuevo EBR*/
            fseek(prueba, test_ebr.part_next, SEEK_SET);
            fwrite(&particion_ebr, sizeof(particion_ebr), 1, prueba);

            /*Cierro los archivos*/
            fflush(prueba);
            fclose(prueba);

            printf("********************************************************************\n");
            printf("Particion creada exitosamente!\n");
            printf("********************************************************************\n");

        }else{

            int next = test_ebr.part_next;

            do{
                fseek(prueba, next, SEEK_SET);
                fread(&test_ebr, sizeof(test_ebr), 1, prueba);

                if(test_ebr.part_next != -1){

                    next = test_ebr.part_next;

                }else{

                    printf("///////////////////////////////////////////////////////////////\n");
                    printf("Antes de la actualizacion:\n");
                    printf("Status: %c\n", test_ebr.part_status);
                    printf("Fit: %c\n", test_ebr.part_fit);
                    printf("Start: %d\n", test_ebr.part_start);
                    printf("Size: %d\n", test_ebr.part_size);
                    printf("Next: %d\n", test_ebr.part_next);
                    printf("Name: %s\n", test_ebr.part_name);
                    printf("///////////////////////////////////////////////////////////////\n");

                    /*STATUS*/
                    test_ebr.part_status = 'A';

                    /*FIT*/
                    test_ebr.part_fit = fit;

                    /*START*/
                    test_ebr.part_start = next + sizeof(test_ebr);

                    /*SIZE*/
                    if(unit == 'B'){
                        test_ebr.part_size = size;
                    }else if(unit == 'K'){
                        test_ebr.part_size = size*1024;
                    }else if(unit == 'M'){
                        test_ebr.part_size = size*1048576;
                    }

                    /*NEXT*/
                    test_ebr.part_next = next + sizeof(test_ebr) + test_ebr.part_size;

                    /*NAME*/
                    strncpy(test_ebr.part_name, name, 16);

                    printf("///////////////////////////////////////////////////////////////\n");
                    printf("Despues de la actualizacion:\n");
                    printf("Status: %c\n", test_ebr.part_status);
                    printf("Fit: %c\n", test_ebr.part_fit);
                    printf("Start: %d\n", test_ebr.part_start);
                    printf("Size: %d\n", test_ebr.part_size);
                    printf("Next: %d\n", test_ebr.part_next);
                    printf("Name: %s\n", test_ebr.part_name);
                    printf("///////////////////////////////////////////////////////////////\n");

                    struct ebr particion_ebr = {
                        'D',
                        'X',
                        0,
                        0,
                        -1,
                        "NONE"
                    };

                    /*Actualizo el EBR existente*/
                    fseek(prueba, next, SEEK_SET);
                    fwrite(&test_ebr, sizeof(test_ebr), 1, prueba);

                    /*Escribo el nuevo EBR*/
                    fseek(prueba, test_ebr.part_next, SEEK_SET);
                    fwrite(&particion_ebr, sizeof(particion_ebr), 1, prueba);

                    /*Cierro los archivos*/
                    fflush(prueba);
                    fclose(prueba);

                    printf("********************************************************************\n");
                    printf("Particion creada exitosamente!\n");
                    printf("********************************************************************\n");
                    break;

                }

            }while(next != -1);

        }

    }

}
