#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <time.h>
#include "graficarDisco.h"
#include "limpiar.h"

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

void graficarDisco(char *path, char *pathImagen){

    printf("\n EN GRAFICAR DISCO %s\n",path);

    char arrPathImg[200];
    limpiar(arrPathImg, 200);
    strcpy(arrPathImg, pathImagen);
    char *pathDot = "/home/marvin/Escritorio/grafdisco.dot";
    char *pathJPG = arrPathImg;

    struct mbr test_mbr;
    struct ebr test_ebr;

    FILE * fmbr = fopen(path, "r+b");
    FILE * fdot = fopen(pathDot,"w+");

    if(fmbr){

        fseek(fmbr,0,SEEK_SET);
        fread(&test_mbr, sizeof(test_mbr), 1, fmbr);
        fprintf(fdot, "digraph disk {\n");
        fprintf(fdot, "node [shape=record];\n");
        fprintf(fdot, "struct1 [label=\"MBR");

        /*MBR PARTITION 1*/
        if(test_mbr.mbr_partition_1.part_status=='A'){

            if(test_mbr.mbr_partition_1.part_type == 'E'){

                fprintf(fdot, "| { EXTENDIDA | {");

                /*Leo las particiones logicas*/
                fseek(fmbr, test_mbr.mbr_partition_1.part_start, SEEK_SET);
                fread(&test_ebr, sizeof(test_ebr), 1, fmbr);

                fprintf(fdot, " EBR");

                if(test_ebr.part_status == 'A'){
                    fprintf(fdot, " | ParticionL // Nombre: %s // Tipo: L", test_ebr.part_name);
                }

                while(test_ebr.part_next != -1){

                    fseek(fmbr,test_ebr.part_next,SEEK_SET);
                    fread(&test_ebr,sizeof(test_ebr),1,fmbr);

                    if(test_ebr.part_status == 'A'){
                        fprintf(fdot, " | EBR");
                        fprintf(fdot, " | ParticionL // Nombre: %s // Tipo: L", test_ebr.part_name);
                    }

                }

                fprintf(fdot, " } }");


            }else{
                fprintf(fdot, " | Particion #1 // Nombre: %s // Tipo: %c", test_mbr.mbr_partition_1.part_name, test_mbr.mbr_partition_1.part_type);
            }

        }else{
            fprintf(fdot, " | LIBRE");
        }

        /*MBR PARTITION 2*/
        if(test_mbr.mbr_partition_2.part_status=='A'){

            if(test_mbr.mbr_partition_2.part_type == 'E'){

                fprintf(fdot, "| { EXTENDIDA | {");

                /*Leo las particiones logicas*/
                fseek(fmbr, test_mbr.mbr_partition_2.part_start, SEEK_SET);
                fread(&test_ebr, sizeof(test_ebr), 1, fmbr);

                fprintf(fdot, " EBR");

                if(test_ebr.part_status == 'A'){
                    fprintf(fdot, " | ParticionL // Nombre: %s // Tipo: L", test_ebr.part_name);
                }

                while(test_ebr.part_next != -1){

                    fseek(fmbr,test_ebr.part_next,SEEK_SET);
                    fread(&test_ebr,sizeof(test_ebr),1,fmbr);

                    if(test_ebr.part_status == 'A'){
                        fprintf(fdot, " | EBR");
                        fprintf(fdot, " | ParticionL // Nombre: %s // Tipo: L", test_ebr.part_name);
                    }

                }

                fprintf(fdot, " } }");


            }else{
                fprintf(fdot, " | Particion #2 // Nombre: %s // Tipo: %c", test_mbr.mbr_partition_2.part_name, test_mbr.mbr_partition_2.part_type);
            }

        }else{
            fprintf(fdot, " | LIBRE");
        }

        /*MBR PARTITION 3*/
        if(test_mbr.mbr_partition_3.part_status=='A'){

            if(test_mbr.mbr_partition_3.part_type == 'E'){

                fprintf(fdot, "| { EXTENDIDA | {");

                /*Leo las particiones logicas*/
                fseek(fmbr, test_mbr.mbr_partition_3.part_start, SEEK_SET);
                fread(&test_ebr, sizeof(test_ebr), 1, fmbr);

                fprintf(fdot, " EBR");

                if(test_ebr.part_status == 'A'){
                    fprintf(fdot, " | ParticionL // Nombre: %s // Tipo: L", test_ebr.part_name);
                }

                while(test_ebr.part_next != -1){

                    fseek(fmbr,test_ebr.part_next,SEEK_SET);
                    fread(&test_ebr,sizeof(test_ebr),1,fmbr);

                    if(test_ebr.part_status == 'A'){
                        fprintf(fdot, " | EBR");
                        fprintf(fdot, " | ParticionL // Nombre: %s // Tipo: L", test_ebr.part_name);
                    }

                }

                fprintf(fdot, " } }");


            }else{
                fprintf(fdot, " | Particion #3 // Nombre: %s // Tipo: %c", test_mbr.mbr_partition_3.part_name, test_mbr.mbr_partition_3.part_type);
            }

        }else{
            fprintf(fdot, " | LIBRE");
        }

        /*MBR PARTITION 4*/
        if(test_mbr.mbr_partition_4.part_status=='A'){

            if(test_mbr.mbr_partition_4.part_type == 'E'){

                fprintf(fdot, "| { EXTENDIDA | {");

                /*Leo las particiones logicas*/
                fseek(fmbr, test_mbr.mbr_partition_4.part_start, SEEK_SET);
                fread(&test_ebr, sizeof(test_ebr), 1, fmbr);

                fprintf(fdot, " EBR");

                if(test_ebr.part_status == 'A'){
                    fprintf(fdot, " | ParticionL // Nombre: %s // Tipo: L", test_ebr.part_name);
                }

                while(test_ebr.part_next != -1){

                    fseek(fmbr,test_ebr.part_next,SEEK_SET);
                    fread(&test_ebr,sizeof(test_ebr),1,fmbr);

                    if(test_ebr.part_status == 'A'){
                        fprintf(fdot, " | EBR");
                        fprintf(fdot, " | ParticionL // Nombre: %s // Tipo: L", test_ebr.part_name);
                    }

                }

                fprintf(fdot, " } }");


            }else{
                fprintf(fdot, " | Particion #4 // Nombre: %s // Tipo: %c", test_mbr.mbr_partition_4.part_name, test_mbr.mbr_partition_4.part_type);
            }

        }else{
            fprintf(fdot, " | LIBRE");
        }

        fprintf(fdot, "\"];\n");
        fprintf(fdot, "}\n");
        fclose(fdot);
        fclose(fmbr);
        char commandd [200] ="dot /home/marvin/Escritorio/grafdisco.dot -o ";
        strcat(commandd,pathJPG);
        strcat(commandd," -Tjpg");
        //printf(commandd);
        system(commandd);

    }

}































