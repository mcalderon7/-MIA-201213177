#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <time.h>
#include "montarParticion.h"
#include "limpiar.h"
#include "vaciarArreglo.h"

char letras[26] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
int contadorLetras = 0;
int contadorLista = 1;
int contadorNodos = 1;

/*******************************************************************************************************************************************************************************************************************************/

typedef struct ns {
	char pathDisco[60];
	char letra;
	int contador;
	struct ns *next;
} node;

node *list_add(node **p, char* ruta, char letter, int counter) {
    /* algunos compiladores no requieren un casting del valor del retorno para malloc  */
    node *n = (node *)malloc(sizeof(node));
    if (n == NULL)
        return NULL;
    n->next = *p;
    *p = n;
    strcpy(n->pathDisco, ruta);
    n->letra = letter;
    n->contador = counter;
    return n;
}

void list_remove(node **p) { /* borrar cabeza*/
    if (*p != NULL) {
        node *n = *p;
	*p = (*p)->next;
	free(n);
    }
}

node **list_search(node **n, char* path) {

    char ruta[60];
    strcpy(ruta, path);

    while (*n != NULL) {
        if (strcmp((*n)->pathDisco, ruta) == 0) {
            return n;
        }
        n = &(*n)->next;
    }
    return NULL;
}

void list_print(node *n) {
    if (n == NULL) {
        printf("lista esta vacía\n");
    }
    while (n != NULL) {
        printf("print %p %p %s %c %d\n", n, n->next, n->pathDisco, n->letra, n->contador);
        n = n->next;
    }
}

/*******************************************************************************************************************************************************************************************************************************/

xnode *x_list_add(xnode **p, char* name, char* ruta, char* id_particion) {

    /*Inicializo la variable de tiempo*/
    time_t hora_de_mount = time(0);

    /* algunos compiladores no requieren un casting del valor del retorno para malloc  */
    xnode *n = (xnode *)malloc(sizeof(xnode));
    if (n == NULL)
        return NULL;
    n->next = *p;
    *p = n;
    strcpy(n->nombreParticion, name);
    strcpy(n->path, ruta);
    strcpy(n->idParticion, id_particion);
    n->hora_de_montado = hora_de_mount;
    return n;
}

void x_list_remove(xnode **p) { /* borrar cabeza*/
    if (*p != NULL) {
        xnode *n = *p;
	*p = (*p)->next;
	free(n);
    }
}

xnode **x_list_search(xnode **n, char* name) {

    char nombre[20];
    limpiar(nombre, 20);
    strcpy(nombre, name);

    while (*n != NULL) {
        if (strcmp((*n)->nombreParticion, nombre) == 0) {
            return n;
        }
        n = &(*n)->next;
    }
    return NULL;
}

xnode **xx_list_search(xnode **n, char* id) {

    char nombre[20];
    strcpy(nombre, id);

    while (*n != NULL) {
        if (strcmp((*n)->idParticion, id) == 0) {
            return n;
        }
        n = &(*n)->next;
    }
    return NULL;
}

void x_list_print(xnode *n) {
    if (n == NULL) {
        printf("lista esta vacía\n");
    }
    while (n != NULL) {
        printf("print %p %p %s %s %s\n", n, n->next, n->nombreParticion, n->path, n->idParticion);
        n = n->next;
    }
}

/*******************************************************************************************************************************************************************************************************************************/

node *n = NULL;
xnode *m = NULL;

/*******************************************************************************************************************************************************************************************************************************/

void montarParticion(char *path, char *name, char *id){

    /*Verifico que lo que venga no sea un unmount*/
    if ((id != NULL) && (id[0] == '\0')) {

        /*Primero verifico si la particion a montar ya esta montada*/
        xnode **z = NULL;

        /*Busco en la lista si ya existe alguna particion montada con ese nombre*/
        z = x_list_search(&m, name);

        /*Si la particion no existe (no esta montada), entonces procedemos, de lo contrario mostramos mensaje de error*/
        if(z == NULL){

            node **x = NULL;

            char full_path[60];
            strcpy(full_path, path);

            /*Verifico si ya existe el disco*/
            x = list_search(&n, full_path);

            if(x == NULL){

                //printf("NO LO ENCONTRO\n");

                /*Registro el disco*/
                list_add(&n, path, letras[contadorLetras], contadorLista);

                /*Registro la parte de la particion a montar*/
                char id_particion[5];
                vaciarArreglo(id_particion);
                strcpy(id_particion, "vd");
                id_particion[2] = letras[contadorLetras];
                char c = contadorLista + '0';
                id_particion[3] = c;

                x_list_add(&m, name, path, id_particion);

                /*Aumento el contador de letras para asignarle la siguiente al otro disco*/
                contadorLetras++;

            }else{

                //printf("SI LO ENCONTRO\n");

                char id_particion[5];
                vaciarArreglo(id_particion);
                strcpy(id_particion, "vd");
                id_particion[2] = (*x)->letra;
                (*x)->contador = (*x)->contador + 1;
                char c = (*x)->contador + '0';
                id_particion[3] = c;

                x_list_add(&m, name, path, id_particion);

            }


            /*IMPRIMO EL CONTENIDO DE LAS LISTAS*/
            printf("******************************************************************************\n");
            printf("IMPRESION DE NODOS\n");
            printf("******************************************************************************\n");
            printf("Lista de discos que han sido montados:\n");
            list_print(n);
            printf("******************************************************************************\n");
            printf("Lista de particiones que han sido montados:\n");
            x_list_print(m);
            printf("******************************************************************************\n");

        }else{
            printf("******************************************************************************\n");
            printf("La particion indicada ya se encuentra montada!\n");
            printf("******************************************************************************\n");
        }

    }else{

        /*Primero verifico que exista el ID que desea desmontar*/
        /*Primero verifico si la particion a montar ya esta montada*/
        xnode **z = NULL;

        /*Busco en la lista si ya existe alguna particion montada con ese nombre*/
        z = xx_list_search(&m, id);

        if(z == NULL){

            printf("******************************************************************************\n");
            printf("No se puede desmontar la particion porque no se encuentra montada!\n");
            printf("******************************************************************************\n");

        }else{

            /*Procedo a eliminar el nodo*/
            x_list_remove(xx_list_search(&m, id));

            printf("******************************************************************************\n");
            printf("Particion desmontada correctamente!\n");
            printf("******************************************************************************\n");

        }


    }


}
