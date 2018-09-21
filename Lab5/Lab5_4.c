#include <pthread.h>
#include <stdio.h>
#include <sys/wait.h>
#define N 5
#define X 100
#define Y 10
#define D 300
int vencedores[N];
int indice = 0;
void* PuloDoSapo(int i)
{
	int dist = 0;
	int percorre;
	int espera;
	while(dist < D)
	{
		percorre = (rand()%X) + 1;
		espera = (rand()%Y) + 1;
		printf("Sapo %d pulou %d de distancia e vai esperar %d u.t\n",i,percorre,espera);
		dist+=percorre;
		sleep(espera);
	}
	vencedores[indice] = i;
	indice++;
	pthread_exit(NULL); /*not necessary*/

}
int main()
{
	int i;
	pthread_t threads[N];
	
	for(i = 0; i< N;i++)
	{
			printf("Creating thread %d\n",i);
			pthread_create(&threads[i], NULL, PuloDoSapo,(void*)i);
	}
	for(i = 0; i< N;i++)
	{
			pthread_join(threads[i],NULL); /* wait for all the threads to
		terminate*/
	}
	printf("Ranking dos Sapos\n");
	for(i = 0; i< N;i++)
	{
		printf("Sapo %d em %dº lugar\n",vencedores[i],i+1);
	}
}
