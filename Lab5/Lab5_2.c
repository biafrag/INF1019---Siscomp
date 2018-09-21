#include <pthread.h>
#include <stdio.h>
#include <sys/wait.h>
#define NUM_THREADS 2
int var = 0;
void Soma5()
{
	var+=5;
	printf("Soma 5 : %d\n",var);
	pthread_exit(NULL); /*not necessary*/
}
void Soma1()
{
	var+=1;
	printf("Soma 1 : %d\n",var);
	pthread_exit(NULL); /*not necessary*/
}
int main()
{
	pthread_t threads[NUM_THREADS];
	printf("Creating thread 0\n");
	pthread_create(&threads[0], NULL, Soma5,NULL);
	printf("Creating thread 1\n");
	pthread_create(&threads[1], NULL, Soma1,NULL);

	pthread_join(threads[0],NULL); /* wait for all the threads to
		terminate*/
	pthread_join(threads[1],NULL); /* wait for all the threads to
		terminate*/
}
