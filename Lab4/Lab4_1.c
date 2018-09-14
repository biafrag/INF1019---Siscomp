//Lab4 numero 1
//Fazer pipe entre dois processos do unix!!Descobrir diretório do processo
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
int main (void)
{
	int fd[2],status;
	int pid;
	const char texto[] = "Uma mesagem bonita";
	char texto2[sizeof texto];
	pipe(fd);
	pid = fork();
	if(pid < 0)
	{
		printf("Erro na criacao de processo\n");
		exit(-1);
	}
	else if (pid == 0)
	{ /* filho */
		close(fd[0]); /* fd[0] desnecessario */
		write(fd[1], texto, strlen(texto)+1); /* escreve para o pai */
		printf("%s\n",texto);
		

	}
	else
	{
		close(fd[1]); /* fd[1] desnecessario */
		read(fd[0], texto2, sizeof texto2); /* lê do filho */
		printf("%s\n",texto2);
		
	}
	close(fd[0]);
	close(fd[1]);
}
