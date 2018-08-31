#include <stdio.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <stdlib.h>
int main (void)
{
    int segmento;
    char *mensagem;
	segmento = shmget(3333, 300*sizeof(char),IPC_CREAT | S_IRUSR | S_IWUSR);  //Retorna id da área alocada
    mensagem = (char*) shmat(segmento,0,0);
    printf("Mensagem do dia eh: %s\n",mensagem);
    //Libera memoria compartilhada do processo
    shmdt(mensagem);
    //Libera memória compartilhada
    shmctl(segmento,IPC_RMID,0);
    return 0;
} 
