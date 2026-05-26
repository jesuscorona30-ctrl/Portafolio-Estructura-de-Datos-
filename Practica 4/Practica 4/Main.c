#include <stdio.h>
#include <stdlib.h>
#include "pila.h"
#include "Laberinto.h"




int main(void)
{
    Laberinto lab = crear_laberinto();
	Coordenada *punto;
	Coordenada *p;
	Pila checkpoint = {NULL,0,-1,imprimirCoordenada,free,NULL};
	int caminos = 0;
	
	Movimientos mov;
	
	Coordenada origen = {1,1};
	Coordenada destino = {25,24};
	
	setOrigen(lab,origen);
	setDestino(lab,destino);
	imprimirLab(lab);
	
	
	Pila pila = {NULL,0,-1,imprimirCoordenada,free,NULL};
	
	//PUSH INICIAL DEL ORIGEN
	punto = crearCoordenada(origen.x,origen.y);
	pushDato(&pila,punto);
	
		//punto = peekPila(pila); /* Devuelve una estructura de tipo coordenada en 
		//la cima actual de la pila, punto puede acceder al valor de x e y */
		
		//imprimirPila(pila); // Imprime todas las coordenas contenidas en la pila
	 
		//mov = movimientosPosibles(lab,*punto);//Devuelve los caminos posibles a recorrer 
		//en el laberinto en la posicion actual
		
		//imprimirMovimientos(mov); //Imprime los caminos por donde puedes pasar
	
	
	//CICLO
	
	
	while( !pilaVacia(pila) )
	{
		if(punto->x == destino.x && punto->y == destino.y)
		{
			break;
		}
		printf("\n\nCima actual de la pila: punto x:%d , y:%d",punto->x,punto->y); 
		mov = movimientosPosibles(lab,*punto);
		caminos = caminosEncontrados(mov,&caminos);
		printf("\nCaminos encontrados: %d",caminos);
		imprimirMovimientos(mov);
		
		//REGRESAR
		
		if(bloqueado(mov))
		{
			while(!pilaVacia(checkpoint))
			{
				
				if(compararCoordenada(pila.cima->dato,checkpoint.cima->dato) != 1)
				{
 
					punto = peekPila(pila);
					printf("\n\nPeek pila: punto x:%d , y:%d",punto->x,punto->y);
					lab[punto->x][punto->y] = '.';
					free( popDato(&pila) );
				}
				else
				{
				p = peekPila(checkpoint);
				printf("\nValor a eliminar en la cima de la pila checkpoint: x:%d, y:%d",p->x,p->y);
				free(popDato(&checkpoint));
				break;
				}
			}
			
			punto = peekPila(pila);
			printf("\nEl valor del punto se encuentra en la posicion: x:%d, y:%d",punto->x,punto->y);
			continue;
		}
		
		if(caminos == 1)	
		{
			//MOVERTE
			if(mov.up == 1)
			{
				printf("\nEntro en la opcion de ARRIBA");
				punto = peekPila(pila);
				punto = crearCoordenada(punto->x-1,punto->y);
				pushDato(&pila,punto);
				dropMigaja(lab,*punto,'o');
				printf("\nPunto x:%d, y:%d",punto->x,punto->y);
			}
		
			if(mov.down == 1)
			{
				printf("\nEntro en la opcion de ABAJO");
				punto = peekPila(pila);
				punto = crearCoordenada(punto->x+1,punto->y);
				pushDato(&pila,punto);
				dropMigaja(lab,*punto,'o');
				printf("\nPunto x:%d, y:%d",punto->x,punto->y);
			
			}
		
			if(mov.right == 1)
			{
				printf("\nEntro en la opcion de DERECHA");
				punto = peekPila(pila);
				punto = crearCoordenada(punto->x,punto->y+1);
				pushDato(&pila,punto);
				dropMigaja(lab,*punto,'o');
				printf("\nPunto x:%d, y:%d",punto->x,punto->y);
				
			}
		
			if(mov.left == 1)
			{
				printf("\nEntro en la opcion de IZQUIERDA");
				punto = peekPila(pila);
				punto = crearCoordenada(punto->x,punto->y-1);
				pushDato(&pila,punto);
				dropMigaja(lab,*punto,'o');
				printf("\nPunto x:%d, y:%d",punto->x,punto->y);
			}
			
		}
		
		else
		{
		
			 //ENCONTRO DOS O MAS CAMINOS, POSICION ACTUAL DEBE SER (1,5)
			 punto = peekPila(pila);
			 p = crearCoordenada(punto->x,punto->y);
			 pushDato(&checkpoint,p);
			 p = peekPila(checkpoint);
			 printf("\nPosicion actual del chekpoint: x:%d , y:%d",p->x,p->y);
			 
			 punto = eligirCamino(mov,punto);
			 printf("\nCamino eligido: x:%d, y:%d",punto->x,punto->y);
			 pushDato(&pila,punto);
			 dropMigaja(lab,*punto,'o');
			 
			 
		}
		
		//imprimirLab(lab);
	}
	
	

	imprimirLab(lab);
	liberarLaberinto(lab);
    printf("\n\n FIN DE PROGRAMA\n\n");
    return 0;
}


