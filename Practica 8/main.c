
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "heap.h"

int* crearEntero(int);
int compararEntero(void*,void*);
int compararPaginas(void*,void*);
void imprimirEntero(void*);
char *crearCadena(char[]);
void imprimirArchivo(void *dato);
void vaciarHeap(Heap *heap);

typedef struct 
{
	char *nombre_doc;
	int num_pags;

}Archivo;

void *crearNodoArchivo(void *, void*);
void elegirOpcion(int, Heap*,int*);
void metodoPrincipal(Heap *heap);
void *generarArchivoRadom();
void mostrarHeapYArbol(Heap *heap, int *bandera);
int compararCadenas(void *cadena1, void *cadena2);
void *eliminarDelHeap(Heap *heap, char *texto);

int main(void)
{
	Heap heap = crearHeap(HEAP_MIN,compararPaginas,imprimirArchivo);
	srand(time(NULL));
	
	metodoPrincipal(&heap);
	
	return 0;
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

int compararPaginas(void *a,void *b)
{
	Archivo *a1 = a, *a2 = b;
	
	if(a1->num_pags == a2->num_pags)return 0;
	else if(a1->num_pags < a2->num_pags)return -1;
	else return 1;
}

void imprimirEntero(void *a)
{
	int *aa=a;
	printf("%d",*aa);
}

void *crearNodoArchivo(void *n_doc, void *n_pags)
{
	Archivo *nuevo_archivo = calloc(1,sizeof(Archivo));
	nuevo_archivo->nombre_doc = n_doc;
	nuevo_archivo->num_pags = *(int*)n_pags;
	return nuevo_archivo;
}

char *crearCadena(char cadena[])
{
	char *nuevo = calloc(strlen(cadena)+1,sizeof(char));
	strcpy(nuevo,cadena);
	return nuevo;
}

void imprimirArchivo(void *dato)
{
	Archivo *ptr = dato;
	printf("Pags: %d,Nombre: %s",ptr->num_pags,ptr->nombre_doc);
}


void metodoPrincipal(Heap *heap)
{
	int opc;
	int bandera = 0;

	do
	{
		mostrarHeapYArbol(heap, &bandera);

		printf("\n\n---MENU---\n");
		printf("[0] Cambiar prioridad\n");
		printf("[1] Mostrar cola de impresion\n");
		printf("[2] Agregar archivo\n");
		printf("[3] Imprimir/Procesar archivo\n");
		printf("[4] Eliminar archivo\n");
		printf("[5] Eliminar todos los archivos\n");
		printf("[6] Terminar programa\n");
		printf("Seleccione una opcion: ");
		scanf("%d",&opc);
		elegirOpcion(opc,heap,&bandera);
		
		
	}while(opc!=6);
	
}

void mostrarHeapYArbol(Heap *heap, int *bandera)
{
	if(*bandera == 0)
	{	
		if(heap->cantidad)
		{
			imprimirHeap(*heap);

			printf("\nARBOL BINARIO: \n");
			heap_arbolBinario(heap);
		}

	}
	
	else if(*bandera == 2)
	{
		*bandera = 0;
		return;
	}
	
	else
	{
			

			if(heap->cantidad)
			{

				void *dato = eliminarHeap(heap);

				if(heap->cantidad == 0)
				{
					
					//SE PROCESA Y ELIMINA EL ARCHIVO DE MAYOR PRIORIDAD LA RAIZ
					printf("\n\nDato eliminado del heap: ");
					imprimirArchivo(dato);
					printf("\n");
				
				}

				else{
						imprimirHeap(*heap);

						printf("\nARBOL BINARIO: \n");
						heap_arbolBinario(heap);

						//SE PROCESA Y ELIMINA EL ARCHIVO DE MAYOR PRIORIDAD LA RAIZ
						printf("\n\nDato eliminado del heap: ");
						imprimirArchivo(dato);
						printf("\n");
					}
				
			}else
			printf("\nVACIO [%d]",heap->cantidad);

			*bandera = 0;
			
	}
}

void elegirOpcion(int opc, Heap *heap, int *bandera)
{
	switch(opc)
	{
		case 0:
			//CAMBIAR PRIORIDAD
			if(heap->tipo == HEAP_MIN)
			{
				heap->tipo = HEAP_MAX;
				heapify(heap);
			}

			else
			{
				heap->tipo = HEAP_MIN;
				heapify(heap);
			}
		break;
		
		case 1:
		{
			//IMPRIMIR COLA DE IMPRESION
			*bandera = 2;
			char *texto = (heap->tipo == HEAP_MIN) ? "\nCOLA DE IMPRESION (MINIMO)":"\nCOLA DE IMPRESION (MAXIMO)";
			printf("\n%s",texto);
			imprimirHeap(*heap);
		}
		break;
		
		case 2:
		insertarHeap(heap,generarArchivoRadom());
		break;

		case 3:
			*bandera = 1;
		break;
		
		case 4:
		{
			Archivo *dato;

			if(heap->cantidad < 0)
			{
				printf("/nERROR: NO EXISTEN ELEMENTOS DENTRO DEL HEAP[%d]",heap->cantidad);
			}
			else
			{
				imprimirHeap(*heap);
				char nombre[6];
				getchar();
				printf("\nIngrese el nombre del archivo a eliminar: ");
				scanf(" %s",nombre);
				dato = eliminarDelHeap(heap,nombre);
				printf("\n\nDato eliminado del heap: ");
				imprimirArchivo(dato);
				printf("\n");
			}

		}
		break;
		
		case 5:
		vaciarHeap(heap);
		break;

		case 6:
		printf("\n\n FIN DE PROGRAMA\n");
		break;
		
	}

}

void* generarArchivoRadom()
{
	int aleatorio = rand()%100+1;
	int tamanio = rand()%6+1;
	char letras[tamanio+1]; 

	for(int i = 0; i < tamanio; i++)
	{
		letras[i] = (rand()%26) + 'a';
	}

	letras[tamanio] = '\0';

	Archivo *archivo_random = crearNodoArchivo(crearCadena(letras),crearEntero(aleatorio));
	
	return archivo_random;
}

void vaciarHeap(Heap *heap)
{
	while(heap->cantidad)
	{
		printf("\n Cantidad:  %d",heap->cantidad);
		void *dato = eliminarHeap(heap);
		printf("\n Dato eliminado: ");
		heap->imprimir(dato);
		free(dato);
	}
}


void *eliminarDelHeap(Heap *heap, char *texto)
{
	void *enco = NULL;
	void *aux;
	int indice = 0;

	while(indice < heap->cantidad)
	{
		aux = heap->datos[indice];

		if(compararCadenas(aux,texto) == 1)
		{
			for(int i = indice; i < heap->cantidad; i++)
			{
				if(heap->datos[i+1]!=NULL)
				heap->datos[i] = heap->datos[i+1];
			}

			void **temp = NULL;
			while(!temp)
				temp = realloc(heap->datos, (heap->cantidad-1) * sizeof(void*) );
			heap->datos = temp;
			heap->cantidad--;

			//HEAPIFY
			heapify(heap);
			enco = aux;
			break;
		}
		

		indice++;
	}

	return enco;
}


int compararCadenas(void *cadena1, void *cadena2)
{
	Archivo *c1 = cadena1;
	char *c2 = cadena2;
	if(!(strcmp(c1->nombre_doc,c2))) return 1;
	else return 0;
}
