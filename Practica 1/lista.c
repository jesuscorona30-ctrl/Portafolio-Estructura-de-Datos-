
//LISTA.c
#include "lista.h"
#include "Alumno.h"

void agregarFinal(Lista *lista,void *dato)
{
	Nodo *nuevo = crearNodo(dato);
	//LISTA VACIA
	if( lista->inicio==NULL && lista->inicio==lista->fin)
	{
		//AGREGAR UNICO NODO
		lista->inicio = lista->fin = nuevo;		
	}
	//LISTA TIENE MINIMO UN NODO
	else
	{
		//ENLAZAR NODO AL FINAL
		lista->fin->sig = nuevo;
		//ACTUALIZAR FINAL
		lista->fin = nuevo;
	}
	lista->cantidad++;
}


Resultado buscar(Lista lista,void *dato)
{	
	Resultado resultado = {NULL,NULL,NULL};

	for (Nodo *q = NULL,*p = lista.inicio; p!= NULL ;q=p, p = p->sig)
	{
		if( lista.comparar(dato, p->dato) == 0)
		{
			//LO ENCONTRAMOS
			resultado.ante = q;
			resultado.enco = p;
			resultado.dato = p->dato;
			break;
		}
	}
	return resultado;
}



void buscarEnLista(Lista lista, void *dato)
{
		// En caso de encontrar mas de un valor con el mismo contenido
		// Imprime todas las que encuentre con dicho valor
		
		Alumno *al[lista.cantidad];
		Resultado res = {NULL,NULL,NULL};
		int encontrados = 0;
		
		for(Nodo *q=NULL, *p = lista.inicio; p!=lista.fin; q = p, p = p->sig)
		{
			if(lista.comparar(dato, p->dato) == 0)
			{
				res.ante = q;
				res.enco = p;
				res.dato = p->dato;
				al[encontrados] = p->dato;
				encontrados++;
			}
			else
			{
				continue;
			}
		}
		
		if(res.enco == NULL)
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



void imprimirResultado(Lista lista,Resultado res)
{
	
	if( res.enco )
	{
		//ENCONTRADO
		if(res.ante)
		{
			printf("\n Anterior:" );
			lista.imprimir(res.ante->dato);
		}
		printf("\n Encontrado:" );
		lista.imprimir(res.enco->dato);
	}
	else
	{
		//NO ENCONTRADO
		printf("\n No encontrado");
	}
}

void agregarEnOrden(Lista *lista,void *dato)
{
	Nodo *nuevo = crearNodo(dato);
	//LISTA VACIA?
	if ( !lista->inicio)
	{	
		lista->inicio = lista->fin = nuevo;
	}	
	//LISTA YA TIENE ALGO
	else
	{
		for (Nodo *q = NULL,*aux = lista->inicio; aux!= NULL ;q=aux, aux = aux->sig)
		{
			
			if( lista->comparar( nuevo->dato , aux->dato  ) < 0)
			{
				//REEMPLAZAR INICIO
				if(aux == lista->inicio)
				{
					nuevo->sig = aux;
					lista->inicio = nuevo;
				}
				//INSERTAR EN MEDIO DE NODOS
				else
				{
					q->sig = nuevo;
					nuevo->sig = aux;
				}
				break;
			}
			else if ( aux == lista->fin)
			{
				aux->sig = nuevo;
				lista->fin = nuevo;
				break;
			}						
		}			
	}	
	lista->cantidad++;
}

void imprimirLista(Lista lista)
{
	//SALIR DE LA FUNCION SI LA LISTA ESTA VACIA
	printf("\n\n [%d] LISTA : \n",lista.cantidad); 
	if(!lista.inicio)
	{
		printf(" VACIA\n");
		return;
	}
	//RECORRER NODOS HASTA QUE LLEGUE EL
	//ENLACE SIGUENTE DEL ULTIMO NODO, QUE ES NULO
	for ( Nodo *aux = lista.inicio; aux!= NULL ; aux = aux->sig)
	{
		//UTILIZAR LA FUNCION DE IMPRIMIR ESPECIFICADA
		//EN LA LISTA
		lista.imprimir( aux->dato );
		//LA FUNCION SE ENCARGA DE DESREFERENCIAR
		//LA DIRECCION DE TIPO VOID AL TIPO ESPECIFICO
	}	
	printf("\n");
}






void eliminarInicio(Lista *lista)
{
	Nodo *aux;
	if(lista->inicio)
	{
		aux = lista->inicio;
		lista->inicio = aux->sig;
		//ELIMINASTE EL UNICO NODO
		if( !lista->inicio) //lista->inicio == NULL
			lista->fin = NULL;
		lista->cantidad--;
		if(lista->liberar) lista->liberar(aux->dato);
		free(aux);
	}
}

void eliminarFinal(Lista *lista)
{
	if(lista->inicio)
	{	
		Resultado res = buscar(*lista,lista->fin->dato);
		lista->fin = res.ante; //PENULTIMO
		if(lista->fin)
			lista->fin->sig = NULL;
		else 
			lista->inicio = NULL;
		if(lista->liberar) lista->liberar(res.enco->dato);
		free(res.enco); //FIN
		lista->cantidad--;
	}	
}


void eliminarDato(Lista *lista,void *dato)
{
	Resultado res = buscar(*lista,dato);
	if( res.enco)
	{
		if( res.enco == lista->inicio)
			eliminarInicio(lista);
		else if (res.enco == lista->fin)
			eliminarFinal(lista);
		else
		{
			res.ante->sig = res.enco->sig;
			if(lista->liberar) lista->liberar(res.enco->dato);
			free(res.enco);
			lista->cantidad--;
		}
	}
}



void insertarInicio(Lista *lista, void *dato)
{
	// Si lista no tiene nada
	if(!lista->inicio)
	{
		lista->inicio = lista->fin = dato;
		lista->cantidad++;
	}

	// Si lista tiene algo
	else
	{
		Nodo *nuevo = crearNodo(dato);
		nuevo->sig = lista->inicio;
		lista->inicio = nuevo;
		lista->cantidad++;
		
	}
}

int insertarEn(Lista *lista, void *dato, int index)
{
	if(index < lista->cantidad && index > lista->cantidad)
	{
		return 0;
	}
	
	// Si el index es el inicio de la lista inserta el nuevo valor
	if(index == 0)
	{
		insertarInicio(lista,dato);
		return 1;
	}
	
	// Si el index es el final de la lista inserta el nuevo valor 
	else if(index == lista->cantidad-1)
	{
		Nodo *nuevo = crearNodo(dato);
		lista->fin->sig = nuevo;
		lista->fin = nuevo;
		lista->cantidad++;
		return 1;
	}
	
	// Si el index es entre los nodos de la lista inserta el nuevo valor
	else
	{
		int conteo = 1;
		
		for(Nodo *aux = lista->inicio->sig, *q = lista->inicio; aux!=NULL; q = q->sig, aux = aux->sig)
		{
			if(conteo==index)
			{
					Nodo *nuevo = crearNodo(dato);
					nuevo->sig = aux;
					q->sig = nuevo;
					lista->cantidad++;
					break;
			}
			conteo++;
		}
		
		return 1;
	}
}

int eliminarEn( Lista *lista, int index)
{
	if(index < lista->cantidad && index > lista->cantidad)
	{
		return 0;
	}
	
	// Si el index es el inicio de la lista inserta el nuevo valor
	if(index == 0)
	{
		eliminarInicio(lista);
		return 1;
	}
	
	// Si el index es el final de la lista inserta el nuevo valor 
	else if(index == lista->cantidad-1)
	{
		eliminarFinal(lista);
		return 1;
	}
	
	// Si el index es entre los nodos de la lista inserta el nuevo valor
	else
	{
		int conteo = 1;
		
		for(Nodo *aux = lista->inicio->sig, *q = lista->inicio; aux!=NULL; q = q->sig, aux = aux->sig)
		{
			if(conteo==index)
			{
					q->sig = aux->sig;
					free(aux);
					lista->cantidad--;
					break;
			}
			conteo++;
		}
		
		return 1;
	}
}


void* removerInicio(Lista *lista)
{
	if(!lista->inicio)
		return NULL;
	void *dato = lista->inicio->dato;
	lista->inicio->dato = NULL;
	eliminarInicio(lista);
	return dato;
}

void reordenar(Lista *lista, int (*comparar)(void*,void*))
{
	Lista aux = {NULL,NULL,0,lista->imprimir,comparar,lista->liberar};
	void *dato;
	while( lista->cantidad  )
	{
		dato = removerInicio(lista);
		agregarEnOrden(&aux,dato);		
	}
	*lista = aux;
	
}


int extraerMatricula(Lista *lista,void *dato)
{
	Resultado res = {NULL,NULL,NULL};
	Nodo *auxant,*aux;
	
	for(Nodo *q = NULL,*p =lista->inicio; p!=NULL ; q = p, p = p->sig)
	{
		if(lista->comparar(dato, p->dato) == 0)
		{
			res.ante = q;
			res.enco = p;
			res.dato = p->dato;
			
			auxant = res.ante;
			aux = res.enco;
			
			
			 // Si el nodo a eliminar es el PRIMERO
            if(auxant == NULL) {
                // Actualizar el inicio de la lista
               eliminarInicio(lista);
            }
			// Si el nodo a eliminar es el ÚLTIMO, actualizar el fin
            else if(aux == lista->fin){
				
				eliminarFinal(lista);
                
            }
            
            // Si el nodo a eliminar está en medio 
            else{
				
                auxant->sig = aux->sig;
				// Liberar el nodo y su dato
				lista->liberar(aux->dato);  // Liberar el dato del alumno
				free(aux);                    // Liberar el nodo
				lista->cantidad--;
            }
            
            
            break;
        }
    }
    
    return 1;  // Retorna 1 si encontró y eliminó, 0 si no
	
}





