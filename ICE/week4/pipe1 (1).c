/*
  This program creates a pipe, and then forks to create a child process.
  The child inherits a duplicate set of file descriptors that refer to
  the same pipe. After the fork, each process closes the descriptors that
  it doesn't need for the pipe. The parent then writes the string
  contained in the program's command-line argument to the pipe, and
  the child reads this string a byte at a time from the pipe and echoes
  it on standard output.
*/

#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
 {
  int pipefd[2];
  pid_t cpid;
  char buf;
  if (argc != 2)
   {
    fprintf(stderr, "Usage: %s <string>\n", argv[0]);
    exit(1);
   }  
  pipe(pipefd);
  cpid = fork();
  if (cpid == 0)
   { /* Child reads from pipe */
    close(pipefd[1]); /* Close write end */
    while (read(pipefd[0], &buf, 1) > 0)
     write(STDOUT_FILENO, &buf, 1);
    write(STDOUT_FILENO, "\n", 1);
    close(pipefd[0]);
    exit(0);
   }
  else
   { /* Parent writes argv[1] to pipe */
    close(pipefd[0]); /* Close read end */
    write(pipefd[1],argv[1],strlen(argv[1]));
    close(pipefd[1]); /* Reader sees EOF */
    wait(NULL); /* Wait for child */
    exit(0);
   }
 }
