#include <stdio.h>
#include <stdlib.h>
#include "verificarPartLog.h"

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

int verificarPartLog(char *path){

    struct mbr test;

    FILE * prueba = fopen(path, "r+b");
    fread(&test, sizeof(test), 1, prueba);

    /*Verifico si alguna de las particiones es extendida, para poder crear las logicas dentro de esta*/
    if(test.mbr_partition_1.part_type == 'E' || test.mbr_partition_2.part_type == 'E' || test.mbr_partition_3.part_type == 'E' || test.mbr_partition_4.part_type == 'E'){
        return 1;
    }else{
        return 0;
    }

}
