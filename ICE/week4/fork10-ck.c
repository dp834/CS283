/*
  void fork10()
*/

#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>

#define N 8

void main()
 {
  pid_t pid[N];
  int i;
  int child_status;
  for (i = 0; i < N; i++)
   if ((pid[i] = fork()) == 0)
    {
     sleep(20-i);
     exit(100+i); /* Child */
    }
  for (i = 0; i < N; i++) 
   {
    pid_t wpid = wait(&child_status);
    if (WIFEXITED(child_status))
     printf("Child %d terminated with exit status %d\n",
      wpid, WEXITSTATUS(child_status));
       else
        printf("Child %d terminate abnormally\n", wpid);
   }
 }
