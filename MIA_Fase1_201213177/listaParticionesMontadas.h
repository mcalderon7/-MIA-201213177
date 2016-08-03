#ifndef LISTAPARTICIONESMONTADAS_H_INCLUDED
#define LISTAPARTICIONESMONTADAS_H_INCLUDED
#include "estructuraListaParticion.h"

void iniciarLista (LISTA_NODOS *lista);
int insertarLista (LISTA_NODOS * lista, NODO * actual, char *dato);
int eliminarDeLaLista (LISTA_NODOS * lista);
void imprimirLista (LISTA_NODOS * lista);


#endif
