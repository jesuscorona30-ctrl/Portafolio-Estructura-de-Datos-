#include "Laberinto.h"


Movimientos movimientosPosibles(Laberinto lab,Coordenada punto)
{
	Movimientos movimientos = {0,0,0,0};
	
	
	//ARRIBA
	if( lab[punto.x-1][punto.y] == '*' || lab[punto.x-1][punto.y] == 'B')
		movimientos.up = 1;
	//ABAJO
	if( lab[punto.x+1][punto.y] == '*' ||  lab[punto.x+1][punto.y] == 'B')
		movimientos.down = 1;
	//DERECHA
	if( lab[punto.x][punto.y+1] == '*' || lab[punto.x][punto.y+1] == 'B')
		movimientos.right = 1;
	//IZQUIERDA
	if( lab[punto.x][punto.y-1] == '*' || lab[punto.x][punto.y-1] == 'B')
		movimientos.left = 1;
	
	return movimientos;	
}


void imprimirMovimientos(Movimientos movimientos)
{	
	printf("\n");
	//ARRIBA
	if( movimientos.up == 1)
		printf(" ARRIBA");
	//ABAJO
	if( movimientos.down == 1)
		printf(" ABAJO");
	//DERECHA
	if( movimientos.right == 1)
		printf(" DERECHA");
	//IZQUIERDA
	if( movimientos.left == 1)
		printf(" IZQUIERDA");
	
}

int caminosEncontrados(Movimientos mov, int *caminos)
{
	
	*caminos = 0;
	
	if(mov.up == 1)
	{
		(*caminos)++;
	}
	
	if(mov.down == 1)
	{
		(*caminos)++;
	}
	
	if(mov.right == 1)
	{
		(*caminos)++;
	}
	
	if(mov.left == 1)
	{
		(*caminos)++;
	}
	
	return *caminos;
	
}


int bloqueado(Movimientos mov)
{
	return mov.up == 0 && mov.up == mov.down && mov.up==mov.left && mov.up==mov.right;
}


Coordenada* eligirCamino(Movimientos mov,Coordenada *punto)
{
	srand(time(NULL));
	
	if(mov.up == 1 && mov.down == 1)
	{
		
		int camino = rand()%2+1;
		
		// CAMINO ARRIBA
		if(camino == 1)
			punto = crearCoordenada(punto->x-1,punto->y);
		
		// CAMINO ABAJO
		else
			punto = crearCoordenada(punto->x+1,punto->y);
			
	}
	
	else if(mov.right == 1 && mov.left == 1)
	{
		int camino = rand()%2+1;
		
		// ELIGIO CAMINO DERECHA
		if(camino == 1)
			punto = crearCoordenada(punto->x,punto->y-1);
	
		// ELIGIO CAMINO IZQUIERDA
		else
			punto = crearCoordenada(punto->x,punto->y+1);
			
	}
	
	
	else if(mov.up == 1 && mov.right == 1)
	{
		int camino = rand()%2+1;
		//CAMINO ARRIBA
		if(camino == 1)
		punto = crearCoordenada(punto->x-1,punto->y);
		else
		punto = crearCoordenada(punto->x,punto->y+1);
	}
	
	else if(mov.up == 1 && mov.left == 1)
	{
		int camino = rand()%2+1;
		
		if(camino == 1)
		punto = crearCoordenada(punto->x-1,punto->y);
		else
		punto = crearCoordenada(punto->x,punto->y-1);
	}
	
	else if(mov.down == 1 && mov.right == 1)
	{
		int camino = rand()%2+1;
		
		if(camino == 1)
		punto = crearCoordenada(punto->x+1,punto->y);
		else
		punto = crearCoordenada(punto->x,punto->y+1);
	}
	
	else if(mov.down == 1 && mov.left == 1)
	{
		int camino = rand()%2+1;
		
		if(camino == 1)
		punto = crearCoordenada(punto->x+1,punto->y);
		else
		punto = crearCoordenada(punto->x,punto->y-1);
	}
	
	return punto;
}
