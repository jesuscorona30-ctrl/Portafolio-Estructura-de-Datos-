
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <HashQ.h>
#include "Libro.h"


int folding(void *);
void imprimir(void *);

char** datos(void);



int main(void)
{
	HashQTable tablahash;
	tablahash.table = calloc(1000,sizeof(void*));
	tablahash.len = 1000;
	tablahash.cant = 0;
	tablahash.min = 30;
	tablahash.max = 70;
	tablahash.fixed = (tablahash.min+tablahash.max)/2;
	tablahash.folding = folding;
	tablahash.imprimir = imprimir;
	tablahash.comparar = (fn_comparar)strcmp;
	tablahash.verbose = 0;
	char** data = datos();
	for(int i = 0 ; i < 210; i++)
	{
		fn_insertKey(&tablahash,data[i]);		
	}
	tablahash.verbose = 1;
	char *estedato = "sofa";
	
	char *res = (char*)fn_searchKey(&tablahash,estedato);
	printf("\n ENCONTRADO: %s", res);
	
	printf("\n TABLA [%d]",tablahash.len);
	for(int i = 0 ; i < tablahash.len; i++)
	{
		if(tablahash.table[i]!=NULL)
		{
			printf("\n [%d] ",i);
			tablahash.imprimir(tablahash.table[i]);
		}
	}
	
	printf("\n ELIMINADO: %s",(char*)fn_deleteKey(&tablahash,estedato));
	
	
	
	
	printf("\n REMAP");
	
	tablahash.verbose = 0;
	remap(&tablahash);
	printf("\n FINREMAP");
	
	tablahash.verbose = 1;
	res = (char*)fn_searchKey(&tablahash,estedato);
	printf("\n ENCONTRADO: %s", res);
	printf("\n TABLA REMAP [%d]",tablahash.len);
	for(int i = 0 ; i < tablahash.len; i++)
	{
		if(tablahash.table[i]!=NULL)
		{
			printf("\n [%d] ",i);
			tablahash.imprimir(tablahash.table[i]);
		}
	}
	
	
	
	Acervo acervo = obtener_libros();
	
	for(int i = 0; i < acervo.cantidad ; i++)
	{
		printf("\n");
		imprimirLibro(acervo.libros+i);
	}


	printf("\n\n FIN DE PROGRAMA\n");
	
	
	return 0;
}


int folding(void *data)
{
	char *cadena = data;
	int key = 0,sector = 1,sumatoria=0;
	for(int i = 0; cadena[i]!='\0'; i++)
	{
		//abc de
		sumatoria += cadena[i];
		if( i!=0 && (i+1)%3 == 0)
		{
			key+= sector*sumatoria;
			sumatoria = 0;
			sector++;
		}
	}	
	key+= sector*sumatoria;
	return key;
	
}

void imprimir(void *data)
{	
	char *cadena = data;
	printf("%s",cadena);
}

char** datos(void)
{
	static char *cadenas[] = {
	"alberto","goku","pepe","luna","sol","mar","rio","cielo","nube","viento",
	"fuego","tierra","roca","arena","bosque","hoja","flor","raiz","tronco","rama",
	"perro","gato","lobo","zorro","oso","tigre","leon","raton","conejo","ciervo",
	"pajaro","aguila","halcon","cuervo","paloma","pez","tiburon","delfin","ballena","pulpo",
	"rojo","azul","verde","amarillo","negro","blanco","gris","rosa","morado","naranja",
	"uno","dos","tres","cuatro","cinco","seis","siete","ocho","nueve","diez",
	"enero","febrero","marzo","abril","mayo","junio","julio","agosto","septiembre","octubre",
	"noviembre","diciembre","lunes","martes","miercoles","jueves","viernes","sabado","domingo","hora",
	"minuto","segundo","tiempo","espacio","energia","luz","sombra","eco","sonido","silencio",
	"camino","ruta","sendero","via","puente","puerta","ventana","techo","pared","suelo",
	"mesa","silla","cama","sofa","puerta","llave","candado","caja","bolsa","mochila",
	"lapiz","pluma","cuaderno","libro","hoja","papel","tinta","color","regla","borrador",
	"codigo","programa","dato","variable","funcion","bucle","arreglo","puntero","memoria","proceso",
	"nodo","lista","arbol","grafo","pila","cola","byte","bit","kernel","sistema",
	"usuario","clave","red","servidor","cliente","puerto","ip","socket","paquete","protocolo",
	"html","css","java","python","csharp","ruby","swift","kotlin","go","rust",
	"linux","windows","macos","android","ios","ubuntu","debian","fedora","arch","mint",
	"intel","amd","nvidia","cpu","gpu","ram","ssd","hdd","placa","fuente",
	"monitor","teclado","raton","pantalla","audio","video","imagen","foto","pixel","vector",
	"algoritmo","logica","calculo","numero","formula","ecuacion","teoria","modelo","simulacion","analisis",
	"salud","mente","cuerpo","vida","amor","odio","paz","guerra","fuerza","valor"
	};
	return cadenas;
}