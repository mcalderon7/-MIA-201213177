#ifndef ESTRUCTURALISTAPARTICION_H_INCLUDED
#define ESTRUCTURALISTAPARTICION_H_INCLUDED

typedef struct nodo {
  char *dato;
  struct ElementoLista *siguiente;
}NODO;

typedef struct ListaNodos {
  NODO *inicio;
  NODO *fin;
  int tamano;
}LISTA_NODOS;

#endif
