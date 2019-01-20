#include "csapp.h"

int main (int argc, char *argv[])
{
	//to store all the file descriptors
	int fd1, fd2, fd3;

	//3 characters to use as buffers
	char c1, c2, c3;

	//reads first arg as a filename to open
	char *fname = argv[1];

	//open argv[1] to each fd
	fd1 = open(fname, O_RDONLY, 0);
	fd2 = open(fname, O_RDONLY, 0);
	fd3 = open(fname, O_RDONLY, 0);

	//makes fd2 point to fd3
	dup2(fd2, fd3);

	//reads first character from infile
	read(fd1, &c1, 1);
	//reads first character from infile
	read(fd2, &c2, 1);
	//reads second character from infile as fd2 moved pointer to next character
	read(fd3, &c3, 1);
	//print all characters read in
	printf("c1 = %c, c2 = %c, c3 = %c\n", c1, c2, c3);

	//exit status
	return 0;
}
