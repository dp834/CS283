#include <stdio.h> 
#include <stdlib.h> 

int main () 
 {
  char * buf;
  int num;
  //left shift one less so num isn't negative
  num = 1 << 30;
  buf = malloc(num) ;
  fgets (buf, 1024, stdin) ;
  printf ("%s\n", buf) ;
  return(1);
 }
