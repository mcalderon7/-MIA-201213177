#ifndef MONTARPARTICION_H_INCLUDED
#define MONTARPARTICION_H_INCLUDED

typedef struct nsx {
	char nombreParticion[20];
	char path[60];
	char idParticion[5];
	time_t hora_de_montado;
	struct nsx *next;
} xnode;

extern xnode *m;
xnode **xx_list_search(xnode **n, char* id);
void montarParticion(char *path, char *name, char *id);

#endif
