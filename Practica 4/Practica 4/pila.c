#include "pila.h"


void* peekPila(Pila pila)
{
	if(pilaVacia(pila))
		return NULL;
	else
		return pila.cima->dato;
}

//VERIFICACION
int pilaVacia(Pila pila)
{
	return pila.cima == NULL && pila.cantidad==0;
}

int pilaLlena(Pila pila)
{
	return pila.cantidad == pila.capacidad;
}

//DATOS
//Añade un nuevo nodo a la pila convirtiendolo en la cima actual
void pushDato(Pila *pila,void *dato)
{
	if(pilaLlena(*pila))
	{
		printf("\nOVERFLOW");
		return;
	}
	Nodo *nuevaCima = crearNodo(dato);
	nuevaCima->sig = pila->cima;	
	pila->cima = nuevaCima; 
	pila->cantidad++;
}


//ORDENAR
void ordenarPila( Pila *pila)
{
		
		Pila ad1 = {NULL,0,pila->capacidad,pila->imprimir,pila->liberar,pila->comparar};
		//Pila ad2 = {NULL,0,pila->capacidad,NULL,NULL,pila->comparar};
		
		Nodo *nodo;
		
		
		while(!pilaVacia(*pila))
		{
			nodo = popNodo(pila);
			
			
			while(!pilaVacia(ad1) && ad1.comparar(ad1.cima->dato, nodo->dato))
			{
						Nodo *aux = popNodo(&ad1);
						pushNodo(pila,aux);
			}
				
					pushNodo(&ad1,nodo);
					
			imprimirPila(ad1);
			printf("\n");
				
		}

	*pila = ad1;

}
		



// Extrae el dato que tiene la cima actual
// Elimina la cima actual y la cambia por el siguiente nodo al que apunta la cima
// Devuelve el numero extraido por la antigua cima
/*Ejemplo:
[3]PILA:
 4
 5
 1
 
[2]PILA:
 5
 1
 
El dato extraido de la lista fue 4
*/

void* popDato(Pila *pila)
{
	void *dato = NULL;
	if(pilaVacia(*pila))
	{
		printf("\nUNDERFLOW");
		return dato;	
	}
	Nodo *cimaVieja = pila->cima;
	pila->cima = pila->cima->sig;	
	dato = cimaVieja->dato;
	free(cimaVieja);
	pila->cantidad--;	
	return dato;
}


//NODOS

//Añade nodos a la pila este convierte el nodo añadido en la nueva cima
void pushNodo(Pila *pila,Nodo *nodo)
{
	if(pilaLlena(*pila))
	{
		printf("\nOVERFLOW");
		return;
	}
	nodo->sig = pila->cima;	
	pila->cima = nodo; 
	pila->cantidad++;
}

// Extrae el nodo de la pila cima(cimaVieja o actual)
// Desenlaza el nodo del siguiente nodo al que apunta cima
// Retorna la direccion del nodo
Nodo* popNodo(Pila *pila)
{
	Nodo *cimaVieja = NULL;
	if(pilaVacia(*pila))
	{
		printf("\nUNDERFLOW");
		return cimaVieja;	
	}
	cimaVieja = pila->cima;
	pila->cima = pila->cima->sig;	
	pila->cantidad--;	
	cimaVieja->sig = NULL;
	return cimaVieja;
}

//VACIAR/ELIMINAR PILA
void vaciarPila(Pila *pila)
{
	while(!pilaVacia(*pila))
	{
		popDato(pila);
	}
}

void eliminarPila(Pila *pila)
{
	while(!pilaVacia(*pila))
	{
		void * dato = popDato(pila);
		if(pila->liberar)
			pila->liberar(dato);
	}	
}


//IMPRIMIR RESPETAR LIFO
void imprimirPila(Pila pila)
{	
	// El -1 INDICA QUE ES DE TAMAÑO INDEFINIDO
	Pila aux = {NULL,0,-1,NULL,NULL};	
	printf("\n [%d]PILA:",pila.cantidad);
	//IMPRIMIR CIMAS ORIGINAL
	//REMUEVE LOS NODOS DE LA ORIGINAL
	//LOS PASA A LA AUX
	while(!pilaVacia(pila))
	{
		printf("\n");
		pila.imprimir( pila.cima->dato);
		pushNodo( &aux , popNodo(&pila) );
	}	
	//RESTAURAR
	//REMUEVE LOS NODOS DE LA AUX
	//LOS PASA A LA ORIGINAL
	while( !pilaVacia(aux))
	{
		pushNodo( &pila , popNodo(&aux) );
	}	
}