/*
  void fork07()
*/

#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>

void main()
 {
  if (fork() == 0) 
   {
    /* Child */
    printf("Terminating Child,PID %d\n",getpid());
    exit(0);
   }
  else 
   {
    printf("Running Parent,PID = %d\n",getpid());
    while (1) ; /* Infinite loop */
   }
 }
