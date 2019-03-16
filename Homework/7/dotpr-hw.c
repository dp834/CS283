#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>

#define NUMTHRDS 4
#define VECLEN 100000

pthread_t callThd[NUMTHRDS];
double *array_a;
double *array_b;
double big_sum;
int veclen;

void *dotprod(void *arg){
	long index = *((long *) arg);//cast to int pointer and dereference, makes compiler happy
	//free memory once we have a copy
	free(arg);
	double *x;
	double *y;
	//set arrays
	x = array_a;
	y = array_b;

	//create a sum variable to return
	double *mysum = malloc(sizeof(double));
	*mysum = 0;
	//set start and end data
	int i, start, end;
	start = index*VECLEN;
	end   = start + VECLEN;
	//loop through start and end and mutiply a*b for the dot product
	for (i=start; i<end ; i++){
		(*mysum) += (x[i] * y[i]);
	}
	//return the sum
	pthread_exit(mysum);
}

int main (int argc, char *argv[]){
	long i;
	double *a, *b;
	void *status;
	a = (double*) malloc (NUMTHRDS*VECLEN*sizeof(double));
	b = (double*) malloc (NUMTHRDS*VECLEN*sizeof(double));
	for (i=0; i<VECLEN*NUMTHRDS; i++){
		a[i]=1;
		b[i]=a[i];
	}
	veclen = VECLEN;
	array_a = a;
	array_b = b;
	big_sum = 0;
	/* ... */
	/* create threads */
	/* ... */
	for(i=0;i<NUMTHRDS;i++){
		/* Each thread works on a different set of data.
			The offset is specified by 'i'. The size of
			the data for each thread is indicated by VECLEN.
		 */
		//pass copy of index to thread
		long *copy = malloc(sizeof(long));
		*copy = i;
		pthread_create(&callThd[i], NULL, dotprod, (void *) copy);
	}

	//used to get return value
	double *tempSum;
	for(i=0; i<NUMTHRDS; i++){
		//join to each thread and get return value
		pthread_join(callThd[i], (void **) &tempSum);
		//add sub sums to the large sum
		big_sum += *tempSum;
		//free the malloc from the thread
		free(tempSum);
	}
	//pring sum 
	printf ("Sum = %f \n", big_sum);
	free (a);
	free (b);
}
