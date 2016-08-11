#ifndef ESTRUCTURAS_H_INCLUDED
#define ESTRUCTURAS_H_INCLUDED

#include <time.h>

typedef struct edd_partition {
    char part_status;
    char part_type;
    char part_fit;
    int part_start;
    int part_size;
    char part_name[16];
}PARTICION;

typedef struct edd_mbr {
    int mbr_tamano;
    time_t mbr_fecha_creacion;
    int mbr_disk_signature;
    struct edd_partition mbr_partition_1;
    struct edd_partition mbr_partition_2;
    struct edd_partition mbr_partition_3;
    struct edd_partition mbr_partition_4;
}MBR;

typedef struct super_bloque{

    int sb_arbol_virtual_count;
    int sb_detalle_directorio_count;
    int sb_inodos_count;
    int sb_bloques_count;
    int sb_free_arbol_virtual_count;
    int sb_free_detalle_directorio_count;
    int sb_free_bloques_count;
    int sb_free_inodes_count;
    time_t sb_mtime;
    time_t sb_umtime;
    int sb_mnt_count;
    int sb_magic;
    int sb_avd_size;
    int sb_detalle_directorio_size;
    int sb_inode_size;
    int sb_block_size;
    int sb_ap_avd;
    int sb_ap_bitmap_avd;
    int sb_ap_detalle_directorio;
    int sb_ap_bitmap_detalle_directorio;
    int sb_ap_tabla_inodo;
    int sb_ap_bitmap_tabla_inodo;
    int sb_ap_bloque;
    int sb_ap_bitmap_bloque;
    int sb_ap_log;
    int sb_ap_copia_super_Bloque;
    int sb_first_free_bit_avd;
    int sb_first_free_bit_detalle_directorio;
    int sb_first_free_bit_tabla_inodo;
    int sb_first_free_bit_bloques;

}SUPERBLOQUE;

typedef struct arbol_virtual_directorio{

    time_t avd_fecha_creacion;
    char avd_name_directorio[16];
    int avd_ap_array_subdirectorios[6];
    int avd_ap_detalle_directorio;
    int avd_ap_avd;

}AVD;

typedef struct edd_archivo{

    char dd_file_nombre[16];
    int dd_file_ap_inodo;
    time_t dd_file_date_creacion;
    time_t dd_file_date_modificacion;

}ARCHIVO;

typedef struct _detalle_directorio{

    ARCHIVO dd_Archive_1;
    ARCHIVO dd_Archive_2;
    ARCHIVO dd_Archive_3;
    ARCHIVO dd_Archive_4;
    ARCHIVO dd_Archive_5;
    int dd_ap_detalle_directorio;

}DETALLE_DIRECTORIO;

typedef struct detalle_inodo{

    int i_count_inodo;
    int i_size_file;
    int i_count_bloques_asignados;
    int i_array_bloques[4];
    int i_ap_indirecto;

}INODO;

typedef struct bloque_de_datos{

    char db_data[25];

}BLOQUE_DATOS;

typedef struct detalle_bitacora{

    char log_tipo_operacion[40];
    int log_tipo;
    char log_nombre[15];
    char log_contenido[100];
    time_t log_fecha;

}BITACORA;

typedef struct avd_bitmap{

    char bitmap[25];

}BITMAP_AVD;

typedef struct detalle_directorio_bitmap{

    char bitmap[25];

}BITMAP_DD;

typedef struct inodo_bitmap{

    char bitmap[25];

}BITMAP_INODO;

typedef struct bloque_datos_bitmap{

    char bitmap[25];

}BITMAP_BD;

#endif




