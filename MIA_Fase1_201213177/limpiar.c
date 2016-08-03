#include "limpiar.h"

void limpiar(char* cadena, int tamanio){
    while(tamanio >= 0){
        cadena[tamanio] = '\0';
        tamanio--;
    }
}