#ifndef ESTRUCTURALISTASDISCO_H_INCLUDED
#define ESTRUCTURALISTASDISCO_H_INCLUDED

typedef struct ElementoLista {
  char *dato;
  struct ElementoLista *siguiente;
}Element;

typedef struct ListaIdentificar {
  Element *inicio;
  Element *fin;
  int tamano;
}Lista;

void inicializacion (Lista *lista);

#endif
