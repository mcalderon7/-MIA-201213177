#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "analizar.h"
#include "removeSpaces.h"
#include "limpiar.h"
#include "vaciarArreglo.h"
#include "escanearCrearDisco.h"
#include "escanearRemoverDisco.h"
#include "escanearCrearParticion.h"
#include "escanearMontarParticion.h"
#include "escanearDesmontarParticion.h"
#include "escanearGraficarMBR.h"
#include "escanearEjecutarScript.h"
#include "escanearFormatearParticion.h"
#include "escanearCrearCarpetaArchivo.h"

void analizar(char *ingreso){

	/*Remuevo los espacios en blanco de la sentencia*/
	RemoveSpaces(ingreso);

	int cx = 0;
	int x = strlen(ingreso);
	int i;
	int estado = 0;
	char c;

	char auxlex[200];

	/*El siguiente ciclo sirve para analizar la primera palabra que viene en la sentencia
	 * para este caso solo pueden venir los siguientes tipos:
	 *
	 * mkdisk
	 * rmdisk
	 * fdisk
	 * mount
	 * unmount
	 *
	 * */

	/*Bandera que me indica si ya alcanzo la primera palabra completa de la sentencia ingresada*/
	int bandera = 0;

    for(i = 0; i < x; i++)
    {

		/*Bandera que me indica si ya alcanzo la primera palabra completa de la sentencia que se ingreso para no seguir analizando*/
		if(bandera == 0){

			c = ingreso[i];

			switch(estado){

				case 0:

					if(isalpha(c)){
						estado = 1;
						auxlex[cx] = c;
						cx++;
						break;
					}

				case 1:

					if(isalpha(c)){
						estado = 1;
						auxlex[cx] = c;
						cx++;
						break;
					}else if(c == '-'){

						/*Esto signfica que lo recien leido es valido, por lo que procedemos con el analisis*/

						if(strcmp(auxlex, "mkdisk") == 0){
							estado = 0;
							vaciarArreglo(auxlex);
							printf("encontro el mkdisk\n");
							/*Mando la cadena completa al analizador de creacion de discos*/
							escanearCrearDisco(ingreso);
							bandera = 1;
							break;
						}else if(strcmp(auxlex, "rmdisk") == 0){
							estado = 0;
							vaciarArreglo(auxlex);
							printf("encontro el rmdisk\n");
							/*Mando la cadena completa al analizador de eliminacion de discos*/
							escanearRemoverDisco(ingreso);
							bandera = 1;
							break;
						}else if(strcmp(auxlex, "fdisk") == 0){
							estado = 0;
							vaciarArreglo(auxlex);
							printf("encontro el fdisk\n");
							/*Mando la cadena completa al analizador de creacion de particiones*/
							escanearCrearParticion(ingreso);
							bandera = 1;
							break;
						}else if(strcmp(auxlex, "mount") == 0){
							estado = 0;
							vaciarArreglo(auxlex);
							printf("encontro el mount\n");
							/*Mando la cadena completa al analizador de montar particiones*/
							escanearMontarParticion(ingreso);
							bandera = 1;
							break;
						}else if(strcmp(auxlex, "unmount") == 0){
							estado = 0;
							vaciarArreglo(auxlex);
							printf("encontro el unmount\n");
							/*Mando la cadena completa al analizador de desmontar particiones*/
							escanearMontarParticion(ingreso);
							bandera = 1;
							break;
						}else if(strcmp(auxlex, "rep") == 0){
                            estado = 0;
							vaciarArreglo(auxlex);
							printf("encontro el rep\n");
							/*Mando la cadena completa al analizador de desmontar particiones*/
							escanearGraficarMBR(ingreso);
							bandera = 1;
							break;
						}else if(strcmp(auxlex, "mkfs") == 0){
                            estado = 0;
							vaciarArreglo(auxlex);
							printf("encontro el mkfs\n");
							/*Mando la cadena completa al analizador de desmontar particiones*/
							escanearFormatearParticion(ingreso);
							bandera = 1;
							break;
						}else if(strcmp(auxlex, "mkfile") == 0){
                            estado = 0;
							vaciarArreglo(auxlex);
							printf("encontro el mkfile\n");
							/*Mando la cadena completa al analizador de desmontar particiones*/
							escanearCrearCarpetaArchivo(ingreso);
							bandera = 1;
							break;
						}


					}else if(c == '/'){
                        if(strcmp(auxlex, "exec") == 0){
                            estado = 0;
							vaciarArreglo(auxlex);
							printf("encontro el exec\n");
							/*Mando la cadena completa al analizador de desmontar particiones*/
							escanearEjecutarScript(ingreso);
							bandera = 1;
							break;
						}
					}

			}

		}

    }

    bandera = 0;

}
