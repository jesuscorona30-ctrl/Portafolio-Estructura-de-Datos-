#include "pila.h"
#include "string.h"

int compararOperadores(void *op1, void *op2);
int operadoresPrecedencia(char operador);



void *peekCima(Pila pila)
{
	if(pilaVacia(pila))
		return NULL;
	
	void *cima = pila.cima->dato;
	return cima;
}

//CONSULTAR LA CIMA DE LA PILA ARBOL
void *peekCimaA(PilaA pila)
{
	if(pilaVaciaA(pila))
		return NULL;
	
	void *cima = pila.cima->dato;
	return cima;
}


//VERIFICIACION
int pilaVacia(Pila pila)
{
	return pila.cima == NULL && pila.cantidad==0;
}


//VERIFICIACION PILA ARBOL VACIA
int pilaVaciaA(PilaA pila)
{
	return pila.cima == NULL && pila.cantidad==0;
}

int pilaLlena(Pila pila)
{
	return pila.cantidad == pila.capacidad;
}

//VERIFICIACION PILA ARBOL LLENA
int pilaLlenaA(PilaA pila)
{
	return pila.cantidad == pila.capacidad;
}


//DATOS
//Añade un nuevo nodo de tipo arbol a la pila convirtiendolo en la cima actual
void pushDatoA(PilaA *pila,void *dato)
{
	if(pilaLlenaA(*pila))
	{
		printf("\nOVERFLOW");
		return;
	}
	NodoA *nuevaCima = crearNodoA(dato);
	nuevaCima->sig = pila->cima;	
	pila->cima = nuevaCima; 
	pila->cantidad++;
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

//SACA DATOS DE TIPO ARBOL DE LA PILA 
void* popDatoA(PilaA *pila)
{
	void *dato = NULL;
	if(pilaVaciaA(*pila))
	{
		printf("\nUNDERFLOW");
		return dato;	
	}
	NodoA *cimaVieja = pila->cima;
	pila->cima = pila->cima->sig;	
	dato = cimaVieja->dato;
	free(cimaVieja);
	pila->cantidad--;	
	return dato;
}

//NODOS ARBOLES

//Añade nodos a la pila este convierte el nodo añadido en la nueva cima
void pushNodoA(PilaA *pila,NodoA *nodo)
{
	if(pilaLlenaA(*pila))
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
NodoA* popNodoA(PilaA *pila)
{
	NodoA *cimaVieja = NULL;
	if(pilaVaciaA(*pila))
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
	//REMOVER LOS NODOS DE LA ORIGINAL
	//PASARLOS A LA AUX
	while(!pilaVacia(pila))
	{
		printf("\n");
		pila.imprimir( pila.cima->dato);
		pushNodo( &aux , popNodo(&pila) );
	}	
	//RESTAURAR
	//REMOVER LOS NODOS DE LA AUX
	//PASARLOS A LA ORIGINAL
	while( !pilaVacia(aux))
	{
		pushNodo( &pila , popNodo(&aux) );
	}	
}


int verificarParentesis(char *cadena)
{
	Pila pila = {NULL,0,-1,NULL,NULL,NULL};
	char texto[MAX];
	strcpy(texto,cadena);
	char *dato;
	int posicion = 0;
	
	while(texto[posicion] != '\0')
	{
		
			//SI LA CADENA CONTIENE ALGUN CARACTER DE APERTURA
			if(texto[posicion]=='(' || texto[posicion]=='[' || texto[posicion]=='{')
			{
						pushDato(&pila,&texto[posicion]);
			}
			
			//SI EN LA CADENA SOLO ENCUENTRA CADENAS DE CIERRE PERO NO DE APERTURA
			if(texto[posicion] == ')' || texto[posicion] == ']' || texto[posicion] == '}')
			{
					// SI LA PILA ESTA VACIA HASTA ESTE PUNTO
					if(pilaVacia(pila)) return 0;// RETORNA 0
					
					//SACA EL DATO DE LA CIMA DE LA PILA 
					dato = popDato(&pila);
					
					//SI LA POSICION ACTUAL DE LA CADENA ENCUENTRA UN CARACTER DE CIERRE
					//PERO SI EL DATO EXTRAIDO DE LA PILA NO COINCIDE CON EL CARACTER DE APERTURA SEÑALADO
					//RETORNA 0
					if(texto[posicion] == ')' && *dato != '(') return 0;
					if(texto[posicion] == ']' && *dato != '[') return 0;
					if(texto[posicion] == '}' && *dato != '{') return 0;
			}
			
			//SI ES UNA LETRA O CARACTER DISTINTO AL INDICADO
			if(texto[posicion]!= ')' || texto[posicion] != ']' || texto[posicion] != ']')
			{
				posicion++;  // Avanza a la siguiente posición
				continue;
			}
			
		posicion++;  // Avanza a la siguiente posición
		
	}
	
	if(!pilaVacia(pila)) return 0;
	
	return 1;
	
}




void infixtoPostfix(char *cadena, char *postfix)
{
	Pila pila = {NULL,0,-1,NULL,free,compararOperadores};
	char *operador_cima;
	int j = 0;

	
	for(int i = 0; cadena[i] != '\0'; i++)
	{
		//SI EL CARACTER ACTUAL ES IGUAL A UN CARACTER DE APERTURA
		//LO AÑADIMOS A LA PILA
		if(cadena[i] == '(')
		{
			if(pilaVacia(pila))
			pushDato(&pila,&cadena[i]);
			else
			pushDato(&pila,&cadena[i]);
		}

		//SI EL CARACTER ACTUAL ES IGUAL A UN CARACTER DE CIERRE
		else if(cadena[i] == ')')
		{
				operador_cima = peekCima(pila);
				
				// MIENTRAS LA PILA NO ESTE VACIA Y EL OPERADOR DE LA CIMA SEA DISTINTO DEL CARACTER
				// DE APERTURA
				while(!pilaVacia(pila) && *operador_cima != '(')
				{
					operador_cima = popDato(&pila); // QUITAMOS EL OPERADOR DE LA PILA
					postfix[j] = *operador_cima; // LO AÑADIMOS A LA CADENA POSTFIX
					j++;
					operador_cima = peekCima(pila); //CONSULTAMOS NUEVAMENTE LA CIMA DE LA PILA
				}

				// SI LA PILA NO ESTA VACIA Y EL OPERADOR DE LA CIMA ES IGUAL AL CARACTER DE APERTURA
				if(!pilaVacia(pila) && *operador_cima == '(')
					popDato(&pila); // LO QUITAMOS DE LA PILA
		}
		
		
		else if(cadena[i] == '+' || cadena[i] == '-' || cadena[i] == '*' || cadena[i] == '/' || cadena[i] == '^')
		{
			if(pilaVacia(pila))
			pushDato(&pila,&cadena[i]);
				
	
			else
			{
				operador_cima = peekCima(pila);
				
				//SI EL OPERADOR ACTUAL ES MAYOR QUE EL DE LA PILA
				if(pila.comparar(&cadena[i],operador_cima) > 0)
				pushDato(&pila,&cadena[i]);
			
				//SI EL OPERADOR ACTUAL ES MENOR O IGUAL
				else
				{
					// MIENTRAS EL OPERADOR ACTUAL SEA MENOR O IGUAL QUE LA CIMA DE LA PILA
					// Y LA PILA NO ESTE VACIA
						while(!pilaVacia(pila) && pila.comparar(&cadena[i],operador_cima) <= 0)
						{
							operador_cima = popDato(&pila);
							postfix[j] = *operador_cima;
							operador_cima = peekCima(pila);
							j++;
						}
						
						pushDato(&pila,&cadena[i]);
				}
				
			}
		
		}
		
		else
		{	
			postfix[j] = cadena[i];
			j++;
		}
		
	}
	
	// VACIAMOS EL RESTO DEL CONTENIDO DE LA PILA
	// AÑADIMOS LOS OPERADORES FALTANTES A LA CADENA POSTFIX
	while(!pilaVacia(pila))
	{
		operador_cima = popDato(&pila);
		postfix[j] = *operador_cima;
		j++;
	}
	
	postfix[j] = '\0';
	
		
}


int compararOperadores(void *op1, void *op2)
{
	char *operador_actual = op1;
	char *operador_cima = op2;
	
	int op_actual = operadoresPrecedencia(*operador_actual);
	int op_cima = operadoresPrecedencia(*operador_cima);
	
	return op_actual - op_cima;
}


int operadoresPrecedencia(char operador)
{
	switch(operador)
	{
		case '^':
		return 3;
		
		case '/': case '*':
		return 2;
		
		case '+': case '-':
		return 1;
		
		case '(':
		return 0;
		
		default:
		return -1;
	}
}