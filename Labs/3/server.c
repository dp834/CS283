#include "csapp.h"
#include <string.h>

void readFileToClient(int);
char* getFilename(char*, int);

int main(int argc, char** argv){
	if(argc != 2){
		printf("Usage: %s <port>\n", argv[0]);
		return 1;
	}

	int port = atoi(argv[1]);
	int listenfd, connfd, clientlen;
	struct sockaddr_in clientaddr;
	struct hostent *hp;
	char *haddrp;

	listenfd = Open_listenfd(port);
	while(1){
		clientlen = sizeof(clientaddr);
		connfd = Accept(listenfd, (SA *)&clientaddr, &clientlen);

		hp = Gethostbyaddr((const char *)&clientaddr.sin_addr.s_addr, sizeof(clientaddr.sin_addr.s_addr), AF_INET);
		haddrp = inet_ntoa(clientaddr.sin_addr);
		printf("Server connected to %s (%s)\n", hp->h_name, haddrp);
	
		readFileToClient(connfd);
		printf("Server closing connection to %s (%s)\n", hp->h_name, haddrp);
		Close(connfd);
	}	
	return 0;
}

void readFileToClient(int connfd){
	size_t n, len;
	char bufIn[MAXLINE];
	char *buffFile = NULL;
	char *fileName = NULL;

	rio_t rio_socket;
	FILE *readFile;
	Rio_readinitb(&rio_socket, connfd);
	n = Rio_readlineb(&rio_socket, bufIn, MAXLINE);
	fileName = getFilename(bufIn, n);
	if(!fileName){//invalid request
		Rio_writen(connfd, "Invalid request\n", sizeof("Invalid request\n"));
		return;
	}
	printf("Opening file: '%s'\n", fileName);
	readFile = fopen(fileName, "r");
	if(readFile == NULL){
		Rio_writen(connfd, "File not found in server's directory\n", sizeof("File not found in server's directory\n"));
	}else{
		while((n = getline(&buffFile, &len, readFile)) != -1){
			Rio_writen(connfd, buffFile, n);
		}
		fclose(readFile);
	}
	if(fileName){
		free(fileName);
	}
}


char* getFilename(char *request, int length){
	char* file = NULL;
	if(strncmp("GET /", request, 5)){
		printf("Doesn't match GET\n");
		//doesn't match
		printf("Recieved invalid request\n");
		return file;
	}else if(strncmp(" HTTP/1.1\r\n", request + (length - 11), 11)){
		printf("End: '%s'\n", request + (length - 11));
		printf("Doesn't match End\n");
		//doesn't match
		printf("Recieved invalid request\n");
		return file;
	}else{
		//valid request
		file = malloc((length-16)*sizeof(char));
		memcpy(file, request + 5, length - 16);
		file[length - 16] = '\0';
	}

	return file;	
}
