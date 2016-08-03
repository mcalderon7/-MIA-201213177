#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "verificarExistenciaParticion.h"

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

int banderaExtendidas = 0;

int verificarExistenciaParticion(char *path, char *name){

    struct mbr test;
    struct ebr test_ebr;

    FILE * prueba = fopen(path, "r+b");
    fseek(prueba,0,SEEK_SET);
    fread(&test, sizeof(test), 1, prueba);

    /*Si alguna de las opciones es verdadera significa que si existe la particion en el disco*/
    if(strcmp(test.mbr_partition_1.part_name, name) == 0){

        if(test.mbr_partition_1.part_type == 'E'){
            return 2;
        }else{
            return 1;
        }

    }else if(strcmp(test.mbr_partition_2.part_name, name) == 0){

        if(test.mbr_partition_2.part_type == 'E'){
            return 2;
        }else{
            return 1;
        }

    }else if(strcmp(test.mbr_partition_3.part_name, name) == 0){

        if(test.mbr_partition_3.part_type == 'E'){
            return 2;
        }else{
            return 1;
        }

    }else if(strcmp(test.mbr_partition_4.part_name, name) == 0){

        if(test.mbr_partition_4.part_type == 'E'){
            return 2;
        }else{
            return 1;
        }

    }else{

        if(test.mbr_partition_1.part_type == 'E'){

            fseek(prueba,test.mbr_partition_1.part_start,SEEK_SET);
            fread(&test_ebr, sizeof(test_ebr), 1, prueba);

            if(strcmp(test_ebr.part_name, name) == 0){
                return 1;
            }else{

                while(test_ebr.part_next != -1){
                    fseek(prueba,test_ebr.part_next,SEEK_SET);
                    fread(&test_ebr,sizeof(test_ebr),1,prueba);

                    if(strcmp(test_ebr.part_name, name) == 0){
                        banderaExtendidas = 1;
                        break;
                    }

                }

                if(banderaExtendidas == 1){
                    return 1;
                    banderaExtendidas = 0;
                }else{
                    return 0;
                }

            }

        }else if(test.mbr_partition_2.part_type == 'E'){

            fseek(prueba,test.mbr_partition_2.part_start,SEEK_SET);
            fread(&test_ebr, sizeof(test_ebr), 1, prueba);

            if(strcmp(test_ebr.part_name, name) == 0){
                return 1;
            }else{

                while(test_ebr.part_next != -1){
                    fseek(prueba,test_ebr.part_next,SEEK_SET);
                    fread(&test_ebr,sizeof(test_ebr),1,prueba);

                    if(strcmp(test_ebr.part_name, name) == 0){
                        banderaExtendidas = 1;
                        break;
                    }

                }

                if(banderaExtendidas == 1){
                    return 1;
                    banderaExtendidas = 0;
                }else{
                    return 0;
                }

            }

        }else if(test.mbr_partition_3.part_type == 'E'){

            fseek(prueba,test.mbr_partition_3.part_start,SEEK_SET);
            fread(&test_ebr, sizeof(test_ebr), 1, prueba);

            if(strcmp(test_ebr.part_name, name) == 0){
                return 1;
            }else{

                while(test_ebr.part_next != -1){
                    fseek(prueba,test_ebr.part_next,SEEK_SET);
                    fread(&test_ebr,sizeof(test_ebr),1,prueba);

                    if(strcmp(test_ebr.part_name, name) == 0){
                        banderaExtendidas = 1;
                        break;
                    }

                }

                if(banderaExtendidas == 1){
                    return 1;
                    banderaExtendidas = 0;
                }else{
                    return 0;
                }

            }

        }else if(test.mbr_partition_4.part_type == 'E'){

            fseek(prueba,test.mbr_partition_4.part_start,SEEK_SET);
            fread(&test_ebr, sizeof(test_ebr), 1, prueba);

            if(strcmp(test_ebr.part_name, name) == 0){
                return 1;
            }else{

                while(test_ebr.part_next != -1){
                    fseek(prueba,test_ebr.part_next,SEEK_SET);
                    fread(&test_ebr,sizeof(test_ebr),1,prueba);

                    if(strcmp(test_ebr.part_name, name) == 0){
                        banderaExtendidas = 1;
                        break;
                    }

                }

                if(banderaExtendidas == 1){
                    return 1;
                    banderaExtendidas = 0;
                }else{
                    return 0;
                }

            }

        }else{
            return 0;
        }

    }

}
