#ifndef BUSQUEDACARPETA_H_INCLUDED
#define BUSQUEDACARPETA_H_INCLUDED

void busqueda_creacion(int numero_de_particion, char *pathArchivo, char *pathDisco);
int busquedaCarpeta(int numero_de_particion, char* pathArchivo, char* pathDisco);
int obtenerApuntadorUltimaCarpeta(int numero_de_particion, char *pathArchivo, char *pathDisco);

#endif
