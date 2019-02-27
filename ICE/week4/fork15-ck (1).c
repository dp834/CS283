/*
  void fork15()
*/

#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>

#define N 8

int ccount = 0;

void child_handler (int sig)
 {
  int child_status;
  pid_t pid = wait(&child_status);
  ccount--;
  printf("Received signal %d from process %d\n",sig, pid);
 }

void child_handler2 (int sig)
 {
  int child_status;
  pid_t pid;
  while ((pid = waitpid(-1, &child_status, WNOHANG)) > 0)
   {
    ccount--;
   	printf("Received signal %d from process %d\n", sig, pid);
   }
 }

void main ()
 {
  pid_t pid[N];
  int i, child_status;
  ccount = N;
  signal(SIGCHLD, child_handler2);
  for (i = 0; i < N; i++)
   if ((pid[i] = fork()) == 0)
    {
     sleep(1);
     exit(0);
    }
  sleep(3);
  while (ccount > 0)
   pause(); /* Suspend until signal occurs */
 }
