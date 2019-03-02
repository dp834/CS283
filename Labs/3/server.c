#include "csapp.h"
#include <string.h>

void readFileToClient(int);
char* getFilename(char*, int);

int main(int argc, char** argv){
	//check args
	if(argc != 2){
		printf("Usage: %s <port>\n", argv[0]);
		return 1;
	}

	//create variables, used slide notes
	int port = atoi(argv[1]);
	int listenfd, connfd, clientlen;
	struct sockaddr_in clientaddr;
	struct hostent *hp;
	char *haddrp;

	//create a file descriptor with port passed from user
	listenfd = Open_listenfd(port);
	while(1){//accept connections forever
		//prepare to recieve new connection
		clientlen = sizeof(clientaddr);
		connfd = Accept(listenfd, (SA *)&clientaddr, &clientlen);
		//finish connection with client
		hp = Gethostbyaddr((const char *)&clientaddr.sin_addr.s_addr, sizeof(clientaddr.sin_addr.s_addr), AF_INET);
		haddrp = inet_ntoa(clientaddr.sin_addr);
		printf("Server connected to %s (%s)\n", hp->h_name, haddrp);
		//process input from client
		readFileToClient(connfd);
		printf("Server closing connection to %s (%s)\n", hp->h_name, haddrp);
		//close connection to client
		Close(connfd);
	}	
	return 0;
}

void readFileToClient(int connfd){
	//initialize
	size_t n, len;
	char bufIn[MAXLINE];
	char *buffFile = NULL;
	char *fileName = NULL;
	
	rio_t rio_socket;
	FILE *readFile;
	//init rio to read user input
	Rio_readinitb(&rio_socket, connfd);
	n = Rio_readlineb(&rio_socket, bufIn, MAXLINE);
	//get filename from request
	fileName = getFilename(bufIn, n);
	if(!fileName){//invalid request
		Rio_writen(connfd, "Invalid request\n", sizeof("Invalid request\n"));
		printf("Invalid request\n");
		return;
	}
	//try to open file with read permissions
	printf("Opening file: '%s'\n", fileName);
	readFile = fopen(fileName, "r");
	if(readFile == NULL){//if file couln't be opened tell user
		Rio_writen(connfd, "File not found in server's directory\n", sizeof("File not found in server's directory\n"));
		printf("File not found\n");
	}else{
		//send user all lines from file
		while((n = getline(&buffFile, &len, readFile)) != -1){
			Rio_writen(connfd, buffFile, n);
		}
		//close file
		fclose(readFile);
	}
	//free the fileName pointer 
	if(fileName){
		free(fileName);
	}
}


char* getFilename(char *request, int length){
	char* file = NULL;
	//checks ther request follows the correct form
	if(strncmp("GET /", request, 5)){
		//doesn't match
		printf("Recieved invalid request\n");
		return file;
	}else if(strncmp(" HTTP/1.1\r\n", request + (length - 11), 11)){
		//doesn't match
		printf("Recieved invalid request\n");
		return file;
	}else{
		//valid request
		file = malloc((length-16)*sizeof(char));//get memory to store the filename
		memcpy(file, request + 5, length - 16);//copy string to the new buffer
		file[length - 16] = '\0';//set last character to be \0 to end string
	}

	return file;	
}
