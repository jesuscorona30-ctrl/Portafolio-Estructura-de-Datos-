
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <time.h>
#include "heap.h"

int* crearEntero(int);
int compararEntero(void*,void*);
void imprimirEntero(void*);
void heapify_minimo(int *arr, int index);
void imprimirArr(int *arr);
void heapify_maximo(int *arr,int index);
void *eliminarDelHeap(Heap *heap);

int main(void)
{
	int arr[10] = {62,21,12,4,49,52,45,48,61,55};
	heapify_minimo(arr,9);
	imprimirArr(arr);
	///*
	Heap heap = crearHeap(HEAP_MIN,compararEntero,imprimirEntero);
	printf("\n INICIO");
	insertarHeap(&heap, crearEntero(7));
	insertarHeap(&heap, crearEntero(4));
	insertarHeap(&heap, crearEntero(5));
	insertarHeap(&heap, crearEntero(2));
	insertarHeap(&heap, crearEntero(1));
	insertarHeap(&heap, crearEntero(3));
	
	
	imprimirHeap(heap);
	heapify(&heap);
	imprimirHeap(heap);
	int *dato = eliminarDelHeap(&heap);
	printf("\nSe elimino el dato: %d",*dato);
	
	
	imprimirHeap(heap);
	
	//heap.tipo = HEAP_MAX;
	//heapify(&heap);
	//imprimirHeap(heap);
	
	//printf("\n");
	//heap_arbolBinario(&heap);
	//printf("\n");
	
	/*
	while(heap.cantidad)
	{
		printf("\n Cantidad:  %d",heap.cantidad);
		void *dato = eliminarHeap(&heap);
		printf("\n Dato eliminado: ");
		imprimirEntero(dato);
		free(dato);
	}*/



	printf("\n\n FIN DE PROGRAMA\n");
	//*/


	
	return 0;
}

void imprimirArr(int *arr)
{
	for(int i = 0; i < 10; i++)
	printf("%d\n",arr[i]);
}

void *eliminarDelHeap(Heap *heap)
{
	void **aux = NULL;
	void *dato = NULL;

	if(!heap->cantidad)
	return dato;

	else if(heap->cantidad == 1)
	{
		dato = heap->datos[0];
		free(heap->datos);
		heap->datos = NULL;
		heap->cantidad = 0;	
		return dato;	
	}

	//SI LA CANTIDAD ES MAS DE UNO
	else
	{
		dato = heap->datos[0];
		heap->datos[0] = heap->datos[heap->cantidad-1];
		heap->datos[heap->cantidad-1] = dato;
		while(!aux)
		aux = realloc(heap->datos,(heap->cantidad-1)*sizeof(void*));
		heap->datos = aux;
		heap->cantidad--;
		heapify(heap);
	}

	return dato;
}


void heapify_minimo(int *arr, int index)
{
	if(index < 0 || index > 10)
	return;

	int min = index;
	int izq = 2*index+1;
	int dch = 2*index+2;

	if(izq < 10 && arr[min] - arr[izq] > 0)
	min = izq;
	if(dch < 10 && arr[min] - arr[dch] > 0)
	min = dch;

	if( min != index)
	{
		int dato = arr[index];
		arr[index] = arr[min];
		arr[min] = dato;
		heapify_minimo(arr,min);
	}

	heapify_minimo(arr,index-1);
}


void heapify_maximo(int *arr,int index)
{
	if(index < 0 || index > 10)
	return;

	int max = index;
	int izq = 2*index+1;
	int dch = 2*index+2;

	if(izq < 10 && arr[max] - arr[izq] < 0)
	max = izq;
	if(dch < 10 && arr[max] - arr[dch] < 0)
	max = dch;

	if(max != index)
	{
		int dato = arr[index];
		arr[index] = arr[max];
		arr[max] = dato;
		heapify_maximo(arr,max);
	}

	heapify_maximo(arr,index-1);
}

int* crearEntero(int dato)
{
	int *nuevo = malloc(sizeof(int));
	*nuevo = dato;
	return nuevo;
}

int compararEntero(void*a,void*b)
{
	int *aa = a,*bb=b;
	if(*aa==*bb)return 0;
	else if(*aa<*bb)return -1;
	else return 1;
}

void imprimirEntero(void *a)
{
	int *aa=a;
	printf("%d",*aa);
}