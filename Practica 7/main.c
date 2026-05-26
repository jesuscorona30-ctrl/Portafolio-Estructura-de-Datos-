#include <stdio.h>
#include "arbol.h"
#include "pila.h"
#include "captura.h"
#include "string.h"
#include <math.h>
#include <ctype.h> //Para verificar si es una letra 

//Estructura para guardar las variables sin repetirlas
typedef struct {
    char letra;
    double valor;
} Variable;

void clonarNodos(NodoA *raizO, NodoA **raizC);
Arbol clonar (Arbol arbol);
void evaluar (Arbol arbol);
void imprimirCaracter(void *dato);
int compCaracter(void *datoA, void *datoB);
void pilaNodosA(char *postfix, Arbol *expresion);
int validarExpresion(char *expresion);
int verificarOperadores(char *expresion);
void mostrarExpresion(char *expresion);
void capturarVariablesEnorden(NodoA *raiz, Variable vars[], int *num_vars);
double evaluarPostorden(NodoA *raiz, Variable vars[], int num_vars);

int main(){
	
	int opc;
	char *cadena = NULL;
	char cadena_anterior[MAX] = "";
	char postfix[MAX];
	Arbol expresion = {NULL,0,imprimirCaracter,NULL,free};

	/*
	inputCadenaDinamica("\n\n Captura expresion: ",&cadena,MAX);
	infixtoPostfix(cadena,postfix);
	
	pilaNodosA(postfix,&expresion);
	
	printf("\n\n");
	imprimirArbol(expresion);

	*/
	do{
		
	mostrarExpresion(cadena);
	printf("\n\n");
	printf("[0] CAPTURAR EXPRESION");
	printf("\n[1] IMPRIMIR ARBOL DE EXPRESION");
	printf("\n[2] EVALUAR EXPRESION");
	printf("\n[3] TERMINAR PROGRAMA");
	inputEntero("\nSeleccione una opcion: ",&opc);
	
	switch(opc)
	{
		case 0:
		{
			
			if(cadena != NULL) {
				strcpy(cadena_anterior, cadena);
			}
			
			inputCadenaDinamica("\n\n Captura expresion: ",&cadena,MAX);
			
			if(validarExpresion(cadena))
				continue;
			else
			{
				printf(" EXPRESION INVALIDA!\n\n");
				
				free(cadena);
				
				if(cadena_anterior[0] != '\0') {
					cadena = cadenaDinamica(cadena_anterior);
				} else {
					//Si no había nada antes, simplemente lo dejamos en NULL
					cadena = NULL;
				}
				
			}
			
			break;
		}
		
		case 1:
		
		infixtoPostfix(cadena,postfix);
		pilaNodosA(postfix,&expresion);
		printf("\n\n");
		imprimirArbol(expresion);
		printf("\n");
		break;
		
		case 2:
		{
			if (expresion.raiz == NULL) {
				printf("\n Error: Primero debes capturar una expresion e imprimir el arbol para generarlo.\n");
			} 
			else 
			{
				Variable variables[100]; //Arreglo para guardar variables distintas
				int n_var = 0;
				
				printf("\n");
				capturarVariablesEnorden(expresion.raiz, variables, &n_var);
				
				printf("\n");
				double resultado = evaluarPostorden(expresion.raiz, variables, n_var);
				
				printf(" Resultado final = %.2lf\n", resultado);
			}
			break;
		}
		break;
		
		case 3:
		printf("\n\n FIN DE PROGRAMA");
		break;
		
		default:
		printf("\n\nOpcion incorrecta");
		break;
		
	}
	
	}while(opc!=3);
	
	return 0;
}

void capturarVariablesEnorden(NodoA *raiz, Variable vars[], int *num_vars)
{
    if (!raiz) return; //Si no existe raiz

    // Izquierda 
    capturarVariablesEnorden(raiz->izq, vars, num_vars);

    //Procesar el nodo actual
    char c = *(char*)(raiz->dato);
    
    //Si no es un operador, es un operando/variable
    if (c != '+' && c != '-' && c != '*' && c != '/' && c != '^') 
    {
        int existe = 0;
		
        //Verificamos si ya capturamos esta letra 
        for(int i = 0; i < *num_vars; i++) {
            if(vars[i].letra == c) {
                existe = 1;
                break;
            }
        }
        
        //Si no existe, le pedimos el valor al usuario
        if(!existe) {
            vars[*num_vars].letra = c;
            char mensaje[50];
            sprintf(mensaje, " Ingrese el valor para la variable %c: ", c);
            
            //Dentro de la funcion capturamos y guardamos el valor del caracter
            inputDouble(mensaje, &vars[*num_vars].valor);
            (*num_vars)++;
        }
    }

    //Derecha 
    capturarVariablesEnorden(raiz->dch, vars, num_vars);
}


double evaluarPostorden(NodoA *raiz, Variable vars[], int num_vars)
{
    if (!raiz) return 0;

    //Si es una hoja es un operando, buscamos su valor en nuestro arreglo de variables y lo retornamos
    if (!raiz->izq && !raiz->dch) 
    {
        char c = *(char*)(raiz->dato);
        for(int i = 0; i < num_vars; i++) {
            if(vars[i].letra == c) {
                return vars[i].valor;
            }
        }
        return 0; //Valor por defecto si por alguna razón no se encontró
    }

    //Izquierda (POSTORDEN)
    double valIzq = evaluarPostorden(raiz->izq, vars, num_vars);
    
    // Derecha (POSTORDEN)
    double valDch = evaluarPostorden(raiz->dch, vars, num_vars);

    //Evaluar el operador
    char operador = *(char*)(raiz->dato);
    switch(operador)
    {
        case '+': return valIzq + valDch;
        case '-': return valIzq - valDch;
        case '*': return valIzq * valDch;
        case '/': 
            if(valDch == 0) {
                printf("\n Error: Division por cero.\n");
                return 0;
            }
            return valIzq / valDch;
        case '^': return pow(valIzq, valDch);
    }
    
    return 0;
}

void mostrarExpresion(char *expresion)
{
	if(!expresion)
		printf("\nEXPRESION: ");
	else
	{
		int i = 0;
		printf("\nEXPRESION: ");
		while(expresion[i] != '\0')
		{
			printf("%c ",expresion[i]);
			i++;
		}
	}
}

int validarExpresion(char *expresion)
{
	if(verificarParentesis(expresion) && verificarOperadores(expresion))
	{
		return 1;
	}
	else
	return 0;
}

int verificarOperadores(char *expresion)
{
	const char operadores[] = "+-/*^";
	int i = 0;
	
	while(expresion[i] != '\0')
	{
		if(expresion[i] == '+' || expresion[i] == '-' || expresion[i] == '*' || expresion[i] == '/' || expresion[i] == '^')
		{
			if(i == 0) //Si es al comienzo de la cadena retorna 0
			return 0;
		
			
			//Si no lo es verifica si el siguiente operador no es un caracter cosecutivo
			for(int j = 0; j < 5 ; j++)
			{
				if(expresion[i+1] != operadores[j] && expresion[i+1] != '\0')
				continue;
				else
					return 0; //Retorna 0 si la expresion es invalida
			}
			
		}
		
		
		i++;
	}
	
	return 1; // Retorna 1 si la expresion es valida
}

void pilaNodosA(char *postfix, Arbol *expresion)
{
	PilaA pila = {NULL,0,-1,imprimirCaracter,free,NULL};
	int i = 0;
	
	if(pilaVaciaA(pila))
	{
		pushDatoA(&pila,&postfix[i]);
		expresion->cantidad++;
		i++;
	}
	
	while(postfix[i] != '\0' && !pilaVaciaA(pila))
	{
	
			if(postfix[i] == '+' || postfix[i] == '-' || postfix[i] == '*' || postfix[i] == '/' || postfix[i] == '^')
			{
				NodoA *operador = crearNodoA(&postfix[i]);
				operador->dch = popNodoA(&pila); 
				operador->izq = popNodoA(&pila); 
				pushNodoA(&pila,operador);
				expresion->cantidad++;
			}
			
			else
			{
				pushDatoA(&pila,&postfix[i]);
				expresion->cantidad++;
			}
			
		i++;
	}
	
	if (!pilaVaciaA(pila)) {
        expresion->raiz = popNodoA(&pila); // Asignar la cima de la pila a la raíz
    }
}

void imprimirCaracter(void *dato)
{
	char *caracter = dato;
	printf(" %c",*caracter);
}

