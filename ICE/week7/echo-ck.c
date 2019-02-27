/*
* echo - read and echo text lines until client closes connection
*/
#include "csapp.h"

char* getLineCount(FILE * file){
	char c = getc(file);
	int i = 0;
	while(c != EOF){
		if(c == '\n'){
			i++;
		}
		c = getc(file);
	}
	char *b = malloc(10*sizeof(char));
	sprintf(b, "%d", i);
	return b;
}
			


void echo(int connfd) 
 {
  size_t n, len;
  char bufIN[MAXLINE];
  char *buffFile = NULL;
  

  rio_t rio_socket;
  FILE *readFile;

  Rio_readinitb(&rio_socket, connfd);
  while((n = Rio_readlineb(&rio_socket, bufIN, MAXLINE)) != 0){
	 bufIN[n-1]='\0';
    printf("Opening file: '%s'\n", bufIN);
	 readFile = fopen(bufIN, "r");
	 if(readFile == NULL){
		Rio_writen(connfd, "File not found in server's directory\n", sizeof("File not found in server's directory\n"));
	 }else{ 
		Rio_writen(connfd, getLineCount(readFile), sizeof(getLineCount(readFile)));
		Rio_writen(connfd, "\n", 2);
	   readFile = fopen(bufIN, "r");
		while((n = getline(&buffFile, &len, readFile)) != -1 ){
			Rio_writen(connfd, buffFile, n);
		}
		fclose(readFile);
	 }
  }
 }
