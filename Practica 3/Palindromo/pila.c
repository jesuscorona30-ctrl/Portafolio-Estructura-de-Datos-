#include "pila.h"


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



int palindromo(char *cadena)
{
	Pila pila = {NULL,0,-1,NULL,NULL,NULL};
	char original[MAX];
	char cad_resultante[MAX]; 
	int posicion = 0;
	
	
	strcpy(original,cadena);
	
	for(int i = 0; original[i] != '\0' ;i++)
	{
	
		printf("%c ",original[i]);
	}
	printf("\n");
	
	
	
	while(original[posicion] != '\0')
	{
		if(original[posicion] == ' ')
		{
			posicion++;
			continue;
		}
		
		else{
		
			if(pilaVacia(pila))
			{
				pushDato(&pila,&original[posicion]);
			}
		
			else
			{
				pushDato(&pila,&original[posicion]);
			}
		}
		
		posicion++;
		
	}
	
	//MIENTRAS PILA NO ESTE VACIA
	posicion = 0;
	while(!pilaVacia(pila))
	{
		
		char *dato = popDato(&pila);
		cad_resultante[posicion] = *dato;
		posicion++;
	}
	
	cad_resultante[posicion] = 	'\0';
	
	for(int i = 0; cad_resultante[i] != '\0' ;i++)
	{
		printf("%c ",cad_resultante[i]);
	}
	
	printf("\n");
	
	
	/*VERIFICAR SI ES O NO UN PALINDROMO
	EJEMPLO:
	ORIGINAL : Anita lava la tina = 18
	CAD_RESULTANTE : anitalavalatinA = 15
	*/
	
	posicion = 0; //RESETEAR POSICION PARA LA CADENA RESULTANTE
	
	for(int i = 0; original[i]!= '\0'; i++)
	{
		//SALTERSE LOS ESPACIOS DE LA CADENA ORIGINAL
		if(original[i] == ' ')
		{
			continue;
		}
		
		else
		{
			//SI EL CARACTER DE AMBAS CADENAS 
			if(original[i] == cad_resultante[posicion])
			{
				posicion++;
			}
			
			//SI EL CARACTER EN LA POSICION ACTUAL CONTIENE UNA LETRA MAYUSCULA EN ALGUNA DE LAS DOS CADENAS
			/*La función tolower() toma un carácter y lo convierte a minúscula. 
			Si ya es minúscula o no es una letra, lo deja igual. */
			else if(tolower(original[i]) == tolower(cad_resultante[posicion]))
			{
				posicion++;
			}
			
			// SI DETECTA QUE EN NINGUNO DE LOS DOS CASOS ANTERIORES COINCIDE ROMPE EL CICLO Y RETORNA 0
			else
			{
				return 0;
			}
			
			
		}
		
	}
	
	//AL SALIR DEL CICLO SI TODAS LAS LETRAS FUERON IGUALES RETORNA 1
	return 1;
}



int verificarParentesis(char *cadena)
{
	
	Pila pila = {NULL,0,-1,NULL,NULL,NULL};
	int posicion = 0, i = 0;
	int bandera = 0;
	char caracter_cerrar;
	char *dato;
	void *d;

	while(cadena[posicion] != '\0')
	{
		if(pilaVacia(pila))
		{
			// SI LA CADENA ES UN PARENTESIS DE APERTURA
			if(cadena[posicion] == '(')
			{
				void *dato = &cadena[posicion];
				pushDato(&pila,dato);
				bandera = 1;
				
			}
			
			//SI LA CADENA ES UN CORCHETE DE APERTURA
			else if(cadena[posicion] == '[')
			{
				void *dato = &cadena[posicion];
				pushDato(&pila,dato);
				bandera = 1;
				
			}
			
			//SI LA CADENA ES UNA LLAVE DE APERTURA
			else if(cadena[posicion] == '{')
			{
				void *dato = &cadena[posicion];
				pushDato(&pila,dato);
				bandera = 1;
				
			}
			
			//SI LA CADENA CONTIENE UNA LETRA O NUMERO ESTA CONTINUARA HASTA ENCONTRAR EL CARACTER DE APERTURA
			// SI ES UN CARACTER DE APERTURA INVERSA NO LO TOMARA EN CUENTA
			else
			{
				continue;
			}
		}
		
		//SI PILA YA TIENE ALGO
		else
		{
			if(!pilaVacia(pila))
			{
				
				dato = pila.cima->dato;
				
				if(*dato == '(')
				{
					caracter_cerrar = ')';
				}
				
				if(*dato == '[')
				{
					caracter_cerrar = ']';
				}
				
				if(*dato == '{')
				{
				caracter_cerrar = '}';
				}
				
				
				// SI ENCUNTRA UN CARACTER DE CIERRE PARA LA APERTURA ACTUAL
				// LO AÑADE A LA PILA Y LO VACIA LUEGO DE SER AÑADIDO
			
			
				if(*dato == '(' && cadena[posicion] == caracter_cerrar)
				{
					d = &cadena[posicion];
					pushDato(&pila,d);
					dato = pila.cima->dato;
				
					while(*dato == ')' || *dato == '(')
					{
							popDato(&pila);
							dato = pila.cima->dato;
					}
				}
			
				if(*dato == '[' && cadena[posicion] == caracter_cerrar)
				{
					d = &cadena[posicion];
					pushDato(&pila,d);
					dato = pila.cima->dato;
				
					while(*dato == ']' || *dato == '[')
					{
						popDato(&pila);
						dato = pila.cima->dato;
					}
				}
			
			
				if(*dato == '{' && cadena[posicion] == caracter_cerrar)
				{
					d = &cadena[posicion];
					pushDato(&pila,d);
					dato = pila.cima->dato;
					
					while(*dato == '}' || *dato == '{')
					{
						popDato(&pila);
						dato = pila.cima->dato;
					}
				}
			
			
				else if(cadena[posicion] != caracter_cerrar)
				{
					if(cadena[posicion] == '(')
					{
						d = &cadena[posicion];
						pushDato(&pila,d);
						
					}
				
					if(cadena[posicion] == '[')
					{
						d = &cadena[posicion];
						pushDato(&pila,d);
						
					}
				
					if(cadena[posicion] == '{')
					{
						d = &cadena[posicion];
						pushDato(&pila,d);
						
					}
				
					//Continua si es una letra
					else{
						continue;
					}
				}
			
			}
			
		}
		
		posicion++;
		
		
	}
	
	if(pilaVacia(pila) && bandera == 1)
	{
		return 1;
	}	
	
	
	return 0;	
	
}