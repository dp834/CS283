#include "csapp.h"

int main(int argc, char **argv) {
	int n;
	rio_t rio;
	char buf[RIO_BUFSIZE];
	int fd;

	//if they pass a file as a parameter
	if (argc == 2) {
		fd = Open(argv[1], O_RDONLY, 0);//open the file
		if(fd < 0){//report if file can't be opened
			printf("Error opening file");
		}
		dup2(fd, STDIN_FILENO); //make stdout point to the file to copy to instead
	}

	Rio_readinitb(&rio, STDIN_FILENO);
	while((n = Rio_readlineb(&rio, buf, RIO_BUFSIZE)) != 0) {
		Rio_writen(STDOUT_FILENO, buf, n);
	}
}
