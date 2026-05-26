#include <stdio.h>
#include "pila.h"
#include "captura.h"
#include <string.h>




int palindromo(char *cadena);
int verificarParentesis(char *cadena);

int main(void)
{
	
	char *cadena = NULL;
	
	inputCadenaDinamica("\n Captura cadena: ",&cadena,MAX);
	printf(" Es palindromo: %s", palindromo(cadena) ? "SI" : "NO");

	inputCadenaDinamica("\n\n Captura expresion: ",&cadena,MAX);
	printf(" Parentesis correctos : %s", verificarParentesis(cadena) ? "SI" : "NO");
	
	free(cadena);
	printf("\n\n FIN DE PROGRAMA");
	return 0;
}

