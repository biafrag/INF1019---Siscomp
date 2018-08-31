#include <stdio.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <stdlib.h>
#define KIDS 8
int main (void)
{
    int pid,status,segmento,*p,id,i,x,final,j,k,n;
    int vetor[128];
	int *vetormaior,maior;
    //Alocando memória compartilhada
    segmento = shmget(IPC_PRIVATE, 8*sizeof(int),IPC_CREAT | IPC_EXCL | S_IRUSR | S_IWUSR);  //Retorna id da área alocada
    //Associando memória compartilhada ao processo
    vetormaior = (int*) shmat(segmento,0,0);
	for(i = 0; i < 8; i++)
	{
		vetormaior[i] = -1;
	}
    for(i = 0; i< KIDS; i++)
    {
        id = fork();
        if(id < 0)
        {
            puts("Error de criacao de processo\n");
            exit(-1);
        }
        else if (id == 0)
        {
			if(i == 0)
			{
				for(k = 0; k < 128; k++)
				{
					vetor[k] = rand()%450;
				}
			 }
            final = i*8 + 16;
            for(j=i*8;j< final;j++)
            {
                printf("Procurando %d\n",getpid());
             	if(vetor[j] > vetormaior[i])
                {
                    vetormaior[i] = vetor[j];
                }
            }
			exit(0);
        }
	}
	maior = -1;
    printf("Processo pai\n");
    waitpid(-1,&status,0);
	for(n = 0; n < 8 ; n++)
	{
		if(vetormaior[n]>maior)
		{
			maior = vetormaior[n];
		}
	}
	printf("Maior deles: %d\n",maior);
    exit(0);
   
    //Libera memoria compartilhada do processo
    shmdt(p);
    //Libera memória compartilhada
    shmctl(segmento,IPC_RMID,0);
    return 0;
}
