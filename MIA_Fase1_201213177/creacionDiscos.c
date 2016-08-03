#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <unistd.h>
#include <time.h>
#include "creacionDiscos.h"
#include "limpiar.h"
#include "getPathOnly.h"
#include "getRandom.h"

typedef struct partition {
    char part_status;
    char part_type;
    char part_fit;
    int part_start;
    int part_size;
    char part_name[16];
} estructura_particion;

struct mbr {
    int mbr_tamano;
    time_t mbr_fecha_creacion;
    int mbr_disk_signature;
    struct partition mbr_partition_1;
    struct partition mbr_partition_2;
    struct partition mbr_partition_3;
    struct partition mbr_partition_4;
};

void crearDisco(int size, char unit, char * path){

    /*Primero obtengo la fecha de creacion*/

    /*char fecha_hora[200];

    char ano[5];
    char mes[5];
    char dia[5];

    char hora[5];
    char minuto[5];
    char segundo[5];

    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    sprintf(ano, "%d", tm.tm_year+1900);
    sprintf(mes, "%d", tm.tm_mon + 1);
    sprintf(dia, "%d", tm.tm_mday);
    sprintf(hora, "%d", tm.tm_hour);
    sprintf(minuto, "%d", tm.tm_min);
    sprintf(segundo, "%d", tm.tm_sec);

    strcpy(fecha_hora, ano);
    strcat(fecha_hora, "-");
    strcat(fecha_hora, mes);
    strcat(fecha_hora, "-");
    strcat(fecha_hora, dia);
    strcat(fecha_hora, "//");
    strcat(fecha_hora, hora);
    strcat(fecha_hora, ":");
    strcat(fecha_hora, minuto);
    strcat(fecha_hora, ":");
    strcat(fecha_hora, segundo);*/

    /*Primero reviso de que tipo es la letra que ingreso el usuario en unit:
        Si unit=K se crea en kilobytes
        Si unit=M se crean en megabytes
    */

    if(unit == 'K'){

        char comando[200];
        limpiar(comando, 200);
        char cp[100];
        limpiar(cp, 100);
        strcpy(cp, getPathOnly(path));
        sprintf(comando, "mkdir %s -p", cp);
        system(comando);
        FILE * fp = fopen(path, "wb");
        fseek(fp, size*1024, SEEK_SET);
        fputc('\n', fp);
        fclose(fp);

        int numeroRandom = getRandom();

        time_t tiempo = time(0);
//        printf(ctime(&tiempo));

        /*Creo el MBR del disco*/
        struct mbr particion_mbr = {
            size*1024,
            tiempo,
            numeroRandom,
            {'D', 'X', 'X', 0, 0, "NONE"},
            {'D', 'X', 'X', 0, 0, "NONE"},
            {'D', 'X', 'X', 0, 0, "NONE"},
            {'D', 'X', 'X', 0, 0, "NONE"}
        };

        FILE * test = fopen(path, "r+b");
        fseek(test,0,SEEK_SET);
        fwrite(&particion_mbr, sizeof(particion_mbr), 1, test);
        fclose(test);

        printf("********************************************************************\n");
        printf("Archivo de disco creado exitosamente\n");
        printf("////////////////////////////////////////////////////////////////////\n");

    }else if(unit == 'M'){

        char comando[200];
        limpiar(comando, 200);
        char cp[100];
        limpiar(cp, 100);
        strcpy(cp, getPathOnly(path));
        sprintf(comando, "mkdir %s -p", cp);
        system(comando);
        FILE * fp = fopen(path, "wb");
        fseek(fp, size*1048576, SEEK_SET);
        fputc('\n', fp);
        fclose(fp);

        int numeroRandom = getRandom();
        time_t tiempo = time(0);

        /*Creo el MBR del disco*/
        struct mbr particion_mbr = {
            size*1024*1024,
            tiempo,
            numeroRandom,
            {'D', 'X', 'X', 0, 0, "NONE"},
            {'D', 'X', 'X', 0, 0, "NONE"},
            {'D', 'X', 'X', 0, 0, "NONE"},
            {'D', 'X', 'X', 0, 0, "NONE"}
        };

        /*Escribo el MBR dentro del archivo*/
        FILE * test = fopen(path, "r+b");
        fseek(test,0,SEEK_SET);
        fwrite(&particion_mbr, sizeof(particion_mbr), 1, test);
        fclose(test);

        printf("********************************************************************\n");
        printf("Archivo de disco creado exitosamente\n");
        printf("////////////////////////////////////////////////////////////////////\n");

    }else{

        printf("********************************************************************\n");
        printf("Tipo de unidad desconocido, revise su sentencia.\n");
        printf("********************************************************************\n");

    }

}
