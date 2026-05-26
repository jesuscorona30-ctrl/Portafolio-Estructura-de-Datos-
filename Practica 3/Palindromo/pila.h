#ifndef PILA_H
#define PILA_H

#include <stdio.h>
#include "nodo.h"
#include <ctype.h> // Necesaria para usar tolower()
#include <string.h>
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

//VERIFICACION
int pilaVacia(Pila pila);
int pilaLlena(Pila pila);


//DATOS
void pushDato(Pila *pila,void *dato); // Insertar
void* popDato(Pila *pila); //Eliminar


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

#endif