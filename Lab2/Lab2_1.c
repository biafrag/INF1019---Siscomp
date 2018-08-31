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
    //Alocando memória compartilhada
    segmento = shmget(3333, 300*sizeof(char),IPC_CREAT | IPC_EXCL | S_IRUSR | S_IWUSR);  //Retorna id da área alocada
    //Associando memória compartilhada ao processo
    printf("Segmento: %d\n",segmento);
    mensagem = (char*) shmat(segmento,0,0);
	printf("Diga a mensagem do dia: ");
    scanf("%[^\n]s",mensagem);
	printf("Mensagem: %s\n",mensagem);
    return 0;
} 
