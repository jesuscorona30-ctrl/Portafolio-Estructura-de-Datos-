#include <stdio.h>
#include "arbol.h"

void imprimirEntero(void *dato);
int compEntero(void *datoA, void *datoB);




int main(){
	
	Arbol a = {NULL,0,imprimirEntero,compEntero,free};
	Resultado result = {NULL,NULL,NULL,DERECHA};
	
	insertarArbol(&a,crearEntero(10));
	insertarArbol(&a,crearEntero(17));
	insertarArbol(&a,crearEntero(5));
	insertarArbol(&a,crearEntero(3));
	insertarArbol(&a,crearEntero(7));
	insertarArbol(&a,crearEntero(2));
	insertarArbol(&a,crearEntero(4));
	insertarArbol(&a,crearEntero(6));
	insertarArbol(&a,crearEntero(8));
	insertarArbol(&a,crearEntero(15));
	insertarArbol(&a,crearEntero(20));
	insertarArbol(&a,crearEntero(14));
	insertarArbol(&a,crearEntero(16));
	insertarArbol(&a,crearEntero(19));
	insertarArbol(&a,crearEntero(22));

	
	printf("\nIMPRESION ORDENADA\n");
	imprimirArbol(a);
	result = buscarNodoEnArbol(a,crearEntero(22));
	if(result.dato == NULL)
	{
		printf("\n\nDATO NO ENCONTRADO");
	}
	else
	{
		
		printf("\nDATO ENCONTRADO:");
		imprimirEntero(result.dato);
		printf("\n");
	}
	
	printf("\n");
	printf("\nIMPRESION INVERSA\n");
	printf("\n\n");
	invertirArbol(&a);
	
	imprimirArbol(a);
	

}


void imprimirEntero(void *dato)
{
	int *datoE = dato;
	printf(" %d", *datoE);
}

int compEntero(void *datoA, void *datoB)
{
	int *a = datoA, *b = datoB;
	return *a-*b;
}
