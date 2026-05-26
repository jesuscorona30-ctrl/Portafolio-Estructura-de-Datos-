#include "Alumno.h"
#include "captura.h"


/*
Alumno* crearAlumno(void)
{
	Alumno *nuevo = calloc(1,sizeof(Alumno));
	inputEntero("\n Matricula: ",&nuevo->matricula);
	inputCadena("\n Nombre: ",nuevo->nombre,LEN);
	inputEntero("\n Semetres: ",&nuevo->semestre);
	inputFloat("\n Promedio: ",&nuevo->promedio);
	return nuevo;	
}
*/

Alumno* crearAlumno(ListaD *lista)
{
	Alumno *nuevo = calloc(1,sizeof(Alumno));
	
	// Si la lista no tiene nada
	if(!lista->inicio)
	{
	inputEntero("\n Matricula: ",&nuevo->matricula);
	inputCadena("\n Nombre: ",nuevo->nombre,LEN);
	inputEntero("\n Semetres: ",&nuevo->semestre);
	inputFloat("\n Promedio: ",&nuevo->promedio);
	}
	
	// Si la lista ya tiene algo
	else
	{
		
		inputEntero("\n Matricula: ",&nuevo->matricula);
		
		for(NodoD *p = lista->inicio; p!=NULL; p = p->sig)
		{
			// Si la matricula coincide con la ingresada retornara NULL como señal de que no se creo el alumno
			if(lista->comparar ( p->dato, nuevo) == 0)
			{
				nuevo = NULL;
				return nuevo;
			}
			
			else
			{
				continue;
			}
		}
			
		inputCadena("\n Nombre: ",nuevo->nombre,LEN);
		inputEntero("\n Semetres: ",&nuevo->semestre);
		inputFloat("\n Promedio: ",&nuevo->promedio);
	}
	
	return nuevo;	
}


void imprimirAlumno(void *dato)
{
	Alumno *alumno = dato;
	printf("\n %-7u | ",alumno->matricula);
	printf("%-40s | ",alumno->nombre);
	printf("%-2d | ",alumno->semestre);
	printf("%.2f  ",alumno->promedio);
}
//comparar
// NEGATIVO si datoA < datoB
// CERO si datoA == datoB
// POSITIVO si datoA > datoB
int compararMatricula(void *datoA,void *datoB)
{
	Alumno *alumA = datoA,*alumB = datoB;
	return alumA->matricula - alumB->matricula;	
}
int compararNombre(void *datoA,void *datoB)
{
	Alumno *alumA = datoA,*alumB = datoB;
	return strcmp(alumA->nombre,alumB->nombre);	
}
int compararSemestre(void *datoA,void *datoB)
{
	Alumno *alumA = datoA,*alumB = datoB;
	return alumA->semestre - alumB->semestre;	
	
}
int compararPromedio(void *datoA,void *datoB)
{
	Alumno *alumA = datoA,*alumB = datoB;
	if( alumA->promedio < alumB->promedio) return -1;
	else if( alumA->promedio > alumB->promedio) return 1;
	else return 0;
}
int compararAlumno(void *datoA,void *datoB)
{
	return 0;
}


// BUSQUEDA DE ALUMNOS
int busquedaMatricula(void *datoA,void *datoB)
{
	Alumno alumA;
	alumA.matricula = *(int*)datoA;
	Alumno *alumB = datoB;
	
	return alumA.matricula - alumB->matricula;	
}

int busquedaNombre(void *datoA,void *datoB)
{
	char *nombre = (char*)datoA;
	Alumno *alumB = datoB;
	return strcmp(nombre,alumB->nombre);	
}

int busquedaSemestre(void *datoA,void *datoB)
{
	Alumno alumA;
	alumA.semestre = *(int*)datoA;
	Alumno *alumB = datoB;
	return alumA.semestre - alumB->semestre;	
	
}


int busquedaPromedio(void *datoA,void *datoB)
{
	Alumno alumA;
	alumA.promedio = *(float*)datoA;
	Alumno *alumB = datoB;
	return alumA.promedio - alumB->promedio;	
	
}