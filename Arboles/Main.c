#include <stdio.h>
#include "arbol.h"

void imprimirEntero(void *dato);
int compEntero(void *datoA, void *datoB);
void imprimirMitades(int *arreglo, int longitud);



int main(){
	
	Arbol a = {NULL,0,imprimirEntero,compEntero,free};
	Arbol b = {NULL,0,imprimirEntero,compEntero,free};
	
	int opc = 0,dato, profundidad;
	
	do{
		
	printf("\n---- MENU ----\n");
	printf("1) Insertar en Arbol A\n");
	printf("2) Insertar en Arbol B\n");
	printf("3) Comparar Arboles\n");
	printf("4) Eliminar dato en arbol A\n");
	printf("5) Eliminar dato en arbol B\n");
	printf("6) Mostrar profundidades\n");
	printf("7) Equilibrar arboles\n");
	printf("8) Imprimir arbol A\n");
	printf("9) Imprimir arbol B\n");
	printf("\nSelecciona una opcion: ");
	scanf("%d",&opc);
	
	
	switch(opc)
	{
		case 1:
		{
			printf("\nIngrese el valor a insertar en el arbol A: ");
			scanf("%d",&dato);
			insertarArbol(&a,crearEntero(dato));
			break;
		}
		
		case 2:
		{
			printf("\nIngrese el valor a insertar en el arbol B: ");
			scanf("%d",&dato);
			insertarArbol(&b,crearEntero(dato));
			break;
		}
		
		case 3:
		compararArboles(a,b);
		break;
		
		case 4:
		if(!a.raiz)
		{
			printf("\nARBOL VACIO\n");
			break;
		}
		printf("\nIngresa el dato a eliminar del arbol A: ");
		scanf("%d",&dato);
		EliminiarDato(&a.raiz,&dato,a.comparar,a.liberar);
		break;
		
		case 5:
		if(!b.raiz)
		{
			printf("\nARBOL VACIO\n");
			break;
		}
		printf("\nIngresa el dato a eliminar del arbol B: ");
		scanf("%d",&dato);
		EliminiarDato(&b.raiz,&dato,b.comparar,b.liberar);
		break;
		
		case 6:
		profundidad = calcularProfundidad(a.raiz);
		printf("\nLa profundidad del arbol A es: %d\n",profundidad);
		profundidad = calcularProfundidad(b.raiz);
		printf("\nLa profundidad del arbol B es: %d\n",profundidad);
		break;
		
		case 7: 
		equilibrarArbol(&a); 
		equilibrarArbol(&b); 
		break;
		
		case 8:
		printf("\n");
		imprimirArbol(a);
		printf("\n");
		break;
		
		case 9:
		printf("\n");
		imprimirArbol(b);
		printf("\n");
		break;
		
	}
	
	printf("\nDeseas regresar al menu?(si=1/no=0): ");
	scanf("%d",&opc);
	
	}while(opc!=0);
	
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




/*
void imprimirMitades(int *arreglo, int longitud)
{
	if(longitud <= 0)
		return;
	
	int mitad = longitud/2;
	printf(" %d",arreglo[mitad]);
	
	//IZQUIERDA
	imprimirMitades(arreglo,mitad);
	
	//DERECHA
	imprimirMitades(arreglo,mitad+1,longitud-1-mitad);
}
*/