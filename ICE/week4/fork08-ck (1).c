/*
  void fork08()
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
    printf("Running Child, PID = %d\n",
    getpid());
    while (1) ; /* Infinite loop */
   }
  else 
   {
    printf("Terminating Parent, PID = %d\n",
    getpid());
    exit(0);
   }
 }
