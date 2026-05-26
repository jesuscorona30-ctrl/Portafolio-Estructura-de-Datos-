#ifndef PILA_H
#define PILA_H

#include <stdio.h>
#include "nodo.h"
#include "nodoarbol.h"
#define MAX 100

typedef struct
{
	Nodo *cima;
	int cantidad;
	int capacidad;
	void (*imprimir)(void*);
	void (*liberar)(void*);
	int (*comparar)(void*,void*);
	
}Pila;

typedef struct
{
	NodoA *cima;
	int cantidad;
	int capacidad;
	void (*imprimir)(void*);
	void (*liberar)(void*);
	int (*comparar)(void*,void*);
	
}PilaA;


//VERIFICIACION
int pilaVacia(Pila pila);
int pilaLlena(Pila pila);
int verificarParentesis(char *cadena);

//DATOS
void pushDato(Pila *pila,void *dato); // Insertar
void* popDato(Pila *pila); //Eliminar
void *peekCima(Pila pila);

//NODOS
void pushNodo(Pila *pila,Nodo *nodo);
Nodo* popNodo(Pila *pila);


//VACIAR/ELIMINAR PILA
void vaciarPila(Pila *pila);
void eliminarPila(Pila *pila);


//IMPRIMIR
void imprimirPila(Pila pila);

//ORDENAR
void ordenarPila( Pila *pila);


void infixtoPostfix(char *cadena, char *postf);


void *peekCimaA(PilaA pila);
int pilaVaciaA(PilaA pila);
int pilaLlenaA(PilaA pila);
void pushDatoA(PilaA *pila,void *dato);
void* popDatoA(PilaA *pila);

void pushNodoA(PilaA *pila,NodoA *nodo);
NodoA* popNodoA(PilaA *pila);

#endif