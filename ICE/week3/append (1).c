#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

void error(char *msg);

int main (int argc, char *argv[])
 {
  char buf[32];
  int fd1, fd2, n;
  if (argc != 3) 
   error("Usage: append from to");
  if ((fd1 = open(argv[1], O_RDONLY, 0)) == -1)
   error("unable to open source file");
  if ((fd2 = open(argv[2], O_WRONLY, 0)) == -1)
   error("unable to open destination file");
  lseek(fd2, 0L, 2);
  while ((n = read(fd1, buf, 32) ) > 0)
   {
    write ( 1, buf, n);
    write ( 1, "\n", 1);
    write ( fd2, buf, n);
   }
  return 0;
 }

void error (char *msg)
 {
  fprintf(stderr, "%s: %s\n", msg, strerror(errno));
  exit(0);
 }
