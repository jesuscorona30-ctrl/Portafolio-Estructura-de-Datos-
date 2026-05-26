#include "arbol.h"

int *crearEntero(int dato)
{
	int *nuevo_dato = malloc(sizeof(int));
	*nuevo_dato = dato;
	return nuevo_dato;
	
}


Resultado buscarNodoEnArbol(Arbol arbol,void *dato)
{
	Resultado result = {NULL,NULL,NULL,DERECHA};
	NodoA *raiz = arbol.raiz;	
	while(raiz)
	{
		if(arbol.comparar(raiz->dato,dato) == 0)
		{
			result.nodo = raiz;
			result.dato = raiz->dato;	
			break;
		}
		else
		{ 
			result.padre = raiz;
			if(raiz->izq && arbol.comparar(raiz->dato,dato) > 0 )
			{
				result.rama = IZQUIERDA;
				raiz = raiz->izq;		
			}				
			else
			{
				result.rama = DERECHA;
				raiz = raiz->dch;
			}
		}
	}
	return result;
}	
	

void* buscarEnArbol(Arbol arbol,void *dato)
{
	void *result = NULL;
	NodoA *raiz = arbol.raiz;
	
	while(raiz)
	{
		if(arbol.comparar(raiz->dato,dato) == 0)
		{
			result = raiz->dato;
			break;
		}
		else if(arbol.comparar(raiz->dato,dato) > 0 )
			raiz = raiz->izq;
		else
			raiz = raiz->dch;
	}
	return result;
}	


void invertirRamas(NodoA *raiz)
{
	if(!raiz)
		return;
	NodoA *aux = raiz->izq;
	raiz->izq = raiz->dch;
	raiz->dch = aux;
	invertirRamas(raiz->izq);
	invertirRamas(raiz->dch);
}

void invertirArbol(Arbol *arbol)
{
	invertirRamas(arbol->raiz);
}


void insertarArbolOrdenado(NodoA *raiz,void *dato,int (*comparar)(void*,void*))
{
	if(comparar(dato,raiz->dato)<=0)
	{
		//IZQUIERDA
		if(!raiz->izq)			
			raiz->izq = crearNodoA(dato);
		else if(!raiz->dch && comparar(dato,raiz->dato)==0)			
			raiz->dch = crearNodoA(dato);
		else			
			insertarArbolOrdenado(raiz->izq,dato,comparar);
	}
	else
	{
		//DERECHA
		if(raiz->dch)
			insertarArbolOrdenado(raiz->dch,dato,comparar);
		else
			raiz->dch = crearNodoA(dato);
	}
}



void insertarArbol(Arbol *arbol,void *dato)
{
	if(!arbol->raiz)
		arbol->raiz = crearNodoA(dato);
	else 
		insertarArbolOrdenado(arbol->raiz,dato,arbol->comparar);
	arbol->cantidad++;
}



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

void imprimirArbol(Arbol arbol)
{
	imprimir_arbol(arbol.raiz,0,arbol.imprimir);
}

void preorden(NodoA *raiz,void (*imprimir)(void*))
{
	if(!raiz)
		return;
	printf(" ");
	imprimir(raiz->dato);
	preorden(raiz->izq,imprimir);
	preorden(raiz->dch,imprimir);
}

void orden(NodoA *raiz,void (*imprimir)(void*))
{
	if(!raiz)
		return;
	orden(raiz->izq,imprimir);
	printf(" ");
	imprimir(raiz->dato);
	orden(raiz->dch,imprimir);	
}

void inverso(NodoA *raiz,void (*imprimir)(void*))
{
	if(!raiz)
		return;
	inverso(raiz->dch,imprimir);	
	printf(" ");
	imprimir(raiz->dato);
	inverso(raiz->izq,imprimir);
}

void postorden(NodoA *raiz,void (*imprimir)(void*))
{
	if(!raiz)
		return;
	postorden(raiz->izq,imprimir);
	postorden(raiz->dch,imprimir);
	printf(" ");
	imprimir(raiz->dato);	
}


void imprimirOrden(Arbol arbol,int opcion)
{
	switch(opcion)
	{
		case PREORDEN: 
			preorden(arbol.raiz,arbol.imprimir);
			break;
		case ORDEN: 
			orden(arbol.raiz,arbol.imprimir);
			break;
		case INVERSO: 
			inverso(arbol.raiz,arbol.imprimir);
			break;
		case POSTORDEN: 
			postorden(arbol.raiz,arbol.imprimir);
			break;
	}
}


void eliminar_NodosA(NodoA *raiz,void (*liberar)(void*))
{
	if(!raiz)
		return;
	eliminar_NodosA(raiz->izq,liberar);
	eliminar_NodosA(raiz->dch,liberar);
	//LIBERAR
	if(liberar)
		liberar(raiz->dato);
	free(raiz);
}


void eliminarArbol(Arbol *arbol)
{
	eliminar_NodosA( arbol->raiz, arbol->liberar);
	arbol->raiz = NULL;
	arbol->cantidad = 0;
}

void copiarValores(NodoA *raiz, int *arr, int *i)
{
	if(!raiz)
		return;
	
	copiarValores(raiz->izq,arr,i);
	arr[*i] = *(int*)(raiz->dato);
	(*i)++;
	copiarValores(raiz->dch,arr,i);
}

int valoresIdenticos(int *arr1, int *arr2, int longitud1, int longitud2)
{
	int posicion = 0, encontrados = 0;
	
	for(int i = 0; i < longitud2; i++)
	{
		if(arr1[posicion] == arr2[i])
		{
			i = -1;
			posicion++;
			encontrados++;
			
			if(encontrados == longitud1)
			return 1;
			
		}
		else
		continue;
	}
	
	return 0;
}

int compararEstructuras(NodoA *raizA, NodoA *raizB, int *equals)
{
	
	if(raizA && raizB && *equals) //SI EXISTE EN AMBAS RAICES
	{
		compararEstructuras(raizA->izq,raizB->izq,equals);
		compararEstructuras(raizA->dch,raizB->dch,equals);
	}
	
	else if( !raizA && !raizB && *equals)
		return *equals;
	
	else
	{
		*equals = 0;
		return *equals;
	}
	
	return *equals;
	
}



void compararArboles(Arbol a, Arbol b)
{
	int equals = 1;
	
	if(!a.raiz && !b.raiz)
	printf("\nArboles vacios!!\n");

	else 
	{
		int datosA[a.cantidad];
		int datosB[b.cantidad];
		int i = 0;
		copiarValores(a.raiz,datosA,&i);
		int j = 0;
		copiarValores(b.raiz,datosB,&j);
	
		printf("\nARREGLO DE DATOS EN A: ");
		for(int c = 0; c < a.cantidad; c++)
		{
			printf("%d ",datosA[c]);
		}
	
		printf("\nARREGLO DE DATOS EN B: ");
		for(int c = 0; c < b.cantidad; c++)
		{
			printf("%d ",datosB[c]);
		}
	
		if(valoresIdenticos(datosA,datosB,a.cantidad,b.cantidad) == 1 && valoresIdenticos(datosB,datosA,b.cantidad,a.cantidad) == 1)
		printf("\n\nLos arboles son identicos en datos!\n");
		else
		printf("\n\nLos arboles no son identicos en valores\n");
	
		if(compararEstructuras(a.raiz,b.raiz,&equals))
			printf("\nLos arboles son identicos en estructuras!\n");
		else
			printf("\nLos arboles no son identicos en estructuras\n");
	}
}

void extraerDatos(NodoA *raiz, void **datos, int *i)
{
	if(!raiz) return;
	
	extraerDatos(raiz->izq,datos,i);
	//imprimir(raiz->dato);
	datos[*i] = raiz->dato;
	(*i)++;
	extraerDatos(raiz->dch,datos,i);
}



void EliminiarDato(NodoA **raiz, void *dato, int (*comparar)(void*, void*), void (*liberar)(void*))
{
	
    // Usamos un puntero auxiliar para recorrer el árbol 
    NodoA **actual = raiz;
    
    while(*actual)
    {
        // Si encontramos el dato
        if(comparar((*actual)->dato, dato) == 0)
        {
            NodoA *eliminar = *actual; // Nodo a eliminar
            
            // Si tiene hijo izquierdo
            if(eliminar->izq)
            {
                // El nuevo padre de este nodo será el hijo izquierdo
                *actual = eliminar->izq; 
                

                // Preguntamos si el nodo a eliminar cuenta con hijo derecho
                if(eliminar->dch)
                {
                    NodoA *temp = eliminar->izq;
                    while(temp->dch != NULL) // Viajamos hasta el extremo derecho
                    {
                        temp = temp->dch;
                    }
                    temp->dch = eliminar->dch; // Conectamos 
                }
            }
            // Si solo tiene hijo derecho y no cuenta con hijo izquierdo
            else if(eliminar->dch)
            {
                *actual = eliminar->dch;
            }
            // Si no tiene hijos es una hoja
            else
            {
                *actual = NULL;
            }
            
            // Liberamos el  nodo a eliminar
            liberar(eliminar->dato);
            free(eliminar);
            break;
        }
        // Si no es el dato, decidimos si viajar a la izquierda o derecha
        else if(comparar((*actual)->dato, dato) > 0)
        {
            actual = &((*actual)->izq); 
        }
        else
        {
            actual = &((*actual)->dch);
        }
    }
}

int calcularProfundidad(NodoA *raiz)
{
	//Si llegamos a un nodo vacío, la profundidad es 0
    if (raiz == NULL) 
    {
        return 0;
    }

    // Calculamos la profundidad de ambas ramas
    int profundidadIzq = calcularProfundidad(raiz->izq);
    int profundidadDch = calcularProfundidad(raiz->dch);

    // Tomamos la rama más profunda y le sumamos 1 
    if (profundidadIzq > profundidadDch) 
    {
        return profundidadIzq + 1;
    } 
    else 
    {
        return profundidadDch + 1;
    }

}


// lLena el arreglo en orden
// Usamos void **arreglo porque cada elemento es un void *dato
void extraerDatosEnOrden(NodoA *raiz, void **arreglo, int *indice)
{
    if (!raiz) return;
    extraerDatosEnOrden(raiz->izq, arreglo, indice);
    
    // Guardamos el puntero 
    arreglo[*indice] = raiz->dato; 
    (*indice)++;
    
    extraerDatosEnOrden(raiz->dch, arreglo, indice);
}

// Reconstruye el árbol equilibrado
NodoA* reconstruirArbolEquilibrado(void **arreglo, int inicio, int fin)
{
    // Devuelve NULL si el segmento es inválido
    if (inicio > fin) return NULL;

    // Encontramos el índice central
    int medio = inicio + (fin - inicio) / 2;

    // Usamos la función crearNodoArbol pasando el dato 
    NodoA *nuevo = crearNodoA(arreglo[medio]); 

    // Aplicamos recursividad para el subárbol izquierdo 
    nuevo->izq = reconstruirArbolEquilibrado(arreglo, inicio, medio - 1);
    
    // Aplicamos recursividad para el subárbol derecho 
    nuevo->dch = reconstruirArbolEquilibrado(arreglo, medio + 1, fin);

    return nuevo;
}

// Vacia los nodos
void vaciarEstructuraNodos(NodoA *raiz)
{
    if (!raiz) return;
    vaciarEstructuraNodos(raiz->izq);
    vaciarEstructuraNodos(raiz->dch);
   
    free(raiz); 
}


void equilibrarArbol(Arbol *arbol)
{
    if (!arbol->raiz) 
	{
		printf("\n\nARBOL VACIO!");
		return;
	}
	
	int b = calcularProfundidad(arbol->raiz->izq) - calcularProfundidad(arbol->raiz->dch);
	
	//Caso equilibrado
	if(b >= -1 && b <= 1){
		printf("\n\nEl arbol esta equilibrado: %d\n",b);
		return;
	}
	printf("\n\nEl arbol no esta equlibrado: %d\n",b);

	//Crea un arreglo de punteros
	int cantidad = arbol->cantidad;
    void **datosOrdenados = (void **)malloc(cantidad * sizeof(void *));
    
    // Llena el arreglo secuencialmente 
    int indice = 0;
    extraerDatosEnOrden(arbol->raiz, datosOrdenados, &indice);

    // Vaciamos los nodos de la estructura
    vaciarEstructuraNodos(arbol->raiz);
    arbol->raiz = NULL; 

   //Reconstruye el arbol equilibrado
    arbol->raiz = reconstruirArbolEquilibrado(datosOrdenados, 0, cantidad - 1);
	
	printf("\nArreglo capturado : ");
	for(int i = 0; i < cantidad; i++)
	{
		printf(" %d",*(int*)datosOrdenados[i]);
	}
	printf("\n\n");
	
	printf("\nArbol Equilibrado: \n\n");
	imprimirArbol(*arbol);
    // Limpia el arreglo temporal
    free(datosOrdenados);
}