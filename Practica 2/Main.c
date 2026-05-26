#include <stdio.h>
#include "Alumno.h"
#include "listadoble.h"
#include "string.h"



int main()
{
	
	int opc = 0;
	ListaD listaD = {NULL,NULL,0,compararPromedio,imprimirAlumno,free};
	
	Alumno *a,*b,*c,*d;
	
	do
	{
		printf("\n---Menu: LISTA DOBLEMENTE ENLAZADA---\n");
		printf("\n1.Registrar Alumno");
		printf("\n2.Desplegar Alumnos");
		printf("\n3.Reordenar");
		printf("\n4.Buscar Alumno");
		printf("\n5.Borrar Alumno");
		printf("\nSeleccione una de las siguientes opciones: ");
		scanf("%d",&opc);
		
		switch(opc)
		{
			case 1:
			{
				listaD.comparar = compararMatricula;
				a = crearAlumno(&listaD);
				printf("\nDatos del alumno %s registrados correctamente!\n",a->nombre);
				insertarEnOrdenD(&listaD,a);
				
				b = crearAlumno(&listaD);
				
				if(b==NULL)
				{
					do{
						
					printf("\nLa matricula ingresada ya existe dentro de la lista\n");
					b = crearAlumno(&listaD);
					
					}while(b==NULL);
				}
			
				insertarEnOrdenD(&listaD,b);
				printf("\nDatos del alumno %s registrados correctamente!\n",b->nombre);
				
				
				c = crearAlumno(&listaD);
				
				if(c==NULL)
				{
					do {
						
					printf("\nLa matricula ingresada ya exite dentro de la lista\n");
					c = crearAlumno(&listaD);
					
					}while(c==NULL);
				}
				
				insertarEnOrdenD(&listaD,c);
				printf("\nDatos del alumno %s registrados correctamente!\n",c->nombre);
				
				
				
				printf("\nInsercion de los datos exitoso!\n");
			}
			break;
			
			case 2:
			{
					int opc;
					printf("\n---Desplegar Alumnos---\n");
					printf("\n1.Ascendente (inicio-fin)");
					printf("\n2.Descendente (fin-inicio)");
					
					do{
						
					printf("\nSeleccione una opcion: ");
					scanf("%d",&opc);
					
					switch(opc)
					{
						
						case 1:
						imprimirListaDIF(listaD);
						break;
						
						case 2:
						imprimirListaDFI(listaD);
						break;
						
						default:
						printf("\nOpcion incorrecta\n");
						break;
					}
					
					}while(opc!=1 && opc!=2);
			}
			break;
			
			case 3:
			{
					int opc;
					printf("\n---Reordenar Alumnos---\n");
					printf("\n1.Reordenar por matricula");
					printf("\n2.Reordenar por nombre");
					printf("\n3.Reordenar por semestre");
					printf("\n4.Reordenar por promedio");
					
					do
					{
					printf("\nSelecciona una de las siguientes opciones: ");
					scanf("%d",&opc);
					
					switch(opc)
					{
						case 1:
						listaD.comparar = compararMatricula;
						reordenarD(&listaD,compararMatricula);
						printf("\nLa lista ha sido reordenada por matriculas!\n");
						printf("\nReordenamiento exitoso!");
						break;
						
						case 2:
						listaD.comparar = compararNombre;
						reordenarD(&listaD,compararNombre);
						printf("\nLa lista ha sido reordenada por nombres!\n");
						printf("\nReordenamiento exitoso!");
						break;
						
						case 3:
						listaD.comparar = compararSemestre;
						reordenarD(&listaD,compararSemestre);
						printf("\nLa lista ha sido reordenada por semestres!\n");
						printf("\nReordenamiento exitoso!");
						break;
						
						case 4:
						listaD.comparar = compararPromedio;
						reordenarD(&listaD,compararPromedio);
						printf("\nLa lista ha sido reordenada por promedios!\n");
						printf("\nReordenamiento exitoso!");
						break;
						
						default:
						printf("\nOpcion incorrecta\n");
						break;
					}
					
					}while(opc < 1 && opc > 4);
			}
			break;
			
			case 4:
			{
				int opc,mat,semestre;
				float promedio;
				char name[15];
				
				printf("\n---BUSCAR ALUMNO POR:---\n");
				printf("\n1.Matricula");
				printf("\n2.Nombre");
				printf("\n3.Semestre");
				printf("\n4.Promedio");
				
				do{
					
				printf("\nSeleccione el criterio de la busqueda: ");
				scanf("%d",&opc);
				
				switch(opc)
				{
					case 1:
					
					printf("\nIngrese la matricula del alumno a buscar: ");
					scanf("%d",&mat);
					listaD.comparar = busquedaMatricula;
					buscarEnListaD(listaD,&mat);
					
					break;
					
					case 2:
					printf("\nIngrese el nombre del alumno a buscar: ");
					getchar();
					fgets(name,sizeof(name),stdin);
					name[strcspn(name, "\n")] = 0;
					listaD.comparar = busquedaNombre;
					buscarEnListaD(listaD,name);
					break;
					
					case 3:
					printf("\nIngrese los semestres del alumno: ");
					scanf("%d",&semestre);
					listaD.comparar = busquedaSemestre;
					buscarEnListaD(listaD,&semestre);
					break;
					
					case 4:
					printf("\nIngrese el promedio del alumno a buscar: ");
					scanf("%f",&promedio);
					listaD.comparar = busquedaPromedio;
					buscarEnListaD(listaD,&promedio);
					break;
					
					default:
					printf("\nOpcion incorrecta\n");
					break;
				}
				
				}while(opc<1 && opc>4);
				
			}
			break;
			
			case 5:
			{
				int mat;
				printf("\n---EXTRAER MATRICULA DE LA LISTA---\n");
				printf("\nIngrese la matricula del alumno a extraer: ");
				scanf("%d",&mat);
				listaD.comparar = busquedaMatricula;
				if(extraerMatricula(&listaD,&mat))
				{
					printf("\nExtraccion de la matricula %d en la lista\n",mat);
				}
				else
				{
					printf("\nERROR: No fue posible extraer la matricula\n");
				}
			}
			break;
			
			default:
			printf("\nOpcion incorrecta\n");
			break;
		}
		
		printf("\n\nDeseas regresar al menu? (si=1/no=0): ");
		scanf("%d",&opc);
		
	}while(opc!=0);
	
	
	printf("\n\nFIN DEL PROGRAMA");
	return 0;
}