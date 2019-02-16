#include "csapp.h"

int main () 
 {
  pid_t pid;
  int x = 1;

  pid = Fork () ;
  if (pid == 0) 
   {
    /* Child */
    printf ("child (id=%5d from %5d) : x = %d\n",getpid(),getppid(), ++ x) ;
    exit (0) ;
   }

  /* Parent */
  printf ("parent (id=%5d): x = %d\n",getpid(), -- x) ;
  exit (0) ;
 }

