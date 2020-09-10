/**
 Recibe como argumento en la línea de comandos el número de procesos hijos a crear (opción -n). 
 El programa debe validar que el valor especificado sea un número entero. 
Sugerencia: revise la función atoi (Enlaces a un sitio externo.).
Crea los n procesos hijos siempre y cuando no existan errores. Si al crear un proceso hijo se genera un error, 
entonces debe mostrar un mensaje indicando el número de procesos hijos creados hasta ese momento y no debe intentar 
crear más procesos hijos.
Espera a que terminen todos los procesos hijos en el mismo orden en que se crearon.
A medida que los procesos hijos van terminando, debe ir guardando el valor de retorno de cada proceso hijo.
Una vez que terminen todos los procesos hijos, el proceso padre debe mostrar una tabla en el siguiente formato:
PID Hijo	Promedio	Histograma
20	20	********************
10	15	**************
50	35	*****************************
60	40	**************************************
Sugerencia: Para determinar la cantidad de * a imprimir, defina una relación respecto al promedio máximo obtenido. 
Por ejemplo, si el promedio máximo obtenido es 1000, entonces divida los promedios entre 100. De esta manera, 
para el promedio máximo imprimirá 10 * y todos los demás estarán acotados por debajo de este máximo.

Por su parte, cada proceso hijo debe:

Calcular el promedio entre su PID y el PID de su padre.
Imprimir un mensaje que diga: "Soy el proceso hijo con PID = $pid y mi promedio es = $promedio".
$pid debe sustituirse por el valor del PID del proceso hijo.
$promedio debe sustituirse por el resultado de calcular el promedio entre el PID del proceso hijo y el PID 
del proceso padre.
Al terminar, debe regresar el promedio calculado como valor de retorno  al proceso padre.
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, const char * argv[]){ 
	int * i;
	int pid;
	int buenos = 0;

	char * number;
	number =(char *) malloc(sizeof number);
	printf("\nNumero de hijos a crear: ");
	scanf("%s", number);
	int n = atoi(number);
	//printf("%d", n);

	int promedio;
	int * pidHijo;
	pidHijo= (int *) malloc(n * sizeof(n));
	printf("PID hijo		Promedio		Histograma\n");
	if(n>0){
		//printf("\nHey\n");
		
		for (i = pidHijo; i < pidHijo + n; i++, buenos++){
			*i = fork();

			if (*i == -1) {
				printf("\nError al crear el proceso hijo. Se han creado %d procesos.\n", buenos);
				return 1;
			}
			else if (*i == 0) {
				promedio=(getpid()+getppid()/2);
				printf(" %d		     	%d			", getpid(), (getpid() + getppid()) / 2);
				
				for(int s=0; s<(promedio/10); s++){
					printf("*");
				}
				printf("\n");
				//printf("Promedio: %d\n", (getpid() + getppid()) / 2);
				exit(0);
			}
		}
		int estado;
		for (i = pidHijo; i < pidHijo + n; i++) {
			waitpid(*i, &estado, 0);
			/*if (WIFEXITED(estado))
                printf("\nYa terminó el hijo con PID %ls \n", pidHijo);*/
		}

	}
	else
	{
		printf("\nEntrada de dato invalida\n");
	}
	
	free(number);
    return 0;
}
