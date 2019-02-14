#include "csapp.h"

int main (int argc, char * * argv) 
 {
  char ** pp;
  struct in_addr addr;
  struct hostent * hostp;

  if (argc != 2) 
   {
    fprintf (stderr, "usage: %s < domain name or dotted - decimal > \n", 
    argv[0]) ;
    exit (0) ;
   }

  if (inet_aton (argv[1], &addr) != 0) 
   hostp = Gethostbyaddr ( (const char * ) &addr, sizeof (addr) , AF_INET) ;
    else 
     hostp = Gethostbyname (argv[1]) ;

  printf ("official hostname: %s\n", hostp -> h_name) ;

  for (pp = hostp -> h_aliases; * pp != NULL; pp ++ ) 
   printf ("alias: %s\n", * pp) ;

//pp points to individual entries in *h_addr_list[]
//(struct in_addr * ) *pp points to the in_addr structures
//(struct in_addr * ) *pp)->s_addr is the IP address
  for (pp = hostp -> h_addr_list; * pp != NULL; pp ++ ) 
   {
    addr.s_addr = ( (struct in_addr * ) * pp) -> s_addr;
    printf ("address: %s\n", inet_ntoa (addr) ) ;
   }
  exit (0) ;
 }
