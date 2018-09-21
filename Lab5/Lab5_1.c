#include <pthread.h>
#include <stdio.h>
#include <sys/wait.h>
#define NUM_THREADS 2
void ContaCrescente()
{
	int i;
	printf("Conta crescente\n");
	for(i = 1; i<21 ; i++)
	{
		printf("%d\n",i);
		sleep(2);
	}
	printf("\n");
	pthread_exit(NULL); /*not necessary*/
}
void ContaDecrescente()
{
	int i;
	printf("Conta Decrescente\n");
	for(i = 30; i>0 ; i--)
	{
		printf("%d\n",i);
		sleep(1);
	}
	printf("\n");
	pthread_exit(NULL); /*not necessary*/
}
int main()
{
	pthread_t threads[NUM_THREADS];
	printf("Creating thread 0\n");
	pthread_create(&threads[0], NULL, ContaCrescente,NULL);
	printf("Creating thread 1\n");
	pthread_create(&threads[1], NULL, ContaDecrescente,NULL);

	pthread_join(threads[0],NULL); /* wait for all the threads to
		terminate*/
	pthread_join(threads[1],NULL); /* wait for all the threads to
		terminate*/
}
