#include <unistd.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>
int main (void)
{
    int segmento,i,j,indice,pid,status,segmento2,indice2;
	int *matriz,*transposta;
	segmento = shmget(IPC_PRIVATE, 16*sizeof(int),IPC_CREAT | S_IRUSR | S_IWUSR);  //Retorna id da área alocada
	segmento2 = shmget(IPC_PRIVATE, 16*sizeof(int),IPC_CREAT | S_IRUSR | S_IWUSR);  //Retorna id da área alocada
    matriz = (int*) shmat(segmento,0,0);
	transposta = (int*) shmat(segmento2,0,0);
	printf("Matriz:\n");
	for(i=0;i<16;i++)
	{
		printf("Diga M[%d][%d]: ",i/4,i%4);
		scanf("%d",&matriz[i]);
		printf("\n");
	}
	for(i = 0;i<4;i++)
	{
		pid = fork();
		if( pid <0)
		{
			printf("erro na criacao de processo\n");
			exit(-1);
		}
		else if (pid ==0)
		{
			printf("Pid: %d\n tranpondo linha %d\n",getpid(),i);
			for(j=0;j<4;j++)
			{
				indice = 4*i+j;	
				indice2 =4*j +i;
				transposta[indice2] = matriz[indice];
				printf("%d ",matriz[indice]);
			}
			printf("\n");
			exit(0);
		}
		else
		{
			waitpid(-1,&status,0);
		}
	}
	printf("\nMatriz:\n");
	for(i=0;i<4;i++)
	{
		for(j=0;j<4;j++)
		{
			indice = 4*i+j;	
			printf ("%d ",matriz[indice]);
		}
		printf("\n");
	}
	printf("\nTransposta\n");
	for(i=0;i<4;i++)
	{
		for(j=0;j<4;j++)
		{
			indice = 4*i+j;	
			printf ("%d ",transposta[indice]);
		}
		printf("\n");
	}
    //Libera memoria compartilhada do processo
    shmdt(matriz);
	shmdt(transposta);
    //Libera memória compartilhada
    shmctl(segmento,IPC_RMID,0);
	shmctl(segmento2,IPC_RMID,0);
    return 0;
}
