#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
int main (void)
{
   int pid,status;
   pid = fork();
   
  if(pid!=0)
  {
    printf("Pai Executando\n");
    printf("Pid dele: %d\n",getpid());
    waitpid(-1,&status,0);
    printf("Pai terminou\n");
    exit(0);
  }
  else
  {
    printf("Filho Executando\n");
    printf("Pid dele: %d\n",getpid());
    printf("Filho terminou\n");
    exit(0);
  }
  
  return 0;
 
}
