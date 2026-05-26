#ifndef LISTA_DOBLE_H
#define LISTA_DOBLE_H

#include "nododoble.h"

typedef struct 
{
	NodoD *inicio;
	NodoD *fin;
	int cant;
	int (*comparar)(void *datoA,void *datoB);
	void (*imprimir)(void *datoA);
	void (*liberar)(void *datoA);
}ListaD;


ListaD inicializarListaD(void);
void mostrarListaD(ListaD lista);
void imprimirListaDFI(ListaD lista);
void imprimirListaDIF(ListaD lista);
void insertarFinalD(ListaD*,void*);


void borrarListaD(ListaD *);
void borrarInicioD(ListaD *);
void borrarFinalD(ListaD *);


void insertarEnOrdenD(ListaD *lista,void* dato);
void insertarInicioD(ListaD *, void*);
int insertarEn(ListaD* lista, void *dato, int index);

void borrarDatoD(ListaD *lista,void* dato,int  (*)(void*,void*));
void buscarEnListaD(ListaD lista, void *dato);

void reordenarD(ListaD *,int  (*comparar)(void*,void*) );
void* removerInicio(ListaD *lista);

void insertarOrdenadoD(ListaD *lista,void* dato);
void insertarInicioD(ListaD *lista,void* dato);
void insertarEnPosicionD(ListaD *lista,void* dato,int pos);
void eliminarEnPosicionD(ListaD *lista,int pos);

int extraerMatricula(ListaD *lista,void *dato);



#endif