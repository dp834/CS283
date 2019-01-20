#include "csapp.h"

int main(){
	int fd1, fd2, fd3;
	fd1 = Open("test.c", O_RDONLY, 0);
	fd2 = Open("statcheck.c", O_RDONLY, 0);
	Close(fd2);
	fd3 = Open("Makefile", O_RDONLY, 0);
	printf("%d", fd3);
	return 0;
}
