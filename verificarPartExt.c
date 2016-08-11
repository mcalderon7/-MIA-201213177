#include <stdio.h>
#include <stdlib.h>
#include "verificarPartExt.h"
#include "verificarParticiones.h"

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

int verificarPartExt(char *path){

    struct mbr test;

    /*Como solo se puede crear una particion extendida, verifico del archivo si ya existe una, si no, pues que se cree si es que hay espacio*/
    FILE * prueba = fopen(path, "r+b");
    fread(&test, sizeof(test), 1, prueba);

    /*Verifico si alguna de las particiones es extendida*/
    if(test.mbr_partition_1.part_type == 'E' || test.mbr_partition_2.part_type == 'E' || test.mbr_partition_3.part_type == 'E' || test.mbr_partition_4.part_type == 'E'){

        return 0;

    /*Si no cuenta con particiones extendidas, verifico que exista espacio en el disco para crear una*/
    }else{

        int valido = verificarParticiones(path);

        if(valido == 1){
            return 1;
        }else{
            return 2;
        }

    }



}
