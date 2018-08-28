#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main (void)
{
   int pid =1,status,var,i,pidneto,j;
   var = 1;
   for(j = 0; j< 2; j++)
   {
        if(pid != 0)
        	pid = fork();
   }
		if(pid!=0)
  		{
    		printf("Pai Executando\n");
    		printf("Pid dele: %d\n",getpid());
    		for(i = 1; i <= 50 ; i++)
    		{
        		printf("Valor Variavel Pai: %d\n",var);
        		var++;
			}
			waitpid(-1,&status,0);
    		printf("Pai terminou\n");
    		exit(0); 
		}
		else
		{
			printf("Filho Executando \n");
    		printf("Pid dele: %d\n",getpid());
        	for(i = 1; i <= 100 ; i++)
        	{
		    	printf("Valor Variavel Filho : %d\n",var);
		    	var+=2; 
        	}
		printf("Filho terminou\n");
        	exit(0);
		}
 
 
  
  return 0;
 
}
