#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "listaDiscosMontados.h"

int ins_fin_lista (Lista * lista, Element * actual, char *dato){
  Element *nuevo_elemento;
  if ((nuevo_elemento = (Element *) malloc (sizeof (Element))) == NULL)
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


int sup_inicio (Lista * lista){
  if (lista->tamano == 0)
    return -1;
  Element *sup_element;
  sup_element = lista->inicio;
  lista->inicio = lista->inicio->siguiente;
  if (lista->tamano == 1)
    lista->fin = NULL;
  free (sup_element->dato);
  free (sup_element);
  lista->tamano--;
  return 0;
}


void visualizacion (Lista * lista){
  Element *actual;
  actual = lista->inicio;
  while (actual != NULL){
      printf ("%p - %s\n", actual, actual->dato);
      actual = actual->siguiente;
  }
}
