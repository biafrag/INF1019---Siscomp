#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main (void)
{
   int pid,status,var,i,pidneto,statusfilho;
   var = 1;
   pid = fork();
   
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
    pidneto = fork();
    if(pidneto != 0 )
    {
		printf("Filho Executando\n");
    	printf("Pid dele: %d\n",getpid());
        for(i = 1; i <= 100 ; i++)
        {
		    printf("Valor Variavel Filho: %d\n",var);
		    var+=2; 
        }
        waitpid(-1,&statusfilho,0);
		printf("Filho terminou\n");
        exit(0);
    }
    else
    {
		printf("Neto Executando\n");
    	printf("Pid dele: %d\n",getpid());
		for(i = 1; i <= 150 ; i++)
        {
		    printf("Valor Variavel Neto: %d\n",var);
		    var+=3; 
        }
		printf("Neto terminou\n");
        exit(0);
	}

  }
  
  return 0;
 
}
