#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
int main(void)
{
	int fdentrada,fdsaida; /* descritor a ser duplicado */
	int retorno2; /* valor de retorno de dup2 */
	char texto[sizeof(char)];
	if ((fdentrada=open("Arq",O_RDONLY,0666)) == -1)
	{
		perror("Error open()");
		return -1;
	}
	if ((fdsaida=open("Arq2",O_CREAT|O_TRUNC|O_WRONLY,0666)) == -1)
	{
		perror("Error open()");
		return -1;
	}

	if ((retorno2 = dup2(fdsaida,1)) == -1)
	{ /* duplicacao de stdout */
		perror("Error dup2()");
		return -3;
	}
	if ((retorno2 = dup2(fdentrada,0)) == -1)
	{ /* duplicacao de stdout */
		perror("Error dup2()");
		return -3;
	}
	while(read(fdentrada, texto, sizeof(char))>0)
	{
		write(fdsaida,texto,sizeof(char));
	}
	//printf("%s %d\n",texto,retorno2);
	close(fdentrada); /* fechamento da entrada stdin */
	close(fdsaida); /* fechamento da entrada stdin */
	return 0;
}
