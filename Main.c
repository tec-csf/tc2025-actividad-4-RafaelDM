/*
 Rafael Díaz Medina A01024592
 Me base en su programa creando procesos del repositorio que usted nos compartio
 En lo general despues de correrlo muchas veces aproximadamente unas 10 veces el programa empieza a fallar al entregar 
 el resultado del promedio, parece ser que lo dividiera 2 veces entre 2, no se si sea la terminal en la que lo ejecuto
 es la terminal de WSLbash
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

typedef struct {
	int pidHijo;
}Hijos;

int main(int argc, const char * argv[]){ 
	pid_t * i;
	int pid;
	int bs = 0;
	int * pidHijo;
	char * number;
	int promedio;

	number =(char *) malloc(sizeof number);
	printf("Numero de hijos a crear: ");
	scanf("%s", number);
	printf("\n");
	int n = atoi(number);

	Hijos * hijo;
    hijo = (Hijos*)malloc(n* sizeof(Hijos));
	pidHijo= (int *) malloc(n * sizeof(n));

	if(n>0){
		for (i = pidHijo; i < pidHijo + n; i++, bs++){
			*i = fork();

			if (*i == -1){
				//-------error--------
				printf("\nError al crear el proceso hijo. Se han creado %d procesos.\n", bs);
				return 1;
			}
			else if (*i == 0){
				(hijo+*i)->pidHijo=getpid();
				//------hijos---------
				promedio=((getpid() + getppid()) / 2);
				//printf("%d",getppid());
				printf("Soy el proceso hijo con PID = %d y mi promedio es = %d \n", (hijo+*i)->pidHijo, promedio);
				exit(promedio);
			}
		}

		int estado;
		//int auxPrint=0;
		sleep(1);//un sleep de un segundito xD
		printf("\nPID hijo		Promedio		Histograma\n");
		for (i = pidHijo; i < pidHijo + n; i++) {
			if (waitpid(*i, &estado, 0)!=-1){
			/*if(auxPrint==){
				printf("PID hijo		Promedio		Histograma\n");
			}*/
			if (WIFEXITED(estado)){
                printf("%d			%d			 ",*i, WEXITSTATUS(estado));

				if(WEXITSTATUS(estado)<200){
					for(int s=0; s<(WEXITSTATUS(estado)/20); s++){
						printf("*");
					}
				}
				else{
					for(int s=0; s<(WEXITSTATUS(estado)/100); s++){
						printf("*");
					}
				}
				printf("\n");
				}
			}
		}

	}
	else
	{
		printf("\nEntrada de dato invalida\n");
	}
	free(hijo);
	hijo=NULL;
	free(pidHijo);
	pidHijo=NULL;
	free(number);
	number=NULL;
    return 0;
}
