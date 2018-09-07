#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>
#define EVER ;;
void usr1handler(int signo); 
void usr2handler(int signo); 
int delay;
clock_t tempoinicial;
int main (int argc, char *argv[])
{
	pid_t pid;
	clock_t tempo;
	signal(SIGUSR1, usr1handler);
	signal(SIGUSR2, usr2handler);
	printf("%d\n",getpid());
	for (EVER);
	return 0;
}
void usr1handler(int signo) 
{
 	tempoinicial = clock();
	printf("Comecei a ligacao\n");

}

void usr2handler(int signo)
{
	clock_t tempofinal,deltat;
	tempofinal = clock();
	int custo;
	deltat = (tempofinal - tempoinicial)/ CLOCKS_PER_SEC ;
	printf("Terminei a ligacao em %d segundos\n",deltat);
	if(deltat<=60)
	{
		custo=deltat*2;
	}
	else
	{
		custo= 60*2 + (deltat-60)*1;
	}
	printf("Custo da Ligacao: %d centavos\n",custo);
	exit(0);
}
