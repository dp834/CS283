#include "csapp.h"
#define MAXLINE 64

int main(int argc, char **argv) 
{
 int n;
 rio_t rio;
 char buf[MAXLINE];

 Rio_readinitb(&rio, STDIN_FILENO);
 while((n = rio_readlineb(&rio, buf, MAXLINE)) != 0) 
  Rio_writen(STDOUT_FILENO, buf, n);
 exit(0);
}
