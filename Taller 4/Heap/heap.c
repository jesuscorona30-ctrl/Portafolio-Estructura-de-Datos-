#include "heap.h"


void imprimir_arbol(NodoA* nodo, int nivel,void (*imprimir)(void*))
{
    int i;
    if (nodo != NULL)
        {
        printf(" ");
		imprimir(nodo->dato);
        if(nodo->dch)
        {
            printf("\n");
            for (i = 0; i < nivel+1; i++)
            {
                if(i==nivel)
                    printf(" |____R ");
                else
                    printf(" |      ");
            }
            imprimir_arbol(nodo->dch, nivel + 1,imprimir);
        }
        if(nodo->izq)
        {
            printf("\n");
            for (i = 0; i < nivel+1; i++)
            {
                printf(" |      ");
                //printf(" |      ");
            }
            printf("\n");
            for (i = 0; i < nivel+1; i++)
            {
                if(i==nivel)
                    printf(" |____L ");
                else
                    printf(" |      ");
            }
            imprimir_arbol(nodo->izq, nivel + 1,imprimir);
        }
    }
}


void heap_arbolBinario(Heap *heap)
{
	if(heap->cantidad == 0) return;
	
	NodoA **nodos_arbol = calloc(heap->cantidad,sizeof(NodoA*));
	
	for(int i = 0; i < heap->cantidad; i++)
	{
		nodos_arbol[i] = crearNodoA(heap->datos[i]);
	}
	
	for(int j = 0; j < heap->cantidad; j++)
	{
		
		int hijoIzq = 2*j+1;
		int hijoDch = 2*j+2;
		
		if(hijoIzq < heap->cantidad)
			(nodos_arbol[j])->izq = nodos_arbol[hijoIzq];
		
		if(hijoDch < heap->cantidad)
			(nodos_arbol[j])->dch = nodos_arbol[hijoDch];
	}
	
	heap->raiz = nodos_arbol[0];
	
	free(nodos_arbol);
	
	//IMPRESION DEL ARBOL
	imprimir_arbol(heap->raiz,0,heap->imprimir);
}


Heap crearHeap(unsigned char tipo,fn_comparar comparar,fn_imprimir imprimir)
{
	Heap heap = {tipo,0,NULL,NULL,comparar,imprimir};
	return heap;
}

void insertarHeap( Heap *heap,void *dato)
{
	void **aux = NULL;
	if(!heap->cantidad)
		heap->datos = calloc(1,sizeof(void*));
	else
	{
		while(!aux)
			aux = realloc(heap->datos, (heap->cantidad+1) * sizeof(void*) );
		heap->datos = aux;
	}	
	heap->datos[heap->cantidad++] = dato;
	//HEAPIFY
	heapify(heap);
}


void* eliminarHeap(Heap *heap)
{
	void *dato = NULL;
	if(!heap->cantidad)
		return dato;
	dato = heap->datos[0];
	if(heap->cantidad == 1)		
	{
		free(heap->datos);
		heap->datos = NULL;
		heap->cantidad--;
		return dato;
	}
	heap->datos[0] = heap->datos[heap->cantidad-1];
	void **aux = NULL;
	while(!aux)
		aux = realloc(heap->datos, (heap->cantidad-1) * sizeof(void*) );
	heap->datos = aux;
	heap->cantidad--;
	//HEAPIFY
	heapify(heap);
	return dato;	
}

void imprimirHeap( Heap heap)
{
	printf("\n HEAP: \n");
	if(heap.cantidad)
	{
		for( int i = 0; i < heap.cantidad; i++)
		{
			printf(" [%d] ",i);
			heap.imprimir( heap.datos[i] );
			printf("\n");
		}
		
	}
	else		
		printf("VACIO");		
}




void heapify_min( Heap *heap,int padre)
{
	if( padre < 0 || padre > (heap->cantidad/2-1) )
		return;
	int min = padre;
	int izq = 2*padre+1;
	int dch = 2*padre+2;
	switch(heap->tipo)
	{
		case HEAP_MIN:			
			if( heap->comparar( heap->datos[min] , heap->datos[izq] ) > 0 )
				min = izq;
			if( dch < heap->cantidad && heap->comparar( heap->datos[min] , heap->datos[dch] ) > 0 )
				min = dch;
			break;			
		case HEAP_MAX:			
			if( heap->comparar( heap->datos[izq] , heap->datos[min] ) > 0 )
				min = izq;
			if( dch < heap->cantidad && heap->comparar( heap->datos[dch] , heap->datos[min] ) > 0 )
				min = dch;
			break;
	}
	if( min!=padre)
	{
		void *dato = heap->datos[padre];
		heap->datos[padre] = heap->datos[min];
		heap->datos[min] = dato;
		heapify_min(heap,min);
	}
	heapify_min(heap,padre-1);
	
	
}


void heapify(Heap *heap)
{
	int indice = heap->cantidad/2-1;
	heapify_min(heap,indice);

}