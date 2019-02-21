/*
 * echoclient.c - An echo client
 */
#include "csapp.h"

int main(int argc, char **argv) 
{
	int clientfd, port;
		int n;
	char *host, buf[MAXLINE];
	rio_t rio;

	if (argc != 3) 
	{
		fprintf(stderr, "usage: %s <host> <port>\n", argv[0]);
		exit(0);
	}
	host = argv[1];
	port = atoi(argv[2]);

	clientfd = Open_clientfd(host, port);
	Rio_readinitb(&rio, clientfd);

	while (Fgets(buf, MAXLINE, stdin) != NULL) 
	{
		rio.rio_cnt = 0;
		Rio_writen(clientfd, buf, strlen(buf));
		n =Rio_readlineb(&rio,buf,MAXLINE);
		int lines = atoi(buf);
		while(lines-- >0){
		 	n = Rio_readlineb(&rio,buf,MAXLINE);
			rio_writen(1, buf, n);
		}
	}
	Close(clientfd);
	exit(0);
}
