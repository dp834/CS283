#include <signal.h> 

#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>

void handler (int) ; /* Ctrl - C handler */

void main (void) 
 {
  signal (SIGINT, handler) ; /* install Ctrl - C handler   */
  while (1) /* loop forever and wait    */
   pause () ;
 }

void handler (int sig) 
 {
  char c;

  signal (sig, SIG_IGN) ; /* disable Ctrl - C           */
  printf ("quit? yn ") ;
  c = getchar () ; /* read an input character  */
  if (c == 'y') exit (0) ;
   else
    signal (SIGINT, handler) ;  /* reinstall the handler    */
 }

