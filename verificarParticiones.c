#include <stdio.h>
#include <stdlib.h>
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

int verificarParticiones(char *path){

    struct mbr test;

    /*Leo del archivo el estado de las particiones para verificar si hay espacio disponible para poder crear una*/
    FILE * prueba = fopen(path, "r+b");
    fread(&test, sizeof(test), 1, prueba);

    if(test.mbr_partition_1.part_status == 'A' && test.mbr_partition_2.part_status == 'A' && test.mbr_partition_3.part_status == 'A' && test.mbr_partition_4.part_status == 'A'){

        return 0;

    }else{

        return 1;

    }

}
