#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

// defines function to be used later
void error(char *msg);

int main (int argc, char *argv[])
 {
  //creates input buffer for reading file
  char buf[32];
  //creates file descriptors and n
  int fd1, fd2, n;
  
  //checks proper arguments are used
  if (argc != 3) 
   error("Usage: append from to");
  
  //try to open source file as read only into fd1
  if ((fd1 = open(argv[1], O_RDONLY, 0)) == -1)
   error("unable to open source file");
  
  //try to open source file as write only into fd2
  if ((fd2 = open(argv[2], O_WRONLY, 0)) == -1)
   error("unable to open destination file");

  //move descriptor to the end of the file so we are appending
  lseek(fd2, 0L, 2);
  
  //read up to 32 bytes into the buffer from fd1 until eof or error
  while ((n = read(fd1, buf, 32) ) > 0)
   {
	 //write the buffer to stdout
    write ( 1, buf, n);
	 //write a newline to stdout
    write ( 1, "\n", 1);
	 //write buffer to destination file (is appending)
    write ( fd2, buf, n);
   }
  //return success status
  return 0;
 }

//used to inform user of error by printing to stderror
void error (char *msg)
 {
  //print to stderr using msg and give actual error
  fprintf(stderr, "%s: %s\n", msg, strerror(errno));
  //still exits successfully (probably shouldn't)
  exit(0);
 }
