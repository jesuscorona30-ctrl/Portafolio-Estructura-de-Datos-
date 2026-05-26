#ifndef NODO_ARBOL
#define NODO_ARBOL
#include <stdlib.h>

typedef struct nodoa
{
	struct nodoa *izq;
	struct nodoa *dch;
	struct nodoa *sig;
	void *dato;
}NodoA;

NodoA* crearNodoA(void *dato);

#endif