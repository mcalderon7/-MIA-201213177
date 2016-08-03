#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "listaParticionesMontadas.h"
#include "estructuraListaParticion.h"

int insertarLista (LISTA_NODOS * lista, NODO * actual, char *dato){
  NODO *nuevo_elemento;
  if ((nuevo_elemento = (NODO *) malloc (sizeof (NODO))) == NULL)
    return -1;
  if ((nuevo_elemento->dato = (char *) malloc (50 * sizeof (char)))
      == NULL)
    return -1;
  strcpy (nuevo_elemento->dato, dato);

  actual->siguiente = nuevo_elemento;
  nuevo_elemento->siguiente = NULL;

  lista->fin = nuevo_elemento;

  lista->tamano++;
  return 0;
}


int eliminarDeLaLista (LISTA_NODOS * lista){
  if (lista->tamano == 0)
    return -1;
  NODO *sup_elemento;
  sup_element = lista->inicio;
  lista->inicio = lista->inicio->siguiente;
  if (lista->tamano == 1)
    lista->fin = NULL;
  free (sup_elemento->dato);
  free (sup_elemento);
  lista->tamano--;
  return 0;
}


void imprimirLista (LISTA_NODOS * lista){
  NODO *actual;
  actual = lista->inicio;
  while (actual != NULL){
      printf ("%p - %s\n", actual, actual->dato);
      actual = actual->siguiente;
  }
}
