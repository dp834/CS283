/* void fork11() */

#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>

#define N 8

void main()
 {
  pid_t pid[N];
  int i, j;
  for( i = 0; i < N; i++){
	pid[i]=-1;
  }
  int child_status;
  for (i = 0; i < N; i++)
   if ((pid[i] = fork()) == 0)
    {
     sleep(10+i);
     for( j = 0; j <= i; j++){
		printf("Child %d pid[%d] = %d\n",getpid(), j, pid[j]);
	  }
	  exit(100+i); /* Child */
    }
  /* Child */
  for (i = 0; i < N; i++) 
   {
    pid_t wpid = waitpid(pid[i], &child_status, 0);
    if (WIFEXITED(child_status))
     printf("Child %d terminated with exit status %d\n",
      wpid, WEXITSTATUS(child_status));
       else
        printf("Child %d terminated abnormally\n", wpid);
   }
 }
