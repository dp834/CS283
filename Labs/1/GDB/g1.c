#include <ctype.h> 
#include <stdio.h> 

int main () 
{
	char c;
	c = fgetc (stdin) ;
	//added brackets to make sure everything runs when it's supposed to
	while (c != EOF) {
		if (isalnum (c) ) {
			printf ("%c\n", c) ;
		} c = fgetc (stdin) ;
	}
	return(1);
}
