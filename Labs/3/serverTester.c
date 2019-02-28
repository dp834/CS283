#include "csapp.h"

void createRequest(char*, char*, char*, char*);

int main(int argc, char** argv){
	if(argc != 4){
		printf("Usage: %s <host> <port> <file>\n", argv[0]);
		return 1;
	}

	int clientfd, port;
	char *host, buf[MAXLINE];
	rio_t rio;
	
	host = argv[1];
	port = atoi(argv[2]);

	clientfd = Open_clientfd(host, port);
	Rio_readinitb(&rio, clientfd);
	createRequest(buf, host, argv[2], argv[3]);

	Rio_writen(clientfd, buf, strlen(buf));	
	rio_writen(1,buf,strlen(buf));		
	int n;

	while((n = Rio_readlineb(&rio, buf, MAXLINE)) > 0){
		rio_writen(1,buf,n);
	}
	printf("\n");
	Close(clientfd);
	return 0;
}

void createRequest(char *buf, char *host, char *port, char *file){
	sprintf(buf, 
		"GET /%s HTTP/1.1\r\n\r\n",file);
}
