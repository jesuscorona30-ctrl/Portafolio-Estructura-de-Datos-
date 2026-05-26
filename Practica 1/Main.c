#include <stdio.h>
#include "Alumno.h"
#include "Lista.h"
#include "string.h"

int main()
{
	
	int opc = 0;
	Lista lista = {NULL,NULL,0,imprimirAlumno,compararMatricula,free};
	
	Alumno *a,*b,*c, *d;
	
	
	do{
	printf("----MENU----\n");
	printf("\n1. Registrar Alumno(s)");
	printf("\n2. Desplegar Alumnos");
	printf("\n3. Reordenar");
	printf("\n4. Buscar Alumno");
	printf("\n5. Borrar Alumno");
	printf("\n6. Salir");
	printf("\n\nSelecciona una opcion: ");
	scanf("%d",&opc);
	
	switch(opc)
	{
		case 1:
				//Registra los alumnos
				a = crearAlumno(&lista);
				agregarEnOrden(&lista,a);
				printf("\nAlumno %s registrado con exito!\n",a->nombre);
				
				b = crearAlumno(&lista);
				
				if(b==NULL)
				{

					do
					{
						printf("\nEsta matricula ya esta registrada en la lista!\n");
						b = crearAlumno(&lista);
						
					}while(b==NULL);
					
				}			
				agregarEnOrden(&lista,b);
				printf("\nAlumno %s registrado con exito!\n",b->nombre);
				
				
				c = crearAlumno(&lista);
				
				if(c==NULL)
				{

					do
					{
						printf("\nEsta matricula ya esta registrada en la lista!\n");
						c = crearAlumno(&lista);
						
					}while(c==NULL);
					
				}			
				agregarEnOrden(&lista,c);
				printf("\nAlumno %s registrado con exito!\n",c->nombre);
				
				
				d = crearAlumno(&lista);
				
				if(d==NULL)
				{

					do
					{
						printf("\nEsta matricula ya esta registrada en la lista!\n");
						d = crearAlumno(&lista);
						
					}while(d==NULL);
					
				}			
				agregarEnOrden(&lista,d);
				
				printf("\nAlumno %s registrado con exito!\n",d->nombre);
				
				printf("\nDatos de alumnos capturados con exito!\n");
				
		break;
		
		case 2:
				imprimirLista(lista);
		break;
		
		case 3:
		{
			do{
				int opc = 0;
				printf("\n--- SUBMENU: REORDENAMIENTO ---");
				printf("\n1. Reordenar por matricula");
				printf("\n2. Reordenar por nombre");
				printf("\n3. Reordenar por semestre");
				printf("\n4. Reordenar por promedio");
				printf("\n\nSeleccione la opcion en la que desea reordenar la lista: ");
				scanf("%d",&opc);
				
				switch(opc)
				{
					case 1:
					reordenar(&lista, compararMatricula);
					printf("\nReordenamiento exitoso!");
					break;
					
					case 2:
					reordenar( &lista ,compararNombre);
					printf("\nReordenamiento exitoso!");
					break;
					
					case 3:
					reordenar( &lista ,compararSemestre);
					printf("\nReordenamiento exitoso!");
					break;
					
					case 4:
					reordenar( &lista ,compararPromedio );
					printf("\nReordenamiento exitoso!");
					break;
					
					default:
					printf("\nOpcion incorrecta");
					break;
				}
				
				
			}while(opc>4 && opc <= 0);
				
		}
		break;
		
		case 4:
		{
				int opc = 0;
				int mat,semestre;
				char name[15];
				float prom;
			
				printf("\n---SUBMENU DE BUSQUEDA---\n");
				printf("\n1. Buscar por matricula");
				printf("\n2. Buscar por nombre");
				printf("\n3. Buscar por semestre");
				printf("\n4. Buscar por promedio");
				printf("\n\nSeleccione una opcion: ");
				scanf("%d",&opc);
				
				switch(opc)
				{
					case 1:
					{
						printf("\nIngrese la matricula del alumno a buscar: ");
						scanf("%d",&mat);
						lista.comparar = busquedaMatricula;
						Alumno *al = NULL;
						Resultado res = buscar(lista,&mat);
						if(res.enco == NULL)
						{
						
							printf("\nMatricula del alumno no encontrada\n");
						
						}else{
							al = res.dato;
							printf("\n---MATRICULA %d ENCONTRADA DEL ALUMNO: %s---\n",al->matricula,al->nombre);
							printf("\nMatricula: %d",al->matricula);
							printf("\nNombre: %s",al->nombre);
							printf("\nSemestres: %d",al->semestre);
							printf("\nPromedio: %.2f\n",al->promedio);
						}
					}
					break;
					
					case 2:
					{
						
						printf("\nIngrese el nombre del alumno a buscar: ");
						getchar();
						fgets(name,sizeof(name),stdin);
						
						/*La funcion strcspn
						Sintaxis: size_t strcspn(const char *s, const char *reject);
						
						Busca el primer índice dentro de name donde aparece el carácter \n (salto de línea)
						Retorna la posición (índice) donde encuentra el primer '\n'
						
						Ejemplo:
						name = ['J','u','a','n','\n','\0', ...]
						índice:  0   1   2   3   4    5
						
						- strcspn(name, "\n") busca el primer \n

						- Lo encuentra en el índice 4

						- Retorna 4
						*/
						name[strcspn(name, "\n")] = 0;
						lista.comparar = busquedaNombre;
						Alumno *al = NULL;
						Resultado res = buscar(lista,name);
						if(res.enco == NULL)
						{
						
							printf("\nNombre del alumno no encontrado\n");
							
						}else{
							al = res.dato;
							printf("\n---NOMBRE DEL ALUMNO ENCONTRADO: %s---\n",al->nombre);
							printf("\nMatricula: %d",al->matricula);
							printf("\nSemestres: %d",al->semestre);
							printf("\nPromedio: %.2f\n",al->promedio);
						}
					}
					break;
					
					case 3:
					{
						
						printf("\nIngrese el semestre del alumno a buscar: ");
						scanf("%d",&semestre);
						lista.comparar = busquedaSemestre;
						/* 
						   Funcion: buscarEnLista();
						   Realiza una busqueda dentro de la lista 
						   imprime los datos del alumno, si el valor 
						   coincide con mas de un elemento econtrado
						   imprimira todos con dicho valor
						*/
						buscarEnLista(lista,&semestre);
					}
					break;
					
					case 4:
					{
						printf("\nIngrese el promedio del alumno a buscar: ");
						scanf("%f",&prom);
						lista.comparar = busquedaPromedio;
						
						/* 
						   Funcion: buscarEnLista();
						   Realiza una busqueda dentro de la lista 
						   imprime los datos del alumno, si el valor 
						   coincide con mas de un elemento econtrado
						   imprimira todos con dicho valor
						*/
						buscarEnLista(lista,&prom); 
					}
					break;
				}
				
		}
		break;
		
		case 5:
		{
			int mat;
			printf("\n---ELIMINAR ALUMNO DE LA LISTA---\n");
			printf("\nIngrese la matricula del alumno a extraer de la lista: ");
			scanf("%d",&mat);
			lista.comparar = busquedaMatricula;
			if(extraerMatricula(&lista,&mat))
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
		printf("\nOpcion no valida\n");
		break;
	}
	
	printf("\nDeseas regresar al menu? (si = 1/no = 0): ");
	scanf("%d",&opc);
	
	}while(opc!=0);
	
	printf("FIN DEL PROGRAMA");
	
	
	
	return 0;
}
