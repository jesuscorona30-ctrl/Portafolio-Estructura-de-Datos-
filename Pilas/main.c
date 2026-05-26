
#include <stdio.h>
#include "nodo.h"
#include "pila.h"

void imprimirEntero(void *dato);
int compararDatos(void *dato1,void *dato2);

int main(){
	
	Pila pila = {NULL,0,-1,imprimirEntero,free,compararDatos};
	
	int arreglo[7] = {8,5,6,10,2,3,9};
	
	for(int i=0; i<7; i++)
	{
		pushDato(&pila,&arreglo[i]);
	}
	
	imprimirPila(pila);
	
	ordenarPila(&pila);
	imprimirPila(pila);
	
	return 0;
}

void imprimirEntero(void *dato)
{
	int *datoA = dato;
	printf(" %d",*datoA);
}

int compararDatos(void *dato1,void *dato2)
{
	int *datoA = dato1;
	int *datoB = dato2;
	
	return *datoA > *datoB;
	
}

