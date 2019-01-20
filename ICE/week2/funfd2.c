#include "csapp.h"

int main (int argc, char *argv[])
{
	//3 file descriptors
	int fd1, fd2, fd3;
	//reads argv 1 to fname
	char *fname = argv[1];

	//opens argv[1] to fd1
	//will create file if it doesn't exist
	//writes to file will override from the beginning
	//will be open as read and write
	//if file is created by O_CREAT then it will be given usr read and usr write permissions
	fd1 = open(fname, O_CREAT|O_TRUNC|O_RDWR, S_IRUSR|S_IWUSR);
	//writes pqrs to created file 
	write(fd1, "pqrs", 4);
	//opens same file as fd1 with append and write permissions, no creation flags needed
	fd3 = open(fname, O_APPEND|O_WRONLY, 0);
	//will append jklmn to file 
	write(fd3, "jklmn", 5);
	//makes fd2 point to fd1
	fd2 = dup(fd1);  /* Allocates descriptor */
	//wxyz will override the jklm but not the n
	write(fd2, "wxyz", 4);
	//ef will be appended to the file
	write(fd3, "ef", 2);

	//file should be pqrswxyznef

	//returns success
	return 0;
}
