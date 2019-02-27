#include <stdlib.h>

void f (){
	int *x;
	x = malloc(10 * sizeof(int));
	x[9] = 0;//x[10] is out of bounds since we zero index
	//x isn't returned or freed so its a memory leak
	free(x);
}

int main (){
	f();
	return 0;
}
