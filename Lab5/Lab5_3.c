#include <pthread.h>
#include <stdio.h>
#include <sys/wait.h>
#define NUM_THREADS 2
#define MAXFILA 8
int fila[MAXFILA];
int ini = 0;
int fim = 0;
int numelem = 0;
void Produtor()
{
	int i = 0;
	while(i < 64)
	{
		
		if(numelem < MAXFILA)
		{
			fila[fim] = rand()%64;
			numelem++;
			printf("Numero %d colocado\n",fila[fim]);
			fim++;
			if(fim == MAXFILA)
			{
				fim = 0;
			}
			i++;
		}	
		else
		{
			printf("Cheia\n");
			sleep(3);
		}
		sleep(1);
	}
	pthread_exit(NULL); /*not necessary*/
}
void Consumidor()
{
	int i = 0;
	while(i < 64)
	{
		if(numelem == 0)
		{
			printf("Vazia\n");
			sleep(3);
		}
		if(ini>=0)
		{
			printf("Item tirado: %d\n",fila[ini]);
			ini++;
			numelem--;
			i++;
		}
		if(ini > MAXFILA)
		{
			ini=0;
		}
		sleep(2);
	}
	pthread_exit(NULL); /*not necessary*/
}
int main()
{
	pthread_t threads[NUM_THREADS];
	printf("Creating thread 0\n");
	pthread_create(&threads[0], NULL, Produtor,NULL);
	printf("Creating thread 1\n");
	pthread_create(&threads[1], NULL, Consumidor,NULL);

	pthread_join(threads[0],NULL); /* wait for all the threads to
		terminate*/
	pthread_join(threads[1],NULL); /* wait for all the threads to
		terminate*/
}
