#include <stdio.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <stdlib.h>
#define KIDS 8
int main (void)
{
    int pid,status,segmento,segmento2,*p,id,i,x,final,j,k,n,vetorvalue;
    int *vetor;
	int *vetormaior,maior,maiorpos;
    //Alocando memória compartilhada
    segmento = shmget(30001, 8*sizeof(int),IPC_CREAT | IPC_EXCL | S_IRUSR | S_IWUSR);  //Retorna id da área alocada
    //Associando memória compartilhada ao processo
    vetormaior = (int*) shmat(segmento,0,0);
	for(k = 0; k < 128; k++)
	{
		vetor[k] = rand()%1000;
	}
	waitpid(-1,&status,0);
    for(i = 0; i< KIDS; i++)
    {
        id = fork();
        if(id < 0)
        {
            puts("Erro de criacao de processo\n");
            exit(-1);
        }
        else if (id == 0)
        {

            final = i*16 + 16;
			printf("Processo %d procurando\n",getpid());
			vetorvalue = -1;
            for(j=i*16;j< final;j++)
            {
             	if(vetor[j] > vetorvalue)
                {
					vetorvalue = vetor[j];
                    vetormaior[i] = j; 
                }
            }
			printf("Maior encontrado nesse vetor na posicao %d do vetor: %d\n",vetormaior[i],vetorvalue); 
			exit(0);
        }
		else
		{
			waitpid(-1,&status,0);
		}
	}
	maior = -1;
    printf("Processo pai\nVetor: \n");
    waitpid(-1,&status,0);
	for(k = 0; k < 128; k++)
	{
		printf("vetor[%d] : %d\n",k,vetor[k]);
	}
	for(n = 0; n < 8 ; n++)
	{
		if(vetor[vetormaior[n]]>maior)
		{
			maior = vetor[vetormaior[n]];
			maiorpos = vetormaior[n];
			
		}
	}
	printf("Maior deles esta na posicao %d e eh %d \n",maiorpos,maior);
   
    //Libera memoria compartilhada do processo
    shmdt(vetormaior);
    //Libera memória compartilhada
    shmctl(segmento,IPC_RMID,0);
    return 0;
}
