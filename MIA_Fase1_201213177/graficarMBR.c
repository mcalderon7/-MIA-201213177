#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <time.h>
#include "graficarMBR.h"

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

void graficarMBR(char *path){

    printf("\n EN GRAFICAR MBR %s\n",path);

    char *pathDot = "/home/marvin/Escritorio/grafmbr.dot";
    char *pathJPG = "/home/marvin/Escritorio/grafmbr.jpg";

    struct mbr test_mbr;
    struct ebr test_ebr;
    int particion = 0;

    FILE * fmbr = fopen(path, "r+b");
    FILE * fdot = fopen(pathDot,"w+");

    if(fmbr){

        fseek(fmbr,0,SEEK_SET);
        fread(&test_mbr, sizeof(test_mbr), 1, fmbr);
        fprintf(fdot,"digraph mbr {\n");
        //fprintf(fdot," rankdir=LR\n");
        fprintf(fdot," node [shape=plaintext]\n");
        fprintf(fdot," b [\n");
        fprintf(fdot,"      style=filled label=<\n");
        fprintf(fdot,"           <TABLE BORDER=\"1\" CELLBORDER=\"1\" CELLSPACING=\"2\">\n");
        fprintf(fdot,"                 <TR>\n");
        fprintf(fdot,"                     <TD COLSPAN=\"2\" ROWSPAN=\"1\"><FONT POINT-SIZE=\"16\">MBR %s</FONT></TD>\n",path);
        fprintf(fdot,"                 </TR>\n");

        //-----encabezado
        fprintf(fdot,"                 <TR>\n");
        fprintf(fdot,"                     <TD COLSPAN=\"1\" ROWSPAN=\"1\"><FONT POINT-SIZE=\"16\">Nombre</FONT></TD>\n");
        fprintf(fdot,"                     <TD COLSPAN=\"1\" ROWSPAN=\"1\"><FONT POINT-SIZE=\"16\">Valor</FONT></TD>\n");
        fprintf(fdot,"                 </TR>\n");

        //---- mbr tam
        fprintf(fdot,"                 <TR>\n");
        fprintf(fdot,"                     <TD COLSPAN=\"1\" ROWSPAN=\"1\"><FONT POINT-SIZE=\"16\">mbr_tamaño</FONT></TD>\n");
        fprintf(fdot,"                     <TD COLSPAN=\"1\" ROWSPAN=\"1\"><FONT POINT-SIZE=\"16\">%d</FONT></TD>\n",test_mbr.mbr_tamano);
        fprintf(fdot,"                 </TR>\n");

        //----fecha

        fprintf(fdot,"                 <TR>\n");
        fprintf(fdot,"                     <TD COLSPAN=\"1\" ROWSPAN=\"1\"><FONT POINT-SIZE=\"16\">mbr_fecha_creacion</FONT></TD>\n");
        fprintf(fdot,"                     <TD COLSPAN=\"1\" ROWSPAN=\"1\"><FONT POINT-SIZE=\"16\">%s</FONT></TD>\n",ctime(&test_mbr.mbr_fecha_creacion)); /*aqui va la fecha*/
        fprintf(fdot,"                 </TR>\n");

        //-----signatura
        fprintf(fdot,"                 <TR>\n");
        fprintf(fdot,"                     <TD COLSPAN=\"1\" ROWSPAN=\"1\"><FONT POINT-SIZE=\"16\">mbr_disk_signature</FONT></TD>\n");
        fprintf(fdot,"                     <TD COLSPAN=\"1\" ROWSPAN=\"1\"><FONT POINT-SIZE=\"16\">%d</FONT></TD>\n",test_mbr.mbr_disk_signature);
        fprintf(fdot,"                 </TR>\n");


        if(test_mbr.mbr_partition_1.part_status=='A'){

            if(test_mbr.mbr_partition_1.part_type=='E'){
                particion = 1;
            }

            //part status
            fprintf(fdot,"                 <TR>\n");
            fprintf(fdot,"                     <TD COLSPAN=\"1\" ROWSPAN=\"1\"><FONT POINT-SIZE=\"16\">part_status_1</FONT></TD>\n");
            fprintf(fdot,"                     <TD COLSPAN=\"1\" ROWSPAN=\"1\"><FONT POINT-SIZE=\"16\">%d</FONT></TD>\n",1);
            fprintf(fdot,"                 </TR>\n");

            //part type
            fprintf(fdot,"                 <TR>\n");
            fprintf(fdot,"                     <TD COLSPAN=\"1\" ROWSPAN=\"1\"><FONT POINT-SIZE=\"16\">part_type_1</FONT></TD>\n");
            fprintf(fdot,"                     <TD COLSPAN=\"1\" ROWSPAN=\"1\"><FONT POINT-SIZE=\"16\">%c</FONT></TD>\n",test_mbr.mbr_partition_1.part_type);
            fprintf(fdot,"                 </TR>\n");

            //---part fit
            fprintf(fdot,"                 <TR>\n");
            fprintf(fdot,"                     <TD COLSPAN=\"1\" ROWSPAN=\"1\"><FONT POINT-SIZE=\"16\">part_fit_1</FONT></TD>\n");
            fprintf(fdot,"                     <TD COLSPAN=\"1\" ROWSPAN=\"1\"><FONT POINT-SIZE=\"16\">%c</FONT></TD>\n",test_mbr.mbr_partition_1.part_fit);
            fprintf(fdot,"                 </TR>\n");

            //---part start
            fprintf(fdot,"                 <TR>\n");
            fprintf(fdot,"                     <TD COLSPAN=\"1\" ROWSPAN=\"1\"><FONT POINT-SIZE=\"16\">part_start_1</FONT></TD>\n");
            fprintf(fdot,"                     <TD COLSPAN=\"1\" ROWSPAN=\"1\"><FONT POINT-SIZE=\"16\">%d</FONT></TD>\n",test_mbr.mbr_partition_1.part_start);
            fprintf(fdot,"                 </TR>\n");

            //---part_size_1
            fprintf(fdot,"                 <TR>\n");
            fprintf(fdot,"                     <TD COLSPAN=\"1\" ROWSPAN=\"1\"><FONT POINT-SIZE=\"16\">part_size_1</FONT></TD>\n");
            fprintf(fdot,"                     <TD COLSPAN=\"1\" ROWSPAN=\"1\"><FONT POINT-SIZE=\"16\">%d</FONT></TD>\n",test_mbr.mbr_partition_1.part_size);
            fprintf(fdot,"                 </TR>\n");

            //---part_name_1
            fprintf(fdot,"                 <TR>\n");
            fprintf(fdot,"                     <TD COLSPAN=\"1\" ROWSPAN=\"1\"><FONT POINT-SIZE=\"16\">part_name_1</FONT></TD>\n");
            fprintf(fdot,"                     <TD COLSPAN=\"1\" ROWSPAN=\"1\"><FONT POINT-SIZE=\"16\">%s</FONT></TD>\n",test_mbr.mbr_partition_1.part_name);
            fprintf(fdot,"                 </TR>\n");

        }
        else
        {
            fprintf(fdot,"                 <TR>\n");
            fprintf(fdot,"                     <TD COLSPAN=\"1\" ROWSPAN=\"1\"><FONT POINT-SIZE=\"16\">part_status_1</FONT></TD>\n");
            fprintf(fdot,"                     <TD COLSPAN=\"1\" ROWSPAN=\"1\"><FONT POINT-SIZE=\"16\">%d</FONT></TD>\n",0);
            fprintf(fdot,"                 </TR>\n");
        }


        if(test_mbr.mbr_partition_2.part_status=='A'){

            if(test_mbr.mbr_partition_2.part_type == 'E'){
                particion = 2;
            }

            //part status
            fprintf(fdot,"                 <TR>\n");
            fprintf(fdot,"                     <TD COLSPAN=\"1\" ROWSPAN=\"1\"><FONT POINT-SIZE=\"16\">part_status_2</FONT></TD>\n");
            fprintf(fdot,"                     <TD COLSPAN=\"1\" ROWSPAN=\"1\"><FONT POINT-SIZE=\"16\">%d</FONT></TD>\n",1);
            fprintf(fdot,"                 </TR>\n");

            //part type
            fprintf(fdot,"                 <TR>\n");
            fprintf(fdot,"                     <TD COLSPAN=\"1\" ROWSPAN=\"1\"><FONT POINT-SIZE=\"16\">part_type_2</FONT></TD>\n");
            fprintf(fdot,"                     <TD COLSPAN=\"1\" ROWSPAN=\"1\"><FONT POINT-SIZE=\"16\">%c</FONT></TD>\n",test_mbr.mbr_partition_2.part_type);
            fprintf(fdot,"                 </TR>\n");

            //---part fit
            fprintf(fdot,"                 <TR>\n");
            fprintf(fdot,"                     <TD COLSPAN=\"1\" ROWSPAN=\"1\"><FONT POINT-SIZE=\"16\">part_fit_2</FONT></TD>\n");
            fprintf(fdot,"                     <TD COLSPAN=\"1\" ROWSPAN=\"1\"><FONT POINT-SIZE=\"16\">%c</FONT></TD>\n",test_mbr.mbr_partition_2.part_fit);
            fprintf(fdot,"                 </TR>\n");

            //---part start
            fprintf(fdot,"                 <TR>\n");
            fprintf(fdot,"                     <TD COLSPAN=\"1\" ROWSPAN=\"1\"><FONT POINT-SIZE=\"16\">part_start_2</FONT></TD>\n");
            fprintf(fdot,"                     <TD COLSPAN=\"1\" ROWSPAN=\"1\"><FONT POINT-SIZE=\"16\">%d</FONT></TD>\n",test_mbr.mbr_partition_2.part_start);
            fprintf(fdot,"                 </TR>\n");

            //---part_size_1
            fprintf(fdot,"                 <TR>\n");
            fprintf(fdot,"                     <TD COLSPAN=\"1\" ROWSPAN=\"1\"><FONT POINT-SIZE=\"16\">part_size_2</FONT></TD>\n");
            fprintf(fdot,"                     <TD COLSPAN=\"1\" ROWSPAN=\"1\"><FONT POINT-SIZE=\"16\">%d</FONT></TD>\n",test_mbr.mbr_partition_2.part_size);
            fprintf(fdot,"                 </TR>\n");

            //---part_name_1
            fprintf(fdot,"                 <TR>\n");
            fprintf(fdot,"                     <TD COLSPAN=\"1\" ROWSPAN=\"1\"><FONT POINT-SIZE=\"16\">part_name_2</FONT></TD>\n");
            fprintf(fdot,"                     <TD COLSPAN=\"1\" ROWSPAN=\"1\"><FONT POINT-SIZE=\"16\">%s</FONT></TD>\n",test_mbr.mbr_partition_2.part_name);
            fprintf(fdot,"                 </TR>\n");

        }else{

            fprintf(fdot,"                 <TR>\n");
            fprintf(fdot,"                     <TD COLSPAN=\"1\" ROWSPAN=\"1\"><FONT POINT-SIZE=\"16\">part_status_2</FONT></TD>\n");
            fprintf(fdot,"                     <TD COLSPAN=\"1\" ROWSPAN=\"1\"><FONT POINT-SIZE=\"16\">%d</FONT></TD>\n",0);
            fprintf(fdot,"                 </TR>\n");
        }


        if(test_mbr.mbr_partition_3.part_status=='A'){

            if(test_mbr.mbr_partition_3.part_type=='E'){
                particion = 3;
            }

            //part status
            fprintf(fdot,"                 <TR>\n");
            fprintf(fdot,"                     <TD COLSPAN=\"1\" ROWSPAN=\"1\"><FONT POINT-SIZE=\"16\">part_status_3</FONT></TD>\n");
            fprintf(fdot,"                     <TD COLSPAN=\"1\" ROWSPAN=\"1\"><FONT POINT-SIZE=\"16\">%d</FONT></TD>\n",1);
            fprintf(fdot,"                 </TR>\n");

            //part type
            fprintf(fdot,"                 <TR>\n");
            fprintf(fdot,"                     <TD COLSPAN=\"1\" ROWSPAN=\"1\"><FONT POINT-SIZE=\"16\">part_type_3</FONT></TD>\n");
            fprintf(fdot,"                     <TD COLSPAN=\"1\" ROWSPAN=\"1\"><FONT POINT-SIZE=\"16\">%c</FONT></TD>\n",test_mbr.mbr_partition_3.part_type);
            fprintf(fdot,"                 </TR>\n");

            //---part fit
            fprintf(fdot,"                 <TR>\n");
            fprintf(fdot,"                     <TD COLSPAN=\"1\" ROWSPAN=\"1\"><FONT POINT-SIZE=\"16\">part_fit_3</FONT></TD>\n");
            fprintf(fdot,"                     <TD COLSPAN=\"1\" ROWSPAN=\"1\"><FONT POINT-SIZE=\"16\">%c</FONT></TD>\n",test_mbr.mbr_partition_3.part_fit);
            fprintf(fdot,"                 </TR>\n");

            //---part start
            fprintf(fdot,"                 <TR>\n");
            fprintf(fdot,"                     <TD COLSPAN=\"1\" ROWSPAN=\"1\"><FONT POINT-SIZE=\"16\">part_start_3</FONT></TD>\n");
            fprintf(fdot,"                     <TD COLSPAN=\"1\" ROWSPAN=\"1\"><FONT POINT-SIZE=\"16\">%d</FONT></TD>\n",test_mbr.mbr_partition_3.part_start);
            fprintf(fdot,"                 </TR>\n");

            //---part_size_1
            fprintf(fdot,"                 <TR>\n");
            fprintf(fdot,"                     <TD COLSPAN=\"1\" ROWSPAN=\"1\"><FONT POINT-SIZE=\"16\">part_size_3</FONT></TD>\n");
            fprintf(fdot,"                     <TD COLSPAN=\"1\" ROWSPAN=\"1\"><FONT POINT-SIZE=\"16\">%d</FONT></TD>\n",test_mbr.mbr_partition_3.part_size);
            fprintf(fdot,"                 </TR>\n");

            //---part_name_1
            fprintf(fdot,"                 <TR>\n");
            fprintf(fdot,"                     <TD COLSPAN=\"1\" ROWSPAN=\"1\"><FONT POINT-SIZE=\"16\">part_name_3</FONT></TD>\n");
            fprintf(fdot,"                     <TD COLSPAN=\"1\" ROWSPAN=\"1\"><FONT POINT-SIZE=\"16\">%s</FONT></TD>\n",test_mbr.mbr_partition_3.part_name    );
            fprintf(fdot,"                 </TR>\n");

        }else{

            fprintf(fdot,"                 <TR>\n");
            fprintf(fdot,"                     <TD COLSPAN=\"1\" ROWSPAN=\"1\"><FONT POINT-SIZE=\"16\">part_status_3</FONT></TD>\n");
            fprintf(fdot,"                     <TD COLSPAN=\"1\" ROWSPAN=\"1\"><FONT POINT-SIZE=\"16\">%d</FONT></TD>\n",0);
            fprintf(fdot,"                 </TR>\n");

        }


        if(test_mbr.mbr_partition_4.part_status == 'A'){

            if(test_mbr.mbr_partition_4.part_type == 'E'){
                particion = 4;
            }

            //part status
            fprintf(fdot,"                 <TR>\n");
            fprintf(fdot,"                     <TD COLSPAN=\"1\" ROWSPAN=\"1\"><FONT POINT-SIZE=\"16\">part_status_4</FONT></TD>\n");
            fprintf(fdot,"                     <TD COLSPAN=\"1\" ROWSPAN=\"1\"><FONT POINT-SIZE=\"16\">%d</FONT></TD>\n",1);
            fprintf(fdot,"                 </TR>\n");

            //part type
            fprintf(fdot,"                 <TR>\n");
            fprintf(fdot,"                     <TD COLSPAN=\"1\" ROWSPAN=\"1\"><FONT POINT-SIZE=\"16\">part_type_4</FONT></TD>\n");
            fprintf(fdot,"                     <TD COLSPAN=\"1\" ROWSPAN=\"1\"><FONT POINT-SIZE=\"16\">%c</FONT></TD>\n",test_mbr.mbr_partition_4.part_type);
            fprintf(fdot,"                 </TR>\n");

            //---part fit
            fprintf(fdot,"                 <TR>\n");
            fprintf(fdot,"                     <TD COLSPAN=\"1\" ROWSPAN=\"1\"><FONT POINT-SIZE=\"16\">part_fit_4</FONT></TD>\n");
            fprintf(fdot,"                     <TD COLSPAN=\"1\" ROWSPAN=\"1\"><FONT POINT-SIZE=\"16\">%c</FONT></TD>\n",test_mbr.mbr_partition_4.part_fit);
            fprintf(fdot,"                 </TR>\n");

            //---part start
            fprintf(fdot,"                 <TR>\n");
            fprintf(fdot,"                     <TD COLSPAN=\"1\" ROWSPAN=\"1\"><FONT POINT-SIZE=\"16\">part_start_4</FONT></TD>\n");
            fprintf(fdot,"                     <TD COLSPAN=\"1\" ROWSPAN=\"1\"><FONT POINT-SIZE=\"16\">%d</FONT></TD>\n",test_mbr.mbr_partition_4.part_start);
            fprintf(fdot,"                 </TR>\n");

            //---part_size_1
            fprintf(fdot,"                 <TR>\n");
            fprintf(fdot,"                     <TD COLSPAN=\"1\" ROWSPAN=\"1\"><FONT POINT-SIZE=\"16\">part_size_4</FONT></TD>\n");
            fprintf(fdot,"                     <TD COLSPAN=\"1\" ROWSPAN=\"1\"><FONT POINT-SIZE=\"16\">%d</FONT></TD>\n",test_mbr.mbr_partition_4.part_size);
            fprintf(fdot,"                 </TR>\n");

            //---part_name_1
            fprintf(fdot,"                 <TR>\n");
            fprintf(fdot,"                     <TD COLSPAN=\"1\" ROWSPAN=\"1\"><FONT POINT-SIZE=\"16\">part_name_4</FONT></TD>\n");
            fprintf(fdot,"                     <TD COLSPAN=\"1\" ROWSPAN=\"1\"><FONT POINT-SIZE=\"16\">%s</FONT></TD>\n",test_mbr.mbr_partition_4.part_name);
            fprintf(fdot,"                 </TR>\n");

        }else{

            fprintf(fdot,"                 <TR>\n");
            fprintf(fdot,"                     <TD COLSPAN=\"1\" ROWSPAN=\"1\"><FONT POINT-SIZE=\"16\">part_status_4</FONT></TD>\n");
            fprintf(fdot,"                     <TD COLSPAN=\"1\" ROWSPAN=\"1\"><FONT POINT-SIZE=\"16\">%d</FONT></TD>\n",0);
            fprintf(fdot,"                 </TR>\n");

        }



        fprintf(fdot,"\n");
        fprintf(fdot,"\n");
        fprintf(fdot,"\n");
        fprintf(fdot,"\n");
        fprintf(fdot,"\n");
        fprintf(fdot,"\n");
        fprintf(fdot,"\n");
        fprintf(fdot,"\n");
        fprintf(fdot,"\n");
        fprintf(fdot,"           </TABLE>>  \n");
        fprintf(fdot,"   ]\n");



        //-------------------------------EBR SSSSS-----------------------------

        if(particion == 1){

            fseek(fmbr,test_mbr.mbr_partition_1.part_start,SEEK_SET);
            fread(&test_ebr,sizeof(test_ebr),1,fmbr);

            if(test_ebr.part_status == 'A'){

                fprintf(fdot," %s [\n",test_ebr.part_name);
                fprintf(fdot,"      style=filled label=<\n");
                fprintf(fdot,"           <TABLE BORDER=\"1\" CELLBORDER=\"1\" CELLSPACING=\"2\">\n");

                //--------
                fprintf(fdot,"                 <TR>\n");
                fprintf(fdot,"                     <TD COLSPAN=\"2\" ROWSPAN=\"1\"><FONT POINT-SIZE=\"16\">EBR(%s)</FONT></TD>\n",test_ebr.part_name);
                fprintf(fdot,"                 </TR>\n");

                //-----encabezado
                fprintf(fdot,"                 <TR>\n");
                fprintf(fdot,"                     <TD COLSPAN=\"1\" ROWSPAN=\"1\"><FONT POINT-SIZE=\"16\">Nombre</FONT></TD>\n");
                fprintf(fdot,"                     <TD COLSPAN=\"1\" ROWSPAN=\"1\"><FONT POINT-SIZE=\"16\">Valor</FONT></TD>\n");
                fprintf(fdot,"                 </TR>\n");
                //----part_status_1
                fprintf(fdot,"                 <TR>\n");
                fprintf(fdot,"                     <TD COLSPAN=\"1\" ROWSPAN=\"1\"><FONT POINT-SIZE=\"16\">part_status_1</FONT></TD>\n");
                fprintf(fdot,"                     <TD COLSPAN=\"1\" ROWSPAN=\"1\"><FONT POINT-SIZE=\"16\">%c</FONT></TD>\n",test_ebr.part_status);
                fprintf(fdot,"                 </TR>\n");
                //----part_fit_1
                fprintf(fdot,"                 <TR>\n");
                fprintf(fdot,"                     <TD COLSPAN=\"1\" ROWSPAN=\"1\"><FONT POINT-SIZE=\"16\">part_fit_1</FONT></TD>\n");
                fprintf(fdot,"                     <TD COLSPAN=\"1\" ROWSPAN=\"1\"><FONT POINT-SIZE=\"16\">%c</FONT></TD>\n",test_ebr.part_fit);
                fprintf(fdot,"                 </TR>\n");
                //----part_start_1
                fprintf(fdot,"                 <TR>\n");
                fprintf(fdot,"                     <TD COLSPAN=\"1\" ROWSPAN=\"1\"><FONT POINT-SIZE=\"16\">part_start_1</FONT></TD>\n");
                fprintf(fdot,"                     <TD COLSPAN=\"1\" ROWSPAN=\"1\"><FONT POINT-SIZE=\"16\">%d</FONT></TD>\n",test_ebr.part_start);
                fprintf(fdot,"                 </TR>\n");
                //------part_size_1
                fprintf(fdot,"                 <TR>\n");
                fprintf(fdot,"                     <TD COLSPAN=\"1\" ROWSPAN=\"1\"><FONT POINT-SIZE=\"16\">part_size_1</FONT></TD>\n");
                fprintf(fdot,"                     <TD COLSPAN=\"1\" ROWSPAN=\"1\"><FONT POINT-SIZE=\"16\">%d</FONT></TD>\n",test_ebr.part_size);
                fprintf(fdot,"                 </TR>\n");
                //------part_next_1
                fprintf(fdot,"                 <TR>\n");
                fprintf(fdot,"                     <TD COLSPAN=\"1\" ROWSPAN=\"1\"><FONT POINT-SIZE=\"16\">part_next_1</FONT></TD>\n");
                fprintf(fdot,"                     <TD COLSPAN=\"1\" ROWSPAN=\"1\"><FONT POINT-SIZE=\"16\">%d</FONT></TD>\n",test_ebr.part_next);
                fprintf(fdot,"                 </TR>\n");
                //------part_name_1
                fprintf(fdot,"                 <TR>\n");
                fprintf(fdot,"                     <TD COLSPAN=\"1\" ROWSPAN=\"1\"><FONT POINT-SIZE=\"16\">part_name_1</FONT></TD>\n");
                fprintf(fdot,"                     <TD COLSPAN=\"1\" ROWSPAN=\"1\"><FONT POINT-SIZE=\"16\">%s</FONT></TD>\n",test_ebr.part_name);
                fprintf(fdot,"                 </TR>\n");

                fprintf(fdot,"           </TABLE>>  \n");
                fprintf(fdot,"   ]\n");

            }


            while(test_ebr.part_next != -1){

                fseek(fmbr,test_ebr.part_next,SEEK_SET);
                fread(&test_ebr,sizeof(test_ebr),1,fmbr);

                if(test_ebr.part_status == 'A'){

                    fprintf(fdot," %s [\n",test_ebr.part_name);
                    fprintf(fdot,"      style=filled label=<\n");
                    fprintf(fdot,"           <TABLE BORDER=\"1\" CELLBORDER=\"1\" CELLSPACING=\"2\">\n");

                    //--------
                    fprintf(fdot,"                 <TR>\n");
                    fprintf(fdot,"                     <TD COLSPAN=\"2\" ROWSPAN=\"1\"><FONT POINT-SIZE=\"16\">EBR(%s)</FONT></TD>\n",test_ebr.part_name);
                    fprintf(fdot,"                 </TR>\n");

                    //-----encabezado
                    fprintf(fdot,"                 <TR>\n");
                    fprintf(fdot,"                     <TD COLSPAN=\"1\" ROWSPAN=\"1\"><FONT POINT-SIZE=\"16\">Nombre</FONT></TD>\n");
                    fprintf(fdot,"                     <TD COLSPAN=\"1\" ROWSPAN=\"1\"><FONT POINT-SIZE=\"16\">Valor</FONT></TD>\n");
                    fprintf(fdot,"                 </TR>\n");

                    //----part_status_1
                    fprintf(fdot,"                 <TR>\n");
                    fprintf(fdot,"                     <TD COLSPAN=\"1\" ROWSPAN=\"1\"><FONT POINT-SIZE=\"16\">part_status_1</FONT></TD>\n");
                    fprintf(fdot,"                     <TD COLSPAN=\"1\" ROWSPAN=\"1\"><FONT POINT-SIZE=\"16\">%c</FONT></TD>\n",test_ebr.part_status);
                    fprintf(fdot,"                 </TR>\n");

                    //----part_fit_1
                    fprintf(fdot,"                 <TR>\n");
                    fprintf(fdot,"                     <TD COLSPAN=\"1\" ROWSPAN=\"1\"><FONT POINT-SIZE=\"16\">part_fit_1</FONT></TD>\n");
                    fprintf(fdot,"                     <TD COLSPAN=\"1\" ROWSPAN=\"1\"><FONT POINT-SIZE=\"16\">%c</FONT></TD>\n",test_ebr.part_fit);
                    fprintf(fdot,"                 </TR>\n");

                    //----part_start_1
                    fprintf(fdot,"                 <TR>\n");
                    fprintf(fdot,"                     <TD COLSPAN=\"1\" ROWSPAN=\"1\"><FONT POINT-SIZE=\"16\">part_start_1</FONT></TD>\n");
                    fprintf(fdot,"                     <TD COLSPAN=\"1\" ROWSPAN=\"1\"><FONT POINT-SIZE=\"16\">%d</FONT></TD>\n",test_ebr.part_start);
                    fprintf(fdot,"                 </TR>\n");

                    //------part_size_1
                    fprintf(fdot,"                 <TR>\n");
                    fprintf(fdot,"                     <TD COLSPAN=\"1\" ROWSPAN=\"1\"><FONT POINT-SIZE=\"16\">part_size_1</FONT></TD>\n");
                    fprintf(fdot,"                     <TD COLSPAN=\"1\" ROWSPAN=\"1\"><FONT POINT-SIZE=\"16\">%d</FONT></TD>\n",test_ebr.part_size);
                    fprintf(fdot,"                 </TR>\n");

                    //------part_next_1
                    fprintf(fdot,"                 <TR>\n");
                    fprintf(fdot,"                     <TD COLSPAN=\"1\" ROWSPAN=\"1\"><FONT POINT-SIZE=\"16\">part_next_1</FONT></TD>\n");
                    fprintf(fdot,"                     <TD COLSPAN=\"1\" ROWSPAN=\"1\"><FONT POINT-SIZE=\"16\">%d</FONT></TD>\n",test_ebr.part_next);
                    fprintf(fdot,"                 </TR>\n");

                    //------part_name_1
                    fprintf(fdot,"                 <TR>\n");
                    fprintf(fdot,"                     <TD COLSPAN=\"1\" ROWSPAN=\"1\"><FONT POINT-SIZE=\"16\">part_name_1</FONT></TD>\n");
                    fprintf(fdot,"                     <TD COLSPAN=\"1\" ROWSPAN=\"1\"><FONT POINT-SIZE=\"16\">%s</FONT></TD>\n",test_ebr.part_name);
                    fprintf(fdot,"                 </TR>\n");

                    fprintf(fdot,"           </TABLE>>  \n");
                    fprintf(fdot,"   ]\n");
                    fprintf(fdot,"\n");

                }

            }

            fprintf(fdot,"}\n");
            fprintf(fdot,"\n");
            //fflush(fdot);
            fclose(fdot);
            fclose(fmbr);
            char commandd [200] ="dot /home/marvin/Escritorio/grafmbr.dot -o ";
            strcat(commandd,pathJPG);
            strcat(commandd," -Tjpg");
            printf(commandd);
            system(commandd);


        }else if(particion == 2){

            fseek(fmbr,test_mbr.mbr_partition_2.part_start,SEEK_SET);
            fread(&test_ebr,sizeof(test_ebr),1,fmbr);

            if(test_ebr.part_status == 'A'){

                fprintf(fdot," %s [\n",test_ebr.part_name);
                fprintf(fdot,"      style=filled label=<\n");
                fprintf(fdot,"           <TABLE BORDER=\"1\" CELLBORDER=\"1\" CELLSPACING=\"2\">\n");

                //--------
                fprintf(fdot,"                 <TR>\n");
                fprintf(fdot,"                     <TD COLSPAN=\"2\" ROWSPAN=\"1\"><FONT POINT-SIZE=\"16\">EBR(%s)</FONT></TD>\n",test_ebr.part_name);
                fprintf(fdot,"                 </TR>\n");

                //-----encabezado
                fprintf(fdot,"                 <TR>\n");
                fprintf(fdot,"                     <TD COLSPAN=\"1\" ROWSPAN=\"1\"><FONT POINT-SIZE=\"16\">Nombre</FONT></TD>\n");
                fprintf(fdot,"                     <TD COLSPAN=\"1\" ROWSPAN=\"1\"><FONT POINT-SIZE=\"16\">Valor</FONT></TD>\n");
                fprintf(fdot,"                 </TR>\n");
                //----part_status_1
                fprintf(fdot,"                 <TR>\n");
                fprintf(fdot,"                     <TD COLSPAN=\"1\" ROWSPAN=\"1\"><FONT POINT-SIZE=\"16\">part_status_1</FONT></TD>\n");
                fprintf(fdot,"                     <TD COLSPAN=\"1\" ROWSPAN=\"1\"><FONT POINT-SIZE=\"16\">%c</FONT></TD>\n",test_ebr.part_status);
                fprintf(fdot,"                 </TR>\n");
                //----part_fit_1
                fprintf(fdot,"                 <TR>\n");
                fprintf(fdot,"                     <TD COLSPAN=\"1\" ROWSPAN=\"1\"><FONT POINT-SIZE=\"16\">part_fit_1</FONT></TD>\n");
                fprintf(fdot,"                     <TD COLSPAN=\"1\" ROWSPAN=\"1\"><FONT POINT-SIZE=\"16\">%c</FONT></TD>\n",test_ebr.part_fit);
                fprintf(fdot,"                 </TR>\n");
                //----part_start_1
                fprintf(fdot,"                 <TR>\n");
                fprintf(fdot,"                     <TD COLSPAN=\"1\" ROWSPAN=\"1\"><FONT POINT-SIZE=\"16\">part_start_1</FONT></TD>\n");
                fprintf(fdot,"                     <TD COLSPAN=\"1\" ROWSPAN=\"1\"><FONT POINT-SIZE=\"16\">%d</FONT></TD>\n",test_ebr.part_start);
                fprintf(fdot,"                 </TR>\n");
                //------part_size_1
                fprintf(fdot,"                 <TR>\n");
                fprintf(fdot,"                     <TD COLSPAN=\"1\" ROWSPAN=\"1\"><FONT POINT-SIZE=\"16\">part_size_1</FONT></TD>\n");
                fprintf(fdot,"                     <TD COLSPAN=\"1\" ROWSPAN=\"1\"><FONT POINT-SIZE=\"16\">%d</FONT></TD>\n",test_ebr.part_size);
                fprintf(fdot,"                 </TR>\n");
                //------part_next_1
                fprintf(fdot,"                 <TR>\n");
                fprintf(fdot,"                     <TD COLSPAN=\"1\" ROWSPAN=\"1\"><FONT POINT-SIZE=\"16\">part_next_1</FONT></TD>\n");
                fprintf(fdot,"                     <TD COLSPAN=\"1\" ROWSPAN=\"1\"><FONT POINT-SIZE=\"16\">%d</FONT></TD>\n",test_ebr.part_next);
                fprintf(fdot,"                 </TR>\n");
                //------part_name_1
                fprintf(fdot,"                 <TR>\n");
                fprintf(fdot,"                     <TD COLSPAN=\"1\" ROWSPAN=\"1\"><FONT POINT-SIZE=\"16\">part_name_1</FONT></TD>\n");
                fprintf(fdot,"                     <TD COLSPAN=\"1\" ROWSPAN=\"1\"><FONT POINT-SIZE=\"16\">%s</FONT></TD>\n",test_ebr.part_name);
                fprintf(fdot,"                 </TR>\n");

                fprintf(fdot,"           </TABLE>>  \n");
                fprintf(fdot,"   ]\n");

            }


            while(test_ebr.part_next != -1){

                fseek(fmbr,test_ebr.part_next,SEEK_SET);
                fread(&test_ebr,sizeof(test_ebr),1,fmbr);

                if(test_ebr.part_status == 'A'){

                    fprintf(fdot," %s [\n",test_ebr.part_name);
                    fprintf(fdot,"      style=filled label=<\n");
                    fprintf(fdot,"           <TABLE BORDER=\"1\" CELLBORDER=\"1\" CELLSPACING=\"2\">\n");

                    //--------
                    fprintf(fdot,"                 <TR>\n");
                    fprintf(fdot,"                     <TD COLSPAN=\"2\" ROWSPAN=\"1\"><FONT POINT-SIZE=\"16\">EBR(%s)</FONT></TD>\n",test_ebr.part_name);
                    fprintf(fdot,"                 </TR>\n");

                    //-----encabezado
                    fprintf(fdot,"                 <TR>\n");
                    fprintf(fdot,"                     <TD COLSPAN=\"1\" ROWSPAN=\"1\"><FONT POINT-SIZE=\"16\">Nombre</FONT></TD>\n");
                    fprintf(fdot,"                     <TD COLSPAN=\"1\" ROWSPAN=\"1\"><FONT POINT-SIZE=\"16\">Valor</FONT></TD>\n");
                    fprintf(fdot,"                 </TR>\n");

                    //----part_status_1
                    fprintf(fdot,"                 <TR>\n");
                    fprintf(fdot,"                     <TD COLSPAN=\"1\" ROWSPAN=\"1\"><FONT POINT-SIZE=\"16\">part_status_1</FONT></TD>\n");
                    fprintf(fdot,"                     <TD COLSPAN=\"1\" ROWSPAN=\"1\"><FONT POINT-SIZE=\"16\">%c</FONT></TD>\n",test_ebr.part_status);
                    fprintf(fdot,"                 </TR>\n");

                    //----part_fit_1
                    fprintf(fdot,"                 <TR>\n");
                    fprintf(fdot,"                     <TD COLSPAN=\"1\" ROWSPAN=\"1\"><FONT POINT-SIZE=\"16\">part_fit_1</FONT></TD>\n");
                    fprintf(fdot,"                     <TD COLSPAN=\"1\" ROWSPAN=\"1\"><FONT POINT-SIZE=\"16\">%c</FONT></TD>\n",test_ebr.part_fit);
                    fprintf(fdot,"                 </TR>\n");

                    //----part_start_1
                    fprintf(fdot,"                 <TR>\n");
                    fprintf(fdot,"                     <TD COLSPAN=\"1\" ROWSPAN=\"1\"><FONT POINT-SIZE=\"16\">part_start_1</FONT></TD>\n");
                    fprintf(fdot,"                     <TD COLSPAN=\"1\" ROWSPAN=\"1\"><FONT POINT-SIZE=\"16\">%d</FONT></TD>\n",test_ebr.part_start);
                    fprintf(fdot,"                 </TR>\n");

                    //------part_size_1
                    fprintf(fdot,"                 <TR>\n");
                    fprintf(fdot,"                     <TD COLSPAN=\"1\" ROWSPAN=\"1\"><FONT POINT-SIZE=\"16\">part_size_1</FONT></TD>\n");
                    fprintf(fdot,"                     <TD COLSPAN=\"1\" ROWSPAN=\"1\"><FONT POINT-SIZE=\"16\">%d</FONT></TD>\n",test_ebr.part_size);
                    fprintf(fdot,"                 </TR>\n");

                    //------part_next_1
                    fprintf(fdot,"                 <TR>\n");
                    fprintf(fdot,"                     <TD COLSPAN=\"1\" ROWSPAN=\"1\"><FONT POINT-SIZE=\"16\">part_next_1</FONT></TD>\n");
                    fprintf(fdot,"                     <TD COLSPAN=\"1\" ROWSPAN=\"1\"><FONT POINT-SIZE=\"16\">%d</FONT></TD>\n",test_ebr.part_next);
                    fprintf(fdot,"                 </TR>\n");

                    //------part_name_1
                    fprintf(fdot,"                 <TR>\n");
                    fprintf(fdot,"                     <TD COLSPAN=\"1\" ROWSPAN=\"1\"><FONT POINT-SIZE=\"16\">part_name_1</FONT></TD>\n");
                    fprintf(fdot,"                     <TD COLSPAN=\"1\" ROWSPAN=\"1\"><FONT POINT-SIZE=\"16\">%s</FONT></TD>\n",test_ebr.part_name);
                    fprintf(fdot,"                 </TR>\n");

                    fprintf(fdot,"           </TABLE>>  \n");
                    fprintf(fdot,"   ]\n");
                    fprintf(fdot,"\n");

                }

            }

            fprintf(fdot,"}\n");
            fprintf(fdot,"\n");
            //fflush(fdot);
            fclose(fdot);
            fclose(fmbr);
            char commandd [200] ="dot /home/marvin/Escritorio/grafmbr.dot -o ";
            strcat(commandd,pathJPG);
            strcat(commandd," -Tjpg");
            printf(commandd);
            system(commandd);

        }else if(particion == 3){

            fseek(fmbr,test_mbr.mbr_partition_3.part_start,SEEK_SET);
            fread(&test_ebr,sizeof(test_ebr),1,fmbr);

            if(test_ebr.part_status == 'A'){

                fprintf(fdot," %s [\n",test_ebr.part_name);
                fprintf(fdot,"      style=filled label=<\n");
                fprintf(fdot,"           <TABLE BORDER=\"1\" CELLBORDER=\"1\" CELLSPACING=\"2\">\n");

                //--------
                fprintf(fdot,"                 <TR>\n");
                fprintf(fdot,"                     <TD COLSPAN=\"2\" ROWSPAN=\"1\"><FONT POINT-SIZE=\"16\">EBR(%s)</FONT></TD>\n",test_ebr.part_name);
                fprintf(fdot,"                 </TR>\n");

                //-----encabezado
                fprintf(fdot,"                 <TR>\n");
                fprintf(fdot,"                     <TD COLSPAN=\"1\" ROWSPAN=\"1\"><FONT POINT-SIZE=\"16\">Nombre</FONT></TD>\n");
                fprintf(fdot,"                     <TD COLSPAN=\"1\" ROWSPAN=\"1\"><FONT POINT-SIZE=\"16\">Valor</FONT></TD>\n");
                fprintf(fdot,"                 </TR>\n");
                //----part_status_1
                fprintf(fdot,"                 <TR>\n");
                fprintf(fdot,"                     <TD COLSPAN=\"1\" ROWSPAN=\"1\"><FONT POINT-SIZE=\"16\">part_status_1</FONT></TD>\n");
                fprintf(fdot,"                     <TD COLSPAN=\"1\" ROWSPAN=\"1\"><FONT POINT-SIZE=\"16\">%c</FONT></TD>\n",test_ebr.part_status);
                fprintf(fdot,"                 </TR>\n");
                //----part_fit_1
                fprintf(fdot,"                 <TR>\n");
                fprintf(fdot,"                     <TD COLSPAN=\"1\" ROWSPAN=\"1\"><FONT POINT-SIZE=\"16\">part_fit_1</FONT></TD>\n");
                fprintf(fdot,"                     <TD COLSPAN=\"1\" ROWSPAN=\"1\"><FONT POINT-SIZE=\"16\">%c</FONT></TD>\n",test_ebr.part_fit);
                fprintf(fdot,"                 </TR>\n");
                //----part_start_1
                fprintf(fdot,"                 <TR>\n");
                fprintf(fdot,"                     <TD COLSPAN=\"1\" ROWSPAN=\"1\"><FONT POINT-SIZE=\"16\">part_start_1</FONT></TD>\n");
                fprintf(fdot,"                     <TD COLSPAN=\"1\" ROWSPAN=\"1\"><FONT POINT-SIZE=\"16\">%d</FONT></TD>\n",test_ebr.part_start);
                fprintf(fdot,"                 </TR>\n");
                //------part_size_1
                fprintf(fdot,"                 <TR>\n");
                fprintf(fdot,"                     <TD COLSPAN=\"1\" ROWSPAN=\"1\"><FONT POINT-SIZE=\"16\">part_size_1</FONT></TD>\n");
                fprintf(fdot,"                     <TD COLSPAN=\"1\" ROWSPAN=\"1\"><FONT POINT-SIZE=\"16\">%d</FONT></TD>\n",test_ebr.part_size);
                fprintf(fdot,"                 </TR>\n");
                //------part_next_1
                fprintf(fdot,"                 <TR>\n");
                fprintf(fdot,"                     <TD COLSPAN=\"1\" ROWSPAN=\"1\"><FONT POINT-SIZE=\"16\">part_next_1</FONT></TD>\n");
                fprintf(fdot,"                     <TD COLSPAN=\"1\" ROWSPAN=\"1\"><FONT POINT-SIZE=\"16\">%d</FONT></TD>\n",test_ebr.part_next);
                fprintf(fdot,"                 </TR>\n");
                //------part_name_1
                fprintf(fdot,"                 <TR>\n");
                fprintf(fdot,"                     <TD COLSPAN=\"1\" ROWSPAN=\"1\"><FONT POINT-SIZE=\"16\">part_name_1</FONT></TD>\n");
                fprintf(fdot,"                     <TD COLSPAN=\"1\" ROWSPAN=\"1\"><FONT POINT-SIZE=\"16\">%s</FONT></TD>\n",test_ebr.part_name);
                fprintf(fdot,"                 </TR>\n");

                fprintf(fdot,"           </TABLE>>  \n");
                fprintf(fdot,"   ]\n");

            }


            while(test_ebr.part_next != -1){

                fseek(fmbr,test_ebr.part_next,SEEK_SET);
                fread(&test_ebr,sizeof(test_ebr),1,fmbr);

                if(test_ebr.part_status == 'A'){

                    fprintf(fdot," %s [\n",test_ebr.part_name);
                    fprintf(fdot,"      style=filled label=<\n");
                    fprintf(fdot,"           <TABLE BORDER=\"1\" CELLBORDER=\"1\" CELLSPACING=\"2\">\n");

                    //--------
                    fprintf(fdot,"                 <TR>\n");
                    fprintf(fdot,"                     <TD COLSPAN=\"2\" ROWSPAN=\"1\"><FONT POINT-SIZE=\"16\">EBR(%s)</FONT></TD>\n",test_ebr.part_name);
                    fprintf(fdot,"                 </TR>\n");

                    //-----encabezado
                    fprintf(fdot,"                 <TR>\n");
                    fprintf(fdot,"                     <TD COLSPAN=\"1\" ROWSPAN=\"1\"><FONT POINT-SIZE=\"16\">Nombre</FONT></TD>\n");
                    fprintf(fdot,"                     <TD COLSPAN=\"1\" ROWSPAN=\"1\"><FONT POINT-SIZE=\"16\">Valor</FONT></TD>\n");
                    fprintf(fdot,"                 </TR>\n");

                    //----part_status_1
                    fprintf(fdot,"                 <TR>\n");
                    fprintf(fdot,"                     <TD COLSPAN=\"1\" ROWSPAN=\"1\"><FONT POINT-SIZE=\"16\">part_status_1</FONT></TD>\n");
                    fprintf(fdot,"                     <TD COLSPAN=\"1\" ROWSPAN=\"1\"><FONT POINT-SIZE=\"16\">%c</FONT></TD>\n",test_ebr.part_status);
                    fprintf(fdot,"                 </TR>\n");

                    //----part_fit_1
                    fprintf(fdot,"                 <TR>\n");
                    fprintf(fdot,"                     <TD COLSPAN=\"1\" ROWSPAN=\"1\"><FONT POINT-SIZE=\"16\">part_fit_1</FONT></TD>\n");
                    fprintf(fdot,"                     <TD COLSPAN=\"1\" ROWSPAN=\"1\"><FONT POINT-SIZE=\"16\">%c</FONT></TD>\n",test_ebr.part_fit);
                    fprintf(fdot,"                 </TR>\n");

                    //----part_start_1
                    fprintf(fdot,"                 <TR>\n");
                    fprintf(fdot,"                     <TD COLSPAN=\"1\" ROWSPAN=\"1\"><FONT POINT-SIZE=\"16\">part_start_1</FONT></TD>\n");
                    fprintf(fdot,"                     <TD COLSPAN=\"1\" ROWSPAN=\"1\"><FONT POINT-SIZE=\"16\">%d</FONT></TD>\n",test_ebr.part_start);
                    fprintf(fdot,"                 </TR>\n");

                    //------part_size_1
                    fprintf(fdot,"                 <TR>\n");
                    fprintf(fdot,"                     <TD COLSPAN=\"1\" ROWSPAN=\"1\"><FONT POINT-SIZE=\"16\">part_size_1</FONT></TD>\n");
                    fprintf(fdot,"                     <TD COLSPAN=\"1\" ROWSPAN=\"1\"><FONT POINT-SIZE=\"16\">%d</FONT></TD>\n",test_ebr.part_size);
                    fprintf(fdot,"                 </TR>\n");

                    //------part_next_1
                    fprintf(fdot,"                 <TR>\n");
                    fprintf(fdot,"                     <TD COLSPAN=\"1\" ROWSPAN=\"1\"><FONT POINT-SIZE=\"16\">part_next_1</FONT></TD>\n");
                    fprintf(fdot,"                     <TD COLSPAN=\"1\" ROWSPAN=\"1\"><FONT POINT-SIZE=\"16\">%d</FONT></TD>\n",test_ebr.part_next);
                    fprintf(fdot,"                 </TR>\n");

                    //------part_name_1
                    fprintf(fdot,"                 <TR>\n");
                    fprintf(fdot,"                     <TD COLSPAN=\"1\" ROWSPAN=\"1\"><FONT POINT-SIZE=\"16\">part_name_1</FONT></TD>\n");
                    fprintf(fdot,"                     <TD COLSPAN=\"1\" ROWSPAN=\"1\"><FONT POINT-SIZE=\"16\">%s</FONT></TD>\n",test_ebr.part_name);
                    fprintf(fdot,"                 </TR>\n");

                    fprintf(fdot,"           </TABLE>>  \n");
                    fprintf(fdot,"   ]\n");
                    fprintf(fdot,"\n");

                }

            }

            fprintf(fdot,"}\n");
            fprintf(fdot,"\n");
            //fflush(fdot);
            fclose(fdot);
            fclose(fmbr);
            char commandd [200] ="dot /home/marvin/Escritorio/grafmbr.dot -o ";
            strcat(commandd,pathJPG);
            strcat(commandd," -Tjpg");
            printf(commandd);
            system(commandd);

        }else if(particion == 4){

            fseek(fmbr,test_mbr.mbr_partition_4.part_start,SEEK_SET);
            fread(&test_ebr,sizeof(test_ebr),1,fmbr);

            if(test_ebr.part_status == 'A'){

                fprintf(fdot," %s [\n",test_ebr.part_name);
                fprintf(fdot,"      style=filled label=<\n");
                fprintf(fdot,"           <TABLE BORDER=\"1\" CELLBORDER=\"1\" CELLSPACING=\"2\">\n");

                //--------
                fprintf(fdot,"                 <TR>\n");
                fprintf(fdot,"                     <TD COLSPAN=\"2\" ROWSPAN=\"1\"><FONT POINT-SIZE=\"16\">EBR(%s)</FONT></TD>\n",test_ebr.part_name);
                fprintf(fdot,"                 </TR>\n");

                //-----encabezado
                fprintf(fdot,"                 <TR>\n");
                fprintf(fdot,"                     <TD COLSPAN=\"1\" ROWSPAN=\"1\"><FONT POINT-SIZE=\"16\">Nombre</FONT></TD>\n");
                fprintf(fdot,"                     <TD COLSPAN=\"1\" ROWSPAN=\"1\"><FONT POINT-SIZE=\"16\">Valor</FONT></TD>\n");
                fprintf(fdot,"                 </TR>\n");
                //----part_status_1
                fprintf(fdot,"                 <TR>\n");
                fprintf(fdot,"                     <TD COLSPAN=\"1\" ROWSPAN=\"1\"><FONT POINT-SIZE=\"16\">part_status_1</FONT></TD>\n");
                fprintf(fdot,"                     <TD COLSPAN=\"1\" ROWSPAN=\"1\"><FONT POINT-SIZE=\"16\">%c</FONT></TD>\n",test_ebr.part_status);
                fprintf(fdot,"                 </TR>\n");
                //----part_fit_1
                fprintf(fdot,"                 <TR>\n");
                fprintf(fdot,"                     <TD COLSPAN=\"1\" ROWSPAN=\"1\"><FONT POINT-SIZE=\"16\">part_fit_1</FONT></TD>\n");
                fprintf(fdot,"                     <TD COLSPAN=\"1\" ROWSPAN=\"1\"><FONT POINT-SIZE=\"16\">%c</FONT></TD>\n",test_ebr.part_fit);
                fprintf(fdot,"                 </TR>\n");
                //----part_start_1
                fprintf(fdot,"                 <TR>\n");
                fprintf(fdot,"                     <TD COLSPAN=\"1\" ROWSPAN=\"1\"><FONT POINT-SIZE=\"16\">part_start_1</FONT></TD>\n");
                fprintf(fdot,"                     <TD COLSPAN=\"1\" ROWSPAN=\"1\"><FONT POINT-SIZE=\"16\">%d</FONT></TD>\n",test_ebr.part_start);
                fprintf(fdot,"                 </TR>\n");
                //------part_size_1
                fprintf(fdot,"                 <TR>\n");
                fprintf(fdot,"                     <TD COLSPAN=\"1\" ROWSPAN=\"1\"><FONT POINT-SIZE=\"16\">part_size_1</FONT></TD>\n");
                fprintf(fdot,"                     <TD COLSPAN=\"1\" ROWSPAN=\"1\"><FONT POINT-SIZE=\"16\">%d</FONT></TD>\n",test_ebr.part_size);
                fprintf(fdot,"                 </TR>\n");
                //------part_next_1
                fprintf(fdot,"                 <TR>\n");
                fprintf(fdot,"                     <TD COLSPAN=\"1\" ROWSPAN=\"1\"><FONT POINT-SIZE=\"16\">part_next_1</FONT></TD>\n");
                fprintf(fdot,"                     <TD COLSPAN=\"1\" ROWSPAN=\"1\"><FONT POINT-SIZE=\"16\">%d</FONT></TD>\n",test_ebr.part_next);
                fprintf(fdot,"                 </TR>\n");
                //------part_name_1
                fprintf(fdot,"                 <TR>\n");
                fprintf(fdot,"                     <TD COLSPAN=\"1\" ROWSPAN=\"1\"><FONT POINT-SIZE=\"16\">part_name_1</FONT></TD>\n");
                fprintf(fdot,"                     <TD COLSPAN=\"1\" ROWSPAN=\"1\"><FONT POINT-SIZE=\"16\">%s</FONT></TD>\n",test_ebr.part_name);
                fprintf(fdot,"                 </TR>\n");

                fprintf(fdot,"           </TABLE>>  \n");
                fprintf(fdot,"   ]\n");

            }


            while(test_ebr.part_next != -1){

                fseek(fmbr,test_ebr.part_next,SEEK_SET);
                fread(&test_ebr,sizeof(test_ebr),1,fmbr);

                if(test_ebr.part_status == 'A'){

                    fprintf(fdot," %s [\n",test_ebr.part_name);
                    fprintf(fdot,"      style=filled label=<\n");
                    fprintf(fdot,"           <TABLE BORDER=\"1\" CELLBORDER=\"1\" CELLSPACING=\"2\">\n");

                    //--------
                    fprintf(fdot,"                 <TR>\n");
                    fprintf(fdot,"                     <TD COLSPAN=\"2\" ROWSPAN=\"1\"><FONT POINT-SIZE=\"16\">EBR(%s)</FONT></TD>\n",test_ebr.part_name);
                    fprintf(fdot,"                 </TR>\n");

                    //-----encabezado
                    fprintf(fdot,"                 <TR>\n");
                    fprintf(fdot,"                     <TD COLSPAN=\"1\" ROWSPAN=\"1\"><FONT POINT-SIZE=\"16\">Nombre</FONT></TD>\n");
                    fprintf(fdot,"                     <TD COLSPAN=\"1\" ROWSPAN=\"1\"><FONT POINT-SIZE=\"16\">Valor</FONT></TD>\n");
                    fprintf(fdot,"                 </TR>\n");

                    //----part_status_1
                    fprintf(fdot,"                 <TR>\n");
                    fprintf(fdot,"                     <TD COLSPAN=\"1\" ROWSPAN=\"1\"><FONT POINT-SIZE=\"16\">part_status_1</FONT></TD>\n");
                    fprintf(fdot,"                     <TD COLSPAN=\"1\" ROWSPAN=\"1\"><FONT POINT-SIZE=\"16\">%c</FONT></TD>\n",test_ebr.part_status);
                    fprintf(fdot,"                 </TR>\n");

                    //----part_fit_1
                    fprintf(fdot,"                 <TR>\n");
                    fprintf(fdot,"                     <TD COLSPAN=\"1\" ROWSPAN=\"1\"><FONT POINT-SIZE=\"16\">part_fit_1</FONT></TD>\n");
                    fprintf(fdot,"                     <TD COLSPAN=\"1\" ROWSPAN=\"1\"><FONT POINT-SIZE=\"16\">%c</FONT></TD>\n",test_ebr.part_fit);
                    fprintf(fdot,"                 </TR>\n");

                    //----part_start_1
                    fprintf(fdot,"                 <TR>\n");
                    fprintf(fdot,"                     <TD COLSPAN=\"1\" ROWSPAN=\"1\"><FONT POINT-SIZE=\"16\">part_start_1</FONT></TD>\n");
                    fprintf(fdot,"                     <TD COLSPAN=\"1\" ROWSPAN=\"1\"><FONT POINT-SIZE=\"16\">%d</FONT></TD>\n",test_ebr.part_start);
                    fprintf(fdot,"                 </TR>\n");

                    //------part_size_1
                    fprintf(fdot,"                 <TR>\n");
                    fprintf(fdot,"                     <TD COLSPAN=\"1\" ROWSPAN=\"1\"><FONT POINT-SIZE=\"16\">part_size_1</FONT></TD>\n");
                    fprintf(fdot,"                     <TD COLSPAN=\"1\" ROWSPAN=\"1\"><FONT POINT-SIZE=\"16\">%d</FONT></TD>\n",test_ebr.part_size);
                    fprintf(fdot,"                 </TR>\n");

                    //------part_next_1
                    fprintf(fdot,"                 <TR>\n");
                    fprintf(fdot,"                     <TD COLSPAN=\"1\" ROWSPAN=\"1\"><FONT POINT-SIZE=\"16\">part_next_1</FONT></TD>\n");
                    fprintf(fdot,"                     <TD COLSPAN=\"1\" ROWSPAN=\"1\"><FONT POINT-SIZE=\"16\">%d</FONT></TD>\n",test_ebr.part_next);
                    fprintf(fdot,"                 </TR>\n");

                    //------part_name_1
                    fprintf(fdot,"                 <TR>\n");
                    fprintf(fdot,"                     <TD COLSPAN=\"1\" ROWSPAN=\"1\"><FONT POINT-SIZE=\"16\">part_name_1</FONT></TD>\n");
                    fprintf(fdot,"                     <TD COLSPAN=\"1\" ROWSPAN=\"1\"><FONT POINT-SIZE=\"16\">%s</FONT></TD>\n",test_ebr.part_name);
                    fprintf(fdot,"                 </TR>\n");

                    fprintf(fdot,"           </TABLE>>  \n");
                    fprintf(fdot,"   ]\n");
                    fprintf(fdot,"\n");

                }

            }

            fprintf(fdot,"}\n");
            fprintf(fdot,"\n");
            //fflush(fdot);
            fclose(fdot);
            fclose(fmbr);
            char commandd [200] ="dot /home/marvin/Escritorio/grafmbr.dot -o ";
            strcat(commandd,pathJPG);
            strcat(commandd," -Tjpg");
            printf(commandd);
            system(commandd);

        }

    }

}
