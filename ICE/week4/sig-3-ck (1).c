/* This program uses the alarm clock to sample the value of a
   global counter in fixed periods. */

#include <signal.h> 

#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>

unsigned long counter; /* global counter           */
int MAX; /* max # of sampling        */
int AlarmCount; /* sampling count           */
int seconds; /* sampling duration        */

/*    This is the alarm signal handler.  When it is activated,  this */
/* function increases the sampling count,  displays the current      */
/* value of the global counter,  and resets both the counter and     */
/* sampling duration.                                               */

void handler (int sig) 
 {
  signal (SIGALRM, SIG_IGN) ;
  printf ("alarm no. %2d ", AlarmCount) ;
  printf ("counter = %12ld\n", counter) ;
  AlarmCount ++ ;
  if (AlarmCount == MAX) 
   {
    printf ("Maximum alarm count reached. exit\n") ;
    exit (0) ;
   }
//counter = 0; /* reset counter */
  alarm (seconds) ;
  signal (SIGALRM, handler) ;   /* reinstall the handler    */
 }

void main (int argc, char * argv[]) 
 {
  if (argc != 3) 
   {
    printf ("Usage: %s seconds max_alarm_count\n", argv[0]) ;
    printf ("No. of seconds 1 Max number of alarms 5\n") ;
    seconds = 1;
    MAX = 5;
   }
  else 
   {
    seconds = atoi (argv[1]) ;
    MAX = atoi (argv[2]) ;
   }
  counter = 0; 
  AlarmCount = 0;
  signal (SIGALRM, handler);
  printf ("Alarm set to %d seconds and is ticking now.....\n", seconds) ;
  alarm (seconds);   /* set alarm clock          */
  while (1)
   counter ++ ;
 }

