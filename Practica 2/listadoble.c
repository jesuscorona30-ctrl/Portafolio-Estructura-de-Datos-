#include "listadoble.h"
#include "nododoble.h"
#include "Alumno.h"
#include <stdio.h>
#include <stdlib.h>

ListaD inicializarListaD(void)
{
	ListaD listaD = {NULL,NULL,0,NULL,NULL,NULL};
	return listaD;
}

void imprimirListaDFI(ListaD lista)
{
	if("\n [%d] LISTA",lista.cant);
	if(!lista.inicio)
	{
		printf("VACIA");
		return;
	}
	
	for(NodoD *aux = lista.fin; aux != NULL; aux = aux->ant)
	{
		printf("\n");
		lista.imprimir(aux->dato);
	}
}


void imprimirListaDIF(ListaD lista)
{
	if("\n [%d] LISTA",lista.cant);
	if(!lista.inicio)
	{
		printf("VACIA");
		return;
	}
	
	for(NodoD *aux = lista.inicio; aux != NULL; aux = aux->sig)
	{
		printf("\n");
		lista.imprimir(aux->dato);
	}
}


void insertarFinalD(ListaD *lista,void* dato)
{
	NodoD *nuevo = crearNodoD(dato);
	
	// LISTA VACIA
	if(!lista->inicio)
	{
		lista->inicio = lista->fin = nuevo;
	}
	//LISTA NO VACIA
	else
	{
		lista->fin->sig = nuevo;
		nuevo->ant = lista->fin;
		lista->fin = nuevo;
	}
	
	lista->cant++;
}


void insertarEnOrdenD(ListaD *lista,void * dato)
{
	NodoD *nuevo = crearNodoD(dato);
	
	//Si la lista esta vacia
	if (!lista->inicio)
	{	
		lista->inicio = lista->fin = nuevo;
	}	
	//Si la lista ya tiene algo
	else
	{
		for (NodoD *p = lista->inicio, *q = p->ant; p!= NULL ; p = p->sig, q = p->ant)
		{
			
			if( lista->comparar( nuevo->dato , p->dato  ) < 0)
			{
				//REEMPLAZAR INICIO
				if(p == lista->inicio)
				{
					p->ant = nuevo;
					nuevo->sig = p;
					lista->inicio = nuevo;
					
					
				}
				//INSERTAR EN MEDIO DE NODOS
				else
				{
					nuevo->ant = q;
					nuevo->sig = p;
					q->sig = nuevo;
					p->ant = nuevo;
					
					
				}
				
				break;
				
			}
			
			else if ( p == lista->fin)
			{
				nuevo->ant = p;
				p->sig = nuevo;
				lista->fin = nuevo;
				break;
			}						
		}			
	}	
	lista->cant++;

}


void borrarInicioD(ListaD *lista)
{
	NodoD *aux;
	
	if(!lista->inicio)
		return;
	
	aux = lista -> inicio;
	
	//UNICO NODO
	if(lista->inicio == lista->fin)
	{
			lista->inicio = lista->fin = NULL;
	}
	//MINIMO 2 NODOS
	else
	{
			lista -> inicio = aux->sig;
			lista->inicio->ant = NULL; //ROMPER ENLACE
	}
	
	if(lista->liberar)
		lista->liberar(aux->dato);
	free(aux);
	
	lista->cant--;
}

void borrarFinalD(ListaD *lista)
{
	NodoD *aux;
	
	if(lista->inicio)
	{
			//UNICO NODO
			if(lista->inicio == lista->fin)
			{
				lista->inicio = lista->fin = NULL;
			}
		
			//SI HAY MAS DE UNO
			else
			{
			aux = lista->fin;
			lista->fin = aux->ant;
			lista->fin->sig = NULL; //ROMPE EL ENLACE
			}
	
		if(lista->liberar)
		lista->liberar(aux->dato);
		
		free(aux);
	
		lista->cant--;
	
	}
	
}


void borrarListaD(ListaD *lista)
{
	/*
	COMPROBAR SI HAY DATOS
	*/
	if(lista->inicio)
	{
		while(lista->inicio)
		{
			borrarInicioD(lista);
		}
	}
	
}


void mostrarListaD(ListaD lista)
{
	//SALIR DE LA FUNCION SI LA LISTA ESTA VACIA
	printf("\n\n [%d] LISTA : \n",lista.cant); 
	if(!lista.inicio)
	{
		printf(" VACIA\n");
		return;
	}
	//RECORRER NODOS HASTA QUE LLEGUE EL
	//ENLACE SIGUENTE DEL ULTIMO NODO, QUE ES NULO
	for (NodoD *aux = lista.inicio; aux!= NULL ; aux = aux->sig)
	{
		//UTILIZAR LA FUNCION DE IMPRIMIR ESPECIFICADA
		//EN LA LISTA
		lista.imprimir( aux->dato );
		//LA FUNCION SE ENCARGA DE DESREFERENCIAR
		//LA DIRECCION DE TIPO VOID AL TIPO ESPECIFICO
	}	
	printf("\n");
}


void reordenarD(ListaD *lista,int (*comparar)(void *datoA, void*datoB) ) 
{
	ListaD aux = {NULL,NULL,0,comparar,lista->imprimir,lista->liberar};
	void *dato;
	while( lista->cant  )
	{
		dato = removerInicio(lista);
		insertarEnOrdenD(&aux,dato);		
	}
	*lista = aux;
}

void* removerInicio(ListaD *lista)
{
	if(!lista->inicio)
		return NULL;
	void *dato = lista->inicio->dato;
	lista->inicio->dato = NULL;
	borrarInicioD(lista);
	return dato;
}


void buscarEnListaD(ListaD lista, void *dato)
{
		// En caso de encontrar mas de un valor con el mismo contenido
		// Imprime todas las que encuentre con dicho valor
		
		Alumno *al[lista.cant];
		NodoD *aux = NULL;
		int encontrados = 0;
		
		for(NodoD *p = lista.inicio; p!=NULL; p = p->sig)
		{
			if(lista.comparar(dato, p->dato) == 0)
			{
				aux = p;
				al[encontrados] = aux->dato;
				encontrados++;
			}
			else
			{
				continue;
			}
		}
		
		if(aux == NULL)
		{
			printf("\nSe encontraron %d resultado(s)\n",encontrados);
			printf("\nNo se encontro ningun elemento en la lista que coicida con el criterio solicitado\n");
			
		}
		else
		{
			printf("\nSe encontraron %d resultado(s): \n",encontrados);
			
			for(int count= 0; count <= encontrados-1; count++)
			{
				printf("\n---Datos del Alumno---\n");
				printf("\nNombre del alumno: %s",al[count]->nombre);
				printf("\nMatricula: %d",al[count]->matricula);
				printf("\nSemestres: %d",al[count]->semestre);
				printf("\nPromedio general: %.2lf\n",al[count]->promedio);
			}
		}
		
		
}



int extraerMatricula(ListaD *lista,void *dato)
{
	
	NodoD *aux;
	
	for(NodoD *p =lista->inicio; p!=NULL ; p = p->sig)
	{
		if(lista->comparar(dato, p->dato) == 0)
		{
			
			aux = p;
			
			 // Si el nodo a eliminar es el PRIMERO
            if(aux == lista->inicio) {
                // Actualizar el inicio de la lista
               borrarInicioD(lista);
            }
			// Si el nodo a eliminar es el ÚLTIMO, actualizar el fin
            else if(aux == lista->fin){
				
				borrarFinalD(lista);
                
            }
            
            // Si el nodo a eliminar está en medio 
            else{
				
                aux->ant->sig =  aux->sig;
				aux->sig->ant = aux->ant;
				// Liberar el nodo y su dato
				lista->liberar(aux->dato);  // Liberar el dato del alumno
				free(aux);                    // Liberar el nodo
				lista->cant--;
            }
            
            
            break;
        }
    }
    
    return 1;  // Retorna 1 si encontró y eliminó, 0 si no
	
}



